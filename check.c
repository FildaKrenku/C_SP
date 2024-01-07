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
	int prefixLen;
	int strLen;
	int i;
	
	/* argumets check */
	if (!str || !prefix) {
		printf("Wrong argumetns");
		exit(EXIT_FAILURE);
	}
	
	/* Calculate the lengths of the input string and the specified prefix */
    prefixLen = strlen(prefix);
    strLen = strlen(str);
   
	/* Prefix Comparison */
    if (strLen < prefixLen) {
        return 0;  
    }

	 /* Prefix Comparison */
    if (strncmp(str, prefix, prefixLen) != 0) {
        return 0;  
    }

     /* Whitespace Check */
    for ( i = prefixLen; i < strLen; i++) {
        if (!isspace(str[i])) {
            return 0; 
        }
    }
	
	/* If all checks pass, returns 1 */
    return 1;  
}



int is_file_exist(char *filename) {
	FILE *f;
	
	/* arguments check */
	if (!filename) {
		return 0;
	}
	/* opeing of the file */
	f = fopen(filename, "r");
	
	/* if opening was successfull returns 1 if not returns 0 */
	if (f) {
		fclose(f);
		return 1;
	} else {
		return 0;
	}
	
	
}

