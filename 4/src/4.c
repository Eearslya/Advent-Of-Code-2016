#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "4.h"

int main(int argc, char **argv) {
    char *name = "INPUT";
    if (argc > 1) name = argv[1];
    char *input = load_file(name);
    if (input == NULL) {
	printf("There was an error opening the input file \"%s\".\n", name);
	return 1;
    }
    run(input);
    free(input);
    return 0;
}

char *load_file(char *name) {
    FILE *input;
    long len;
    char *ret;
    size_t res;
    input = fopen(name, "r");
    if (input == NULL) return NULL;
    fseek(input, 0, SEEK_END);
    len = ftell(input);
    rewind(input);
    ret = malloc(sizeof(char) * (len+1));
    if (ret == NULL) return NULL;
    res = fread(ret,1,len,input);
    if (res != len) return NULL;
    ret[len] = 0;
    fclose(input);
    return ret;
}

struct room *parse_input(char *input, int *num) {
    char *in, *line;
    char c;
    struct room *ret;
    int i,j,x,state;
    in = malloc(strlen(input)+1);
    strcpy(in, input);
    ret = NULL;
    i = 0;
    line = strtok(in, "\r\n");
    while (line != NULL) {
	int l = strlen(line);
	if (l == 0) break;
	ret = realloc(ret, sizeof(struct room)*(i+1));
	ret[i].name = malloc(l); // Temporary allocation larger than needed
	state = 0;
	x = 0;
	for (j=0; j < l; j++) {
	    c = line[j];
	    if (state == 0) {
		if (c >= '0' && c <= '9') {
		    ret[i].name = realloc(ret[i].name, x);
		    ret[i].name[x-1] = 0;
		    x = 0;
		    state++;
		    j--;
		    continue;
		}
		ret[i].name[x++] = c;
	    }
	    else if (state == 1) {
		ret[i].sector = atoi(&line[j]);
		state++;
	    }
	    else {
		if ((c>='0'&&c<='9')||c=='[') continue;
		ret[i].checksum[x++] = c;
		if (x == 5) {
		    ret[i].checksum[5] = 0;
		    break;
		}
	    }
	}
	i++;
	line = strtok(NULL, "\r\n");
    }
    free(in);
    *num = i;
    return ret;
}

void free_rooms(struct room *rooms, int count) {
    int i;
    for (i=0; i < count; i++) {
	if (rooms[i].name != NULL) free(rooms[i].name);
    }
}

void run(char *input) {
    struct room *rooms,*valid;
    int count,vcount;
    rooms = parse_input(input, &count);
    valid = filter_rooms(rooms, count, &vcount);
    printf("Part One Solution: %d\n", part_one(valid, vcount));
    printf("Part Two Solution: %d\n", part_two(valid, vcount));
    free_rooms(rooms, count);
    free(rooms);
    free(valid);
}

void decrypt(char *str, int r) {
    int i,len;
    char c;
    len = strlen(str);
    for (i=0; i < len; i++) {
	c = str[i];
	if (c == '-') str[i] = ' ';
	else str[i] = rotx(c, r);
    }
}

char rotx(char c, int r) {
    int i;
    for (i=0; i < r; i++) {
	c++;
	if (c > 'z') c = 'a';
    }
    return c;
}

struct room *filter_rooms(struct room *rooms, int len, int *valid) {
    struct room *ret;
    int i,j,v,x,y,z;
    unsigned char counts[26];
    char topfive[6];
    v = 0;
    ret = NULL;
    topfive[5] = 0;
    for (i=0; i < len; i++) {
	x = strlen(rooms[i].name);
	memset(counts,0,sizeof(unsigned char)*26);
	for (j=0; j < x; j++) {
	    if (rooms[i].name[j] == '-') continue;
	    counts[(rooms[i].name[j]-'a')]++;
	}
	x = 0;
	for (x=0; x < 5; x++) {
	    y = 0;
	    z = 0;
	    for (j=0; j < 26; j++) {
		if (counts[j] > y) {
		    y = counts[j];
		    z = j;
		}
	    }
	    topfive[x] = z+'a';
	    counts[z] = 0;
	}
	if (strcmp(rooms[i].checksum, topfive) == 0) {
	    ret = realloc(ret, sizeof(struct room)*(v+1));
	    memcpy(&ret[v],&rooms[i],sizeof(struct room));
	    v++;
	}
    }
    *valid = v;
    return ret;
}

int part_one(struct room *rooms, int len) {
    int i,ret;
    ret = 0;
    for (i=0; i < len; i++) {
	ret += rooms[i].sector;
    }
    return ret;
}

int part_two(struct room *rooms, int len) {
    int i;
    for (i=0; i < len; i++) {
	decrypt(rooms[i].name, rooms[i].sector);
	if (strcmp(rooms[i].name, "northpole object storage") == 0) return rooms[i].sector;
    }
    return 0;
}
