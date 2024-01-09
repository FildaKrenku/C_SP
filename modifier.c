 /* modifier.c */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#include "modifier.h"

#define WIN_PATH '\\'
#define LIN_PATH '/'
#define PREFIX_FILE '"'
 
 
/**
 * this function is removing spaces of text
 *
 * @param char *text text 
 */
void remove_spaces(char *text) {
	int length;
    int i;
	
	
	if (!text) {
		printf("wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	/* Calculate the length of the input string */
    length = strlen(text);
  

    for ( i = 0; i < length; i++) {
    	/* Check if the current character is an asterisk surrounded by spaces */
        if (text[i] == '*' && i > 0 && i < length - 1 && isspace(text[i - 1]) && isspace(text[i + 1])) {
            /*	 Remove the spaces around the asterisk by shifting the remaining characters */
            memmove(&text[i - 1], &text[i + 2], length - i);
            length -= 2;  /* Update the length of the modified string */
            i--;		  /* Decrement the index to recheck the current position */
        }
    }
    
}


/**
 * this function is rmoving quotes of str
 *
 * @param char *str string with quotes
 */
char* removeQuotes(char *str) {
    int len;
    int j = 0; 
    int i;
    char *result;
    
    /* Argument Check */
    if (!str) {
    	printf("Wrong arguments\n");
    	exit(EXIT_FAILURE);
	}
    
    /* Calculate the length of the input string */
    len = strlen(str);
  

    /* Allocate memory for the result */
    result = (char *)malloc(len + 1); 
	
	/* Check if memory allocation was successful */
    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for ( i = 0; i < len-1; ++i) {
    	/* Check if the current character is not the specified prefix character */
        if (str[i] != PREFIX_FILE) {
            result[j] = str[i];
            j++;
        }
    }
    
    /* Null-terminate the result string */
	result[j] = '\0';  
	
    return result;
}


/**
 * this function is extracting path of filename
 *
 * @param char *filename name of file 
 */
char* extract_path(char *filename) {
	char *lastbslash;
	char *lastslash;
	
	/* argument check */
	if(!filename){
		printf("wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	/* Determine the Last Occurrence of Path Separators */
	lastbslash = strrchr(filename, WIN_PATH);
	lastslash = strrchr(filename, LIN_PATH);
	
    if (lastbslash) {
        /* Get the length of the path */
        int path_len = lastbslash - filename;

        /* Create a new string for the path */
        char *path = (char *)malloc(path_len + 1); 
		
		/* checking if the allocation was successful */
        if (path == NULL) {
            printf("Chyba: Nepodarilo se alokovat pamat pro vystupni cestu.\n");
            exit(EXIT_FAILURE);
        }
		
		/* copiing text to path */
        strncpy(path, filename, path_len);
        path[path_len] = '\0';
		
	
		
        return path;
        
    } else if (lastslash) {
    	/* Get the length of the path */
        int path_len = lastslash - filename;

        /* Create a new string for the path */
        char *path = (char *)malloc(path_len + 1); 
		
		/* checking if the allocation was successful */
        if (path == NULL) {
            printf("Chyba: Nepodarilo se alokovat pamat pro vystupni cestu.\n");
            exit(EXIT_FAILURE);
        }

		/* copiing text to path */
        strncpy(path, filename, path_len);
        path[path_len] = '\0';
		
			
	
        return path;
    	
	} else {
        return NULL;
    }	

}

/**
 * this function is connecting path to filename
 *
 * @param char *path path to file
 * @param char *filename name of file
 */
char* connect_path(char *path, char *filename) {
	
	char *lastbslash;
	char *lastslash;
	
	if(!path || !filename){
		printf("wrong arguments");
		exit(EXIT_FAILURE);
	}

	
	lastbslash = strrchr(path, WIN_PATH);
	lastslash = strrchr(path, LIN_PATH);
	

	/* check if path contains / or \ at the end */
    int path_len = strlen(path);
    
    if (lastbslash) {
    	if (path_len > 0 && path[path_len - 1] != '\\') {
	        /* if not add one to len  */
	        path_len++; 
    	}	
	}
	
	else if (lastslash) {
    	if (path_len > 0 && path[path_len - 1] != '/') {
	        /* if not add one to len  */
	        path_len++; 
    	}	
	}
    

    
    char *result = (char *)malloc(path_len + strlen(filename) + 1); 
	
	/* check if allocating was successful */
    if (result == NULL) {
        printf("Allocating memory failed\n");
        exit(EXIT_FAILURE);
    }

    /* copy existing path to result*/
    strcpy(result, path);

    /* copy proper slash */
    if (lastbslash) {
    	
    	strcat(result, "\\");	
	}
	else if (lastslash) {
		
		strcat(result, "/");	
	}
    
	/* copy filename */
    strcat(result, filename);
	
    return result;
    
}



/**   
 * this function is extraction extension of filename
 *
 * @param char *filename name of file
 */
char* extractExtension(char *filename) {
	char *result;
	
	/*argument check */
	if (!filename) {
		printf("Wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	result = (char *) malloc(strlen(filename) - 1);
	
	/* checking if allocating was successful */
	if (!result) {
		printf("allocating memory failed");
		exit(EXIT_FAILURE);
	}
	
	/* copiing to result */
	strncpy(result, filename, strlen(filename));
	result[strlen(filename) - 2] = '\0';
	
	return result;
	
	
}

/**
 * this fucntion is trimmig whitespace of input
 *
 * @param char *input string with whitespaces
 */
char* trim_white_spaces(char *input) {
	
	/* argument check */
    if (input == NULL) {
        return NULL;  /* Handle NULL input */
    }

    /* Trim leading white characters */
    while (isspace(*input)) {
        input++;
    }

    /* Trim trailing white characters */
    char *end = input + strlen(input) - 1;
    while (end > input && isspace(*end)) {
        end--;
    }
    *(end + 1) = '\0';  /* Null-terminate the trimmed string */

    return input;
}




