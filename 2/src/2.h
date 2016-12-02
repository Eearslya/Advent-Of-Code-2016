#ifndef AOC_2_H
#define AOC_2_H

int aoc(int,char**);
char *keypad(char**,int,int,int,char**,int,int);
char *part_one(char**,int);
char *part_two(char**,int);
char *load_file(char*);
char **parse_input(char*,int*);
void error(char*);
void run(char*);

#endif /* AOC_2_H */
