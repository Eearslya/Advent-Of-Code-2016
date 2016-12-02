#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1.h"

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

struct inst *parse_input(char *str, int *res) {
    int i, len, count, dist;
    char *buf, *input;
    char dir;
    struct inst *ret;

    len = strlen(str);
    input = malloc(sizeof(char)*(len+1));
    strcpy(input,str);
    count = 1;
    for (i=0; i < len; i++) {
	if (input[i] == ',') count++;
    }

    ret = malloc(sizeof(struct inst) * count);
    buf = strtok(input,", ");
    i = 0;
    while (buf != NULL) {
	sscanf(buf, "%c%d", &dir, &dist);
	if (dir == 'L') ret[i].dir = LEFT;
	else ret[i].dir = RIGHT;
	ret[i].dist = dist;
	buf = strtok(NULL, ", ");
	i++;
    }
    if (i == 0) {
	free(input);
	free(ret);
	return NULL;
    }

    *res = count;
    free(input);
    return ret;
}

int turn(int start, int dir) {
    if (dir == LEFT) start--;
    else start++;
    if (start == 0) start = 4;
    if (start == 5) start = 1;
    return start;
}

void run(char *input) {
    int count, partone, parttwo, i, j, x, y, dir;
    unsigned char map[1024][1024];
    struct inst *inst;
    inst = parse_input(input, &count);
    parttwo = -1;
    x = 512;
    y = 512;
    dir = NORTH;
    memset(map,0,1024*1024);
    for (i=0; i < count; i++) {
	dir = turn(dir, inst[i].dir);
	for (j=0; j < inst[i].dist; j++) {
	    if (dir==NORTH) y++;
	    else if (dir==EAST) x++;
	    else if (dir==SOUTH) y--;
	    else x--;
	    map[y][x]++;
	    if (map[y][x] > 1 && parttwo == -1) {
		parttwo = abs(512-abs(x)) + abs(512-abs(y));
	    }
	}
    }
    partone = abs(512-abs(x)) + abs(512-abs(y));
    printf("Part One Solution: %d\nPart Two Solution: %d\n",partone,parttwo);
    free(inst);
}
