 /* modifier.c */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "modifier.h"
 
 
/** 
 * funkce pro smazani bilich znaku.
 * kokotpica
 */ 
void remove_spaces(char *text) {
    int length = strlen(text);
    int i;

    for ( i = 0; i < length; i++) {
        if (text[i] == '*' && i > 0 && i < length - 1 && isspace(text[i - 1]) && isspace(text[i + 1])) {
           
            memmove(&text[i - 1], &text[i + 2], length - i);
            length -= 2;
            i--;
        }
    }
}



char* removeQuotes(char *str) {
    int len = strlen(str);
  
    char *result = (char *)malloc(len + 1);  
    char prefix_file = '"';
    
    
    int j = 0;  /* Index pro nový řetězec */
    int i;

    if (result == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    for ( i = 0; i < len-1; ++i) {
        if (str[i] != prefix_file) {
            result[j] = str[i];
            j++;
        }
    }
    
	result[j] = '\0';  
	
    return result;
}



char* extract_path(char *filename) {
	char *lastslash = strrchr(filename, '\\');
    if (lastslash) {
        /* Získat délku cesty (počítáno od začátku řetězce) */
        size_t path_len = lastslash - filename;

        /* Vytvořit nový řetězec pro cestu s dynamickou alokací paměti */
        char *path = (char *)malloc(path_len + 1); /* +1 pro null-terminátor */

        if (path == NULL) {
            printf("Chyba: Nepodarilo se alokovat pamat pro vystupni cestu.\n");
            exit(EXIT_FAILURE);
        }

        strncpy(path, filename, path_len);
        path[path_len] = '\0';
		
		/*
        printf("Extrahovana cesta k souboru: %s\n", path);
		*/

        return path;
    } else {
        return NULL; /* Pokud zpětné lomítko není nalezeno, vraťte NULL */
    }	

}


char* connect_path(char *path, char *filename) {
	/* Zkontrolovat, zda cesta obsahuje zpětné lomítko na konci */
    size_t path_len = strlen(path);
    if (path_len > 0 && path[path_len - 1] != '\\') {
        /* Pokud není, přidat zpětné lomítko */
        path_len++; 
    }

    /* Připravit nově alokovaný řetězec pro spojenou cestu */
    char *result = (char *)malloc(path_len + strlen(filename) + 1); /* +1 pro null-terminátor */

    if (result == NULL) {
        printf("Chyba: Nepodarilo se alokovat pamat pro spojenou cestu.\n");
        exit(EXIT_FAILURE);
    }

    /* Kopírovat existující cestu */
    strcpy(result, path);

    /* Připojit název souboru k cestě */
    strcat(result, "\\");

    strcat(result, filename);
	
    return result;
    
}




char* extractExtension(char *filename){
	
	char *result = (char *) malloc(strlen(filename) - 1);
	
	strncpy(result, filename, strlen(filename));
	result[strlen(filename) - 2] = '\0';
	
	return result;
	
	
}







