#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "1.h"

int main(int argc, char **argv) {
  FILE *input;
  long len;
  char *in;
  size_t res;
  input = fopen("INPUT", "r");
  if (input == NULL) error("Could not open the \"INPUT\" file!\n");
  fseek(input, 0, SEEK_END);
  len = ftell(input);
  rewind(input);
  in = malloc(sizeof(char) * (len+1));
  if (in == NULL) error("Out of memory!\n");
  res = fread(in,1,len,input);
  if (res != len) error("There was an error reading the \"INPUT\" file.\n");
  in[len] = 0;
  fclose(input);
  run(in);
  free(in);
  return 0;
}

struct inst *parse_input(char *input, int *res) {
  int i;
  struct inst *ret;
  int len = strlen(input);
  int count = 1;
  for (i=0; i < len; i++) {
    if (input[i] == ',') count++;
  }
  ret = malloc(sizeof(struct inst) * count);
  char *buf;
  char dir;
  int dist;
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
  *res = count;
  return ret;
}

void error(char *msg) {
  printf(msg);
  exit(1);
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
