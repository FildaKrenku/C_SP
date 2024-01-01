/* check.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"


/**
 * Funkce pro kontrolu bilich zanku
 * kokotpica
 */
int linecheck(const char *str, const char *prefix) {
    size_t prefixLen = strlen(prefix);
    size_t strLen = strlen(str);
    size_t i;

    if (strLen < prefixLen) {
        return 0;  
    }

    if (strncmp(str, prefix, prefixLen) != 0) {
        return 0;  
    }

    
    for ( i = prefixLen; i < strLen; i++) {
        if (!isspace(str[i])) {
            return 0; 
        }
    }

    return 1;  
}



int is_file_exist(char *filename){
	
	if(!filename){
		return 0;
	}
	
	FILE *f = fopen(filename, "r");
	
	if(f){
		fclose(f);
		return 1;
	} else {
		return 0;
	}
	
	
}



void printStringWithWhitespace(const char *str) {
	int i;
    for (i = 0; str[i] != '\0'; i++) {
        printf("Char: %c ASCII: %d\n", str[i], str[i]);
    }
}
