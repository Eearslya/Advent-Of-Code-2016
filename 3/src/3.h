#ifndef AOC_3_H
#define AOC_3_H

struct triangle {
    int a;
    int b;
    int c;
};

char *load_file(char*);
void run(char*);
int find_real(struct triangle*,int);
struct triangle *parse_input_one(char*,int*);
struct triangle *parse_input_two(char*,int*);

#endif /* AOC_3_H */
