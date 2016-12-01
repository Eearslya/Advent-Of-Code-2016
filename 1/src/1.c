#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1.h"

#ifdef UNITTEST /* Remove main() and swap memory functions if we're doing unit tests */
# include <stdlib.h>
# include <setjmp.h>
# include <stddef.h>
# include <cmocka.h>
# define malloc(n) test_malloc(n)
# define calloc(n,c) test_calloc(n,c)
# define free(n) test_free(n)
# define realloc(n,s) test_realloc(n,s)
#else
int main(int argc, char **argv) {
    return aoc(argc, argv);
}
#endif /* UNITTEST */

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

struct inst *parse_input(char *str, int *res) {
    int i, len, count, dist;
    char *buf, *input;
    char dir;
    struct inst *ret;

    input = NULL;
    ret = NULL;
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

void run(char *input) {
    int count;
    struct inst *inst = parse_input(input, &count);
    printf("Part One Solution: %d\n", part_one(inst, count));
    printf("Part Two Solution: %d\n", part_two(inst, count));
    free(inst);
}

int turn(int start, int dir) {
    if (dir == LEFT) start--;
    else start++;
    if (start == 0) start = 4;
    if (start == 5) start = 1;
    return start;
}

int part_one(struct inst *input, int len) {
    int i;
    int x = 0;
    int y = 0;
    int dir = NORTH;
    for (i=0; i < len; i++) {
	dir = turn(dir, input[i].dir);
	if (dir == NORTH) y += input[i].dist;
	else if (dir == EAST) x += input[i].dist;
	else if (dir == SOUTH) y -= input[i].dist;
	else x -= input[i].dist;
    }
    int distance = abs(x) + abs(y);
    return distance;
}

int part_two(struct inst *input, int len) {
    int i, j;
    int x = 512;
    int y = 512;
    int dir = NORTH;
    int done = 0;
    unsigned char map[1024][1024];
    for (i=0; i < 1024; i++) {
	for (j=0; j < 1024; j++) {
	    map[i][j] = 0;
	}
    }
    for (i=0; i < len; i++) {
	dir = turn(dir, input[i].dir);
	for (j=0; j < input[i].dist; j++) {
	    if (dir==NORTH) y++;
	    else if (dir==EAST) x++;
	    else if (dir==SOUTH) y--;
	    else x--;
	    map[y][x]++;
	    if (map[y][x] > 1) {
		done = 1;
		break;
	    }
	}
	if (done) break;
    }
    int distance = abs(512-abs(x)) + abs(512-abs(y));
    return distance;
}
