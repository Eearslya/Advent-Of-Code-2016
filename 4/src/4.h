#ifndef AOC_4_H
#define AOC_4_H

struct room {
    char *name;
    int sector;
    char checksum[6];
};

char rotx(char,int);
char *load_file(char*);
void run(char*);
void decrypt(char*,int);
struct room *parse_input(char*,int*);
struct room *filter_rooms(struct room*,int,int*);
int part_one(struct room*,int);
int part_two(struct room*,int);

#endif /* AOC_4_H */
