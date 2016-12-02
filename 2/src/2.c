#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "2.h"

int main(int argc, char **argv) {
    return aoc(argc, argv);
}

int aoc(int argc, char **argv) {
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

char **parse_input(char *str, int *res) {
    char **ret;
    char *input;
    char *line;
    int i;
    input = malloc(strlen(str)+1);
    strcpy(input,str);
    ret = NULL;
    line = strtok(input,"\r\n");
    i = 0;
    while (line != NULL) {
	int len = strlen(line);
	if (len == 0) break;
	ret = realloc(ret, sizeof(char*)*(i+1));
	ret[i] = malloc(len+1);
	strcpy(ret[i],line);
	line = strtok(NULL,"\r\n");
	i++;
    }
    *res = i;
    free(input);
    return ret;
}

void free_input(char **input, int len) {
    int i;
    for (i=0; i < len; i++) {
	free(input[i]);
    }
}

void run(char *input) {
    int count;
    char **strs = parse_input(input, &count);
    char *one = part_one(strs, count);
    char *two = part_two(strs, count);
    printf("Part One Solution: %s\n", one);
    printf("Part Two Solution: %s\n", two);
    free(one);
    free(two);
    free_input(strs, count);
    free(strs);
}

char *keypad(char **input, int len, int sx, int sy, char **m, int xx, int yx) {
    int i,j,x,y,z;
    char *code = malloc(sizeof(char)*(len+1));
    x = sx;
    y = sy;
    for (i=0; i < len; i++) {
	z = strlen(input[i]);
	for (j=0; j < z; j++) {
	    switch(input[i][j]) {
	    case 'U':
		if (y>0 && m[y-1][x] != ' ') y--;
		break;
	    case 'R':
		if (x<xx && m[y][x+1] != ' ') x++;
		break;
	    case 'D':
		if (y<yx && m[y+1][x] != ' ') y++;
		break;
	    case 'L':
		if (x>0 && m[y][x-1] != ' ') x--;
		break;
	    }
	}
	code[i] = m[y][x];
    }
    code[len] = 0;
    return code;
}

char *part_one(char **input, int len) {
    char *pad[3] = {
	"123",
	"456",
	"789"
    };
    return keypad(input,len,1,1,pad,2,2);
}

char *part_two(char **input, int len) {
    char *pad[5] = {
	"  1  ",
	" 234 ",
	"56789",
	" ABC ",
	"  D  "
    };
    return keypad(input,len,0,2,pad,4,4);
}
