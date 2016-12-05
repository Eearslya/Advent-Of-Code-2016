#include <openssl/md5.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "5.h"

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
    char *ret,line[32];
    int i;
    input = fopen(name, "r");
    if (input == NULL) return NULL;
    fgets(line, 32, input);
    len = strlen(line);
    ret = malloc(sizeof(char) * (len+1));
    if (ret == NULL) return NULL;
    strcpy(ret, line);
    for (i=0; i < len; i++) if (ret[i]=='\r'||ret[i]=='\n')ret[i]=0;
    fclose(input);
    return ret;
}

void run(char *input) {
    get_password(input,1);
    get_password(input,2);
}

void get_password (char *input, int part) {
    int i,locked,val,pos;
    unsigned char md5[16];
    char *str;
    char c, ret[9];
    size_t len, max;
    locked = 0;
    max = strlen(input) + 16;
    str = malloc(max);
    memset(ret,'*',8);
    ret[8] = 0;
    if (part == 1) pos = 0;
    printf("Part %s Solution: %s\r", (part==1?"One":"Two"), ret);
    fflush(stdout);
    for(i=0;1;i++) {
	len = snprintf(str, max, "%s%d", input, i);
	MD5((const unsigned char*)str, len, md5);
	if (md5[0] == 0 && md5[1] == 0 && (md5[2]&0xF0) == 0) {
	    val = (part==1)?(md5[2]&0x0F):((md5[3]&0xF0)>>4);
	    if (part == 2) pos = md5[2]&0x0F;
	    if (pos >= 8 || ret[pos] != '*') continue;
	    c = (val<=9)?(val+'0'):(val+'a'-10);
	    ret[pos] = c;
	    if (part == 1) pos++;
	    printf("Part %s Solution: %s\r", (part==1?"One":"Two"), ret);
	    fflush(stdout);
	    locked++;
	}
	if (locked == 8) break;
    }
    printf("\n");
    free(str);
}
