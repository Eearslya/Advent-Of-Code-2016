#ifndef AOC_1_H
#define AOC_1_H

#define NORTH 1
#define EAST  2
#define SOUTH 3
#define WEST  4

#define LEFT  1
#define RIGHT 2

struct inst {
  short dir;
  short dist;
};

void error(char*);
struct inst *parse_input(char*,int*);
void run(char*);
int turn(int,int);
int part_one(struct inst*,int);
int part_two(struct inst*,int);

#endif /* AOC_1_H */
