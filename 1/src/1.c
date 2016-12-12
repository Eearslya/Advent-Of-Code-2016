#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1.h"

int main(int argc, char **argv) {
    char *name = "INPUT";
    if (argc > 1) name = argv[1];
    char *input = load_file(name);
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
    if (input == NULL) error("Error opening file!");
    fseek(input, 0, SEEK_END);
    len = ftell(input);
    rewind(input);
    ret = malloc(sizeof(char) * (len+1));
    if (ret == NULL) error("Out of memory!");
    res = fread(ret,1,len,input);
    if (res != len) error("Error reading file!");
    ret[len] = 0;
    fclose(input);
    return ret;
}

void inst_push(struct inst **head, int dir, int dist) {
    struct inst *cur;
    if (*head == NULL) {
	*head = malloc(sizeof(struct inst));
	if (*head == NULL) error("Out of memory!");
	(*head)->dir = dir;
	(*head)->dist = dist;
	(*head)->next = NULL;
	return;
    }
    cur = *head;
    while (cur->next != NULL) cur = cur->next;
    cur->next = malloc(sizeof(struct inst));
    if (cur->next == NULL) error("Out of memory!");
    cur->next->dir = dir;
    cur->next->dist = dist;
    cur->next->next = NULL;
}

struct inst *inst_pop(struct inst **head) {
    struct inst *ret;
    struct inst *next;
    if (*head == NULL) return NULL;
    next = (*head)->next;
    ret = *head;
    *head = next;
    return ret;
}

int pos_push(struct pos **head, int x, int y) {
    struct pos *cur;
    if (*head == NULL) {
	*head = malloc(sizeof(struct pos));
	if (*head == NULL) error("Out of memory!");
	(*head)->x = x;
	(*head)->y = y;
	(*head)->next = NULL;
	return 1;
    }
    cur = *head;
    while (cur->next != NULL) {
	if (cur->x == x && cur->y == y) return 0;
	cur = cur->next;
    }
    cur->next = malloc(sizeof(struct pos));
    if (cur->next == NULL) error("Out of memory!");
    cur->next->x = x;
    cur->next->y = y;
    cur->next->next = NULL;
    return 1;
}

void pos_destroy(struct pos *head) {
    struct pos *tmp;
    while (head != NULL) {
	tmp = head;
	head = head->next;
	free(tmp);
    }
}

struct inst *parse_input(char *str) {
    int dist;
    char *buf;
    char dir;
    struct inst *ret;
    ret = NULL;
    buf = strtok(str,", ");
    while (buf != NULL) {
	if (sscanf(buf, "%c%d", &dir, &dist) != 2) error("Invalid input file!");
	inst_push(&ret,(dir=='L'?LEFT:RIGHT),dist);
	buf = strtok(NULL, ", ");
    }
    return ret;
}

void run(char *input) {
    int partone, parttwo, j, x, y, dir;
    struct inst *insts;
    struct inst *inst;
    struct pos *pos;
    pos = NULL;
    insts = parse_input(input);
    parttwo = -1;
    x = 0;
    y = 0;
    dir = NORTH;
    while ((inst = inst_pop(&insts)) != NULL) {
	dir += (inst->dir==LEFT?(dir==0?3:-1):(dir==3?-3:1));
	for (j=0; j < inst->dist; j++) {
	    x += move_matrix[dir][0];
	    y += move_matrix[dir][1];
	    if (parttwo == -1 && !pos_push(&pos,x,y)) {
		parttwo = abs(x) + abs(y);
	    }
	}
	free(inst);
    }
    pos_destroy(pos);
    partone = abs(x) + abs(y);
    printf("Part One Solution: %d\nPart Two Solution: %d\n",partone,parttwo);
}

void _error(char *msg, const char *file, int line) {
    printf("%s:%d: %s\n", file, line, msg);
    exit(1);
}
