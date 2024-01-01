/* ccdoc.c main */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>



#include "filequeue.h"
#include "comment.h"
#include "check.h"
#include "modifier.h"



#define LINE_LEN 1024


/**
 * Funkce pro vypsani modulu
 */
void print_module(char *module) {
	char *name = strrchr(module, '\\');
	
	if(name){
		printf("Module: %s \n\n", name+1);
	}
	else{
		printf("Module: %s \n\n", module);	
	}
	
	
	
}

void findFiles(fileQueue *fqueue, fileQueue *usedFiles, char *filename){
	const char *include_prefix = "#include ";
	char *inc;
	char *file_s;
	char *file_e1;
	char *file_e2;
	
	char *final;
	
	const char *ex1 = ".c";
	const char *ex2 = ".h";
	const char prefix_file = '"';
	char *dotC_file;
	char *full_path;

	
	char line[LINE_LEN];
	
	FILE *file = fopen(filename, "r");
	
	if(file == NULL){
		printf("soubor neexistuje");
		exit(2);
	}
	
	char *path = extract_path(filename);
	
	
	
	while(fgets(line, sizeof(line), file)){
		inc = strstr(line, include_prefix);
		if(inc){
			file_s = strchr(inc, prefix_file);
			if(file_s){
				file_e1 = strstr(file_s, ex1);
				file_e2 = strstr(file_s, ex2);
				if(file_e1 || file_e2){
					
					
					
					
					final = removeQuotes(file_s);
					
					if(path){
						full_path = connect_path(path, final);
	                    if (is_file_set(usedFiles, full_path) == 0) {
	                        addFilename(fqueue, full_path);
	                        addFilename(usedFiles, full_path);
	                        free(full_path);   
	                    }	
					} else {
						if (is_file_set(usedFiles, final) == 0) {
	                        addFilename(fqueue, final);
	                        addFilename(usedFiles, final);
	                    }
					}
					
				
					
					
                    
                    if(file_e2){
                    	
                    	
                    	
                    	dotC_file = (char *) malloc(strlen(final));
                    	
                    	if(!dotC_file){
                    		printf("failed to alocated the memory");
                    		exit(2);
						}
						
						
						
						strncpy(dotC_file, final, strlen(final) - 1);
						
						dotC_file[strlen(final)-2] = '\0';
						
						strcat(dotC_file, ex1);
						
						
						
						
						if(path){
							full_path = connect_path(path, dotC_file);
							if (is_file_set(usedFiles, full_path) == 0 && is_file_exist(full_path)) {
		                        addFilename(fqueue, full_path);
		                        addFilename(usedFiles, full_path);
		                        free(full_path);
	                    	}
						}else {
							if (is_file_set(usedFiles, dotC_file) == 0 && is_file_exist(dotC_file)) {
		                        addFilename(fqueue, dotC_file);
		                        addFilename(usedFiles, dotC_file);
		                        
		                    }
						}
						
						
						}
	
	                      
					}
				}
			}
			
		}
	
	free(path);
	fclose(file);	
}


/**
 * @brief najde komentare.
 *
 * Funkce pro nacteni souboru a zpracovani
 * komentaru a kokotu
 *
 * @param char *filename jmeno souboru.
 * @return void nic.
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
        	add(queue, commentBuffer);
		}
        
    }

    fclose(file);
}

/**
 * main kokotpica
 *
 * @param int argc pocet argumentu.
 * @param char *argv[] pole argumentu
 *
 * @author \ textcopyright{} Jan Naj
 * @version 1.0
 */
