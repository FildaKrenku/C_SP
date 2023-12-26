/* ccdoc.c main */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "filequeue.h"
#include "comment.h"
#include "comment.h"
#include "kokot.c"



#define LINE_LEN 1024


/**
 * Funkce pro zpracovani komentare 
 */
void processComment(commentQueue *queue,char  *com) {
   add(queue, com); 
}

/**
 * Funkce pro vypsani modulu
 */
void print_module(char *module){
	printf("Module: %s \n\n", module);
}


char* removeQuotes(char *str) {
    int len = strlen(str);
  
    char *result = (char *)malloc(len);  
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



void findFiles(fileQueue *fqueue, char *filename){
	const char *include_prefix = "#include ";
	char *inc;
	char *file_s;
	char *file_e1;
	char *file_e2;
	
	char *final;
	
	const char *ex1 = ".c";
	const char *ex2 = ".h";
	const char prefix_file = '"';

	
	char line[LINE_LEN];
	
	FILE *file = fopen(filename, "r");
	
	if(file == NULL){
		printf("soubor neexistuje");
		exit(2);
	}
	
	while(fgets(line, sizeof(line), file)){
		inc = strstr(line, include_prefix);
		if(inc){
			file_s = strchr(inc, prefix_file);
			if(file_s){
				file_e1 = strstr(file_s, ex1);
				file_e2 = strstr(file_s, ex2);
				if(file_e1 || file_e2){
					
					final = removeQuotes(file_s);
					
					if(is_file_set(fqueue, final) == 0){
						addFilename(fqueue, final);	
					}
				}
			}
		}
		
	}
}





/**
 * Funkce pro kontrolu bilich zanku
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


/**
 * Funkce pro nacteni souboru a zpracovani komentaru
 *  
 * @param commentQueue *queue fronta komentaru
 * @param char *filename jmeno souboru 
 * @return void nic
 */
void findComments(commentQueue *queue, char *filename) {
	

	
	
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Chyba: Nelze otevrit soubor %s.\n", filename);
        exit(2);  /* Návratový kód 2 pro chybu souboru */
    }

    char line[LINE_LEN];
    char commentBuffer[5 * LINE_LEN];
    int insideComment = 0;
    int store_last = 0;

    while (fgets(line, sizeof(line), file)) {
        /* Zpracování dokumentačních komentářů */
        if (linecheck(line, "/**") || linecheck(line, "/*!")) {
            insideComment = 1;
            strncpy(commentBuffer, line, sizeof(line));
        } else if (insideComment && strstr(line, "*/")) {
            strncat(commentBuffer, line, sizeof(line));
            insideComment = 0;
            store_last = 1;
        } else if (insideComment) {
            strncat(commentBuffer, line, sizeof(line));
        } else if (store_last){
        	strncat(commentBuffer, line, sizeof(line));
        	store_last = 0;
        	processComment(queue, commentBuffer);
		}
        
    }

    fclose(file);
}

/**
 * main kokotpica
 */
int main(int argc, char *argv[]) {
	char *inputFile = argv[1];	
    char *outputFile = NULL;
    
	const char *ex = ".c";
    char *dotC = strstr(inputFile,ex);
    const char *ex2 = ".h";
    char *dotH = strstr(inputFile,ex2);
    
    char *texextension = "-doc.tex";
    
    int inputLen = strlen(inputFile);
    char *dotPosition = strrchr(inputFile, '.');
    
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
	
	
    


    if (argc == 3) {
        outputFile = argv[2];
    } else {
        
       
        if (dotPosition != NULL) {
        	
        	outputFile = (char *)malloc(sizeof(inputLen + strlen(texextension) + 1));

            if (outputFile == NULL) {
                printf("Chyba: Nepodarilo se alokovat pamat pro vystupni soubor.\n");
                exit(EXIT_FAILURE);
            }
        
        	strncpy(outputFile, inputFile, strlen(inputFile)-2);
        
        	strcat(outputFile,texextension);
        
            
           
            
        } else {
            printf("Chyba: Nebyla rozpoznana pripona vstupniho souboru.\n");
            exit(1);
        }
    }

		printf("%s\n",inputFile);
		printf("%s\n",outputFile);
    

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
	
	
	
	printf("Program documantation\n\n");
	
	while(fqueue->start != NULL){
	
		newname = peek(fqueue);
		
		print_module(newname);
		
		findFiles(fqueue, newname);
	
		findComments(queue, newname);
			
		printComments(queue);
		
		freeQueue(queue);
		
	}
	
	
	
 	
    /* Uvolnění paměti */
    free(inputFile);
    free(outputFile);
    freeQueue(queue);
    freeFileQueue(fqueue);
   

    return 0;
}