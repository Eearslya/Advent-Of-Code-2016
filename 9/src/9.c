#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "9.h"

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
    int i;
    input = fopen(name, "r");
    if (input == NULL) return NULL;
    fseek(input, 0, SEEK_END);
    len = ftell(input);
    rewind(input);
    ret = malloc(sizeof(char) * (len+1));
    if (ret == NULL) return NULL;
    res = fread(ret,1,len,input);
    if (res != len) return NULL;
    for (i=0;i<len;i++)if(ret[i]=='\n'||ret[i]=='\r')ret[i]=0;
    ret[len] = 0;
    fclose(input);
    return ret;
}

long decompress(char *str, int recurse) {
    char *inner;
    int pos, len, skipamount, skipcount;
    long ret;
    len = strlen(str);
    ret = 0;
    for (pos=0; pos < len;) {
	if (str[pos] == '(') {
	    sscanf(&str[pos], "(%dx%d)", &skipamount, &skipcount);
	    while(str[pos++]!=')'){}
	    if (recurse == 0) {
		ret += (skipamount * skipcount);
	    }
	    else {
		inner = calloc(skipamount+1,1);
		memcpy(inner, &str[pos], skipamount);
		ret += decompress(inner, 1) * skipcount;
		free(inner);
	    }
	    pos += skipamount;
	}
	else {
	    ret++;
	    pos++;
	}
    }
    return ret;
}

void run(char *input) {
    printf("Part One Solution: %lu\n", decompress(input, 0));
    printf("Part Two Solution: %lu\n", decompress(input, 1));
}
