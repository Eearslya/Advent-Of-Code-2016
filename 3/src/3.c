#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "3.h"

int main(int argc, char **argv) {
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

struct triangle *parse_input_one(char *str, int *res) {
    int i;
    char *line;
    char *input;
    struct triangle *ret;
    input = malloc(strlen(str)+1);
    strcpy(input,str);
    line = strtok(input, "\r\n");
    ret = NULL;
    i = 0;
    while (line != NULL) {
	if (strlen(line) == 0) break;
	ret = realloc(ret, sizeof(struct triangle)*(i+1));
	sscanf(line, "%d%d%d", &ret[i].a, &ret[i].b, &ret[i].c);
	line = strtok(NULL, "\r\n");
	i++;
    }
    *res = i;
    free(input);
    return ret;
}

struct triangle *parse_input_two(char *str, int *res) {
    int i,a,b,c;
    char *line;
    char *input;
    struct triangle *ret;
    input = malloc(strlen(str)+1);
    strcpy(input,str);
    line = strtok(input, "\r\n");
    ret = NULL;
    i = 0;
    while (line != NULL) {
	if (strlen(line) == 0) break;
	ret = realloc(ret,sizeof(struct triangle)*(i+3));
	sscanf(line,"%d%d%d",&a,&b,&c);
	ret[i].a = a;
	ret[i+1].a = b;
	ret[i+2].a = c;
	line = strtok(NULL,"\r\n");
	sscanf(line,"%d%d%d",&a,&b,&c);
	ret[i].b = a;
	ret[i+1].b = b;
	ret[i+2].b = c;
	line = strtok(NULL,"\r\n");
	sscanf(line,"%d%d%d",&a,&b,&c);
	ret[i].c = a;
	ret[i+1].c = b;
	ret[i+2].c = c;
	line = strtok(NULL,"\r\n");
	i += 3;
    }
    *res = i;
    free(input);
    return ret;
}

void run(char *input) {
    int count;
    struct triangle *t1, *t2;
    t1 = parse_input_one(input, &count);
    printf("Part One Solution: %d\n", find_real(t1, count));
    t2 = parse_input_two(input, &count);
    printf("Part Two Solution: %d\n", find_real(t2, count));
    free(t1);
    free(t2);
}

int find_real(struct triangle *input, int count) {
    int ret,i,a,b,c;
    ret = 0;
    for (i=0; i < count; i++) {
	a = input[i].a;
	b = input[i].b;
	c = input[i].c;
	if ((a+b)>c && (a+c)>b && (c+b)>a) ret++;
    }
    return ret;
}
