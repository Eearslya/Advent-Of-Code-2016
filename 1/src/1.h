#ifndef AOC_1_H
#define AOC_1_H

#define NORTH 1
#define EAST  2
#define SOUTH 3
#define WEST  4

#define LEFT  1
#define RIGHT 2

struct inst {
    unsigned char dir;
    unsigned char dist;
};

int aoc(int,char**);
int turn(int,int);
int part_one(struct inst*,int);
int part_two(struct inst*,int);
char *load_file(char*);
void error(char*);
void run(char*);
struct inst *parse_input(char*,int*);

#endif /* AOC_1_H */
