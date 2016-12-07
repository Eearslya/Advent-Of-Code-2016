#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "6.h"

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

void run(char *input) {
    int **counts;
    char *code, *one, *two;
    int size, i, j, high, low, h, l;
    code = strtok(input, "\r\n");
    size = strlen(code);
    counts = malloc(sizeof(int*)*size);
    for (i=0; i < size; i++) counts[i] = calloc(sizeof(int)*26,1);
    one = calloc(size+1, 1);
    two = calloc(size+1, 1);
    while (code != NULL) {
	for (i=0; i < size; i++) counts[i][(code[i]-'a')]++;
	code = strtok(NULL, "\r\n");
    }
    for (i=0; i < size; i++) {
	high = 0;
	low = 9999;
	for (j=0; j < 26; j++) {
	    if (counts[i][j] > high) {
		high = counts[i][j];
		h = j;
	    }
	    if (counts[i][j] < low) {
		low = counts[i][j];
		l = j;
	    }
	}
	one[i] = h+'a';
	two[i] = l+'a';
    }
    printf("Part One Solution: %s\n", one);
    printf("Part Two Solution: %s\n", two);
    for (i=0; i < size; i++) free(counts[i]);
    free(counts);
    free(one);
    free(two);
}
