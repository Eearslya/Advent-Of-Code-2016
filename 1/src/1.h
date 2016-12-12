#ifndef AOC_1_H
#define AOC_1_H

#define NORTH 0
#define EAST  1
#define SOUTH 2
#define WEST  3

#define LEFT  1
#define RIGHT 2

#define error(m) _error(m,__FILE__,__LINE__)

struct pos {
    int x;
    int y;
    struct pos *next;
};

struct inst {
    unsigned char dir;
    unsigned char dist;
    struct inst *next;
};

char move_matrix[4][2] = {{0,1},{1,0},{0,-1},{-1,0}};

void inst_push(struct inst**,int,int);
void pos_destroy(struct pos*);
void run(char*);
void _error(char*,const char*,int);
int pos_push(struct pos**,int,int);
char *load_file(char*);
struct inst *inst_pop(struct inst**);
struct inst *parse_input(char*);

#endif /* AOC_1_H */