int main(int argc, char *argv[]) {
	char *inputFile = argv[1];	
    char *outputFile = NULL;
    
	const char *ex1 = ".c";
    char *dotC = strstr(inputFile,ex1);
    const char *ex2 = ".h";
    char *dotH = strstr(inputFile,ex2);

    char *texextension = "-doc.tex";
    
    char *dotC_file;
    
    int inputLen;
    char *dotPosition;
    
    commentQueue *queue;
    fileQueue *fqueue;
    fileQueue *usedFiles;
    char *newname;
    char *nextname;
    
    
	
	
	
    /* Zpracování příkazové řádky */
    if (argc < 2) {
    	
        
        printf("Chyba: Nebyl zadan vstupni soubor.\n");
        
        
        
        exit(1);  /* Návratový kód 1 pro chybný vstup */
    }
     
    if(!dotC && !dotH){
    	printf("Chyba: spatna pripona souboru \n");
    	exit(1);
	}
	
	
    

	
    if (argc == 3) {
    	outputFile = argv[2];
	} else {
		
		dotPosition = strrchr(inputFile, '.');
	
		
		char *path = extract_path(inputFile);
		char *lastslash;

		if(path){
			lastslash = strrchr(inputFile, '\\') + 1;
			inputLen = strlen(lastslash);	
		} else{
			inputLen = strlen(inputFile);
		}
		
	
		
	    if (dotPosition != NULL) {
	   
	    	
	        outputFile = (char *)malloc(inputLen + strlen(texextension) + 1);  
	        
	        if (outputFile == NULL) {
	            printf("Chyba: Nepodarilo se alokovat pamat pro vystupni soubor.\n");
	            exit(EXIT_FAILURE);
	        }
	        
	    	
	
	        
	        if(path){
	        	strncpy(outputFile, lastslash, inputLen - 2);
	        	outputFile[inputLen - 2] = '\0';
	        	strcat(outputFile, texextension);
	        	outputFile = connect_path(path, outputFile);
			}
			else{
				strncpy(outputFile, inputFile, inputLen - 2);
				outputFile[inputLen - 2] = '\0';
				strcat(outputFile, texextension);	
			}
			
	 
	        
	    } else {
	        printf("Chyba: Nebyla rozpoznána pripona vstupniho souboru.\n");
	        exit(EXIT_FAILURE);
	    }
	}

    
	printf("%s\n",inputFile);
	printf("%s\n",outputFile);
	
	
  

	/* alocation memory for comqueue */
    queue = (commentQueue *) malloc(sizeof(commentQueue));
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
    
    usedFiles = (fileQueue *) malloc(sizeof(fileQueue));
     if (fqueue == NULL) {
        printf("Chyba: Nepodarilo se alokovat pamat pro frontu komentaru.\n");
        exit(EXIT_FAILURE);
    }
    
    initializeFileQueue(usedFiles);
    
    addFilename(fqueue, inputFile);
	addFilename(usedFiles, inputFile);
    
    if(dotH) {
    	dotC_file = (char *) malloc(strlen(inputFile));
                    	
        if(!dotC_file){
            printf("failed to alocated the memory");
            exit(2);
		}
						
		strncpy(dotC_file, inputFile, strlen(inputFile) - 1);
		dotC_file[strlen(inputFile) - 2] = '\0';
		strcat(dotC_file, ex1);
		
		
		if (is_file_set(usedFiles, dotC_file) == 0 && is_file_exist(dotC_file)) {
 	       	addFilename(fqueue, dotC_file);
		    addFilename(usedFiles, dotC_file);
		}
		
	}
    
	
		
	printf("Program documantation\n\n");
	
	while(fqueue->start != NULL){
		
		/*
		printFileQueue(fqueue);
		*/
		newname = peek(fqueue);
	
		
		/*
		printf("pouzite soubory");
		printFileQueue(usedFiles);
		*/
		
		   
	
		
		
		
		findFiles(fqueue, usedFiles, newname);
		
	
		if (fqueue->start != NULL){
			
		
			
			if(strcmp(extractExtension(newname), extractExtension(fqueue->start->name)) == 0){
				
				findComments(queue, newname);
				
				nextname = peek(fqueue);
				
				findComments(queue, nextname);
				
				print_module(extractExtension(newname));    
				
				processComments(queue);
				   
				mergeComments(queue);
				
				printComments(queue);
				
				freeQueue(queue);
			}
			else{
				
				print_module(newname);
				findComments(queue, newname);
				processComments(queue);
				printComments(queue);
				freeQueue(queue);
				
			}
		}
			
		
		
		
		
	}
	
	
	
 	
    /* Uvolnění paměti */
    free(inputFile);
    free(outputFile);
    freeFileQueue(fqueue);
    freeFileQueue(usedFiles);
   
   	printf("hotovo");
    return 0;
}



