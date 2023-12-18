/* ccdoc.c main */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comment.h"
#include "filequeue.h"

/*Funkce pro zpracování dokumentačního komentáře */ 
void processComment(commentQueue *queue,char  *com) {
   add(queue, com); 
}


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


/* Funkce pro načtení souboru a zpracování dokumentace */
void processFile(commentQueue *queue, char *filename) {
	
	char line[1024];
    char commentBuffer[1024];
    int insideComment = 0;
    
    FILE *file = fopen(filename, "r");
    
    if (file == NULL) {
        printf("Chyba: Nelze otevrit soubor %s.\n", filename);
        
        exit(2);  /* Návratový kód 2 pro chybu souboru */
    }

  

    while (fgets(line, sizeof(line), file)) {
    	
    	
    	
        /* Zpracování dokumentačních komentářů */
        if (linecheck(line, "/**") || linecheck(line, "/*!")) {
            insideComment = 1;
            strcpy(commentBuffer, line);
        } else if (insideComment && strstr(line, "*/")) {
            strcat(commentBuffer, line);
            processComment(queue, commentBuffer);
            insideComment = 0;
        } else if (insideComment) {
            strcat(commentBuffer, line);
        }
    }

    fclose(file);
}

/**
 *main kokotpica
*/
int main(int argc, char *argv[]) {
	char *inputFile = argv[1];
    char *outputFile = NULL;
    
   	const char *ex = ".c";
    char *dotC = strstr(inputFile,ex);
    const char *ex2 = ".h";
    char *dotH = strstr(inputFile,ex2);
    
    commentQueue *queue;
    fileQueue *fqueue;
    char *newname;

	
	
    /* Zpracování příkazové řádky */
    if (argc < 2) {
    	
        
        printf("Chyba: Nebyl zadan vstupni soubor.\n");
        printf("Pouziti: %s <vstupni_soubor.c>\n", argv[0]);
        
        
        exit(1);  /* Návratový kód 1 pro chybný vstup */
    }
     
    if(!dotC && !dotH){
    	printf("Chyba: spatna pripona souboru \n");
    	exit(1);
	}
    

/*
    if (argc == 3) {
        
        outputFile = argv[2];
    } else {
        
        char *dotPosition = strrchr(inputFile, '.');
        if (dotPosition != NULL) {
            *dotPosition = '\0';  
            asprintf(&outputFile, "%s-doc.tex", inputFile);
        } else {
            fprintf(stderr, "Chyba: Nebyla rozpoznana pripona vstupniho souboru.\n");
            exit(1);
        }
    }
   */ 

	/* alocation memory for comqueue */
    queue = (commentQueue *)malloc(sizeof(commentQueue));
    if (queue == NULL) {
        printf("Chyba: Nepodarilo se alokovat pamat pro frontu komentaru.\n");
        exit(EXIT_FAILURE);
    }

    initializeQueue(queue);
    
    
    /* alocation memory for filenamequeue */
    fqueue = (fileQueue *) malloc(sizeof(fileQueue));
     if (fqueue == NULL) {
        printf("Chyba: Nepodarilo se alokovat pamat pro frontu komentaru.\n");
        exit(EXIT_FAILURE);
    }
    
    initializeFileQueue(fqueue);
    
	addFilename(fqueue, inputFile);
	
	printFileQueue(fqueue);
	
	while(fqueue->start != NULL){
	
		newname = peek(fqueue);
		processFile(queue, newname);	
	}
	
	
	printComments(queue);
 
    /* Uvolnění paměti */
    free(inputFile);
    free(outputFile);
    freeQueue(queue);
    freeFileQueue(fqueue);
   

    return 0;
}