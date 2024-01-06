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
    int prefixLen = strlen(prefix);
    int strLen = strlen(str);
    int i;

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

