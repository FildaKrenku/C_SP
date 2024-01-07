/* ccdoc.c main */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



#include "filequeue.h"
#include "comment.h"
#include "check.h"
#include "modifier.h"
#include "printer.h"



#define LINE_LEN 1024
#define EX1 ".c"
#define EX2 ".h"
#define EX3 ".tex"
#define TEX_EX "-doc.tex"
#define PREFIX_FILE '"'
#define PREFIX_INCLUDE "#include"





void findFiles(fileQueue *fqueue, fileQueue *usedFiles, char *filename) {
	
	char *inc;
	char *file_s;
	char *file_e1;
	char *file_e2;
	
	char *final;
	char *dotC_file;
	char *full_path;
	char *path;
	
	char line[LINE_LEN];
	
	/* argument check */
	if( !fqueue || !usedFiles || !filename) {
		printf("Wrong arguments\n");
		exit(EXIT_FAILURE);
	}
	
	/* open file check */
	FILE *file = fopen(filename, "r");
	
	if (file == NULL) {
		printf("File does not exists %s\n", filename);
		exit(2);
	}
	

	/* iterating through file and finding includes and then once a .h file is find .c file is made from it*/
	while (fgets(line, sizeof(line), file)) {
		inc = strstr(line, PREFIX_INCLUDE); /* include found */
		if (inc) {
			file_s = strchr(inc, PREFIX_FILE); /* quotes found */
			if (file_s){
				file_e1 = strstr(file_s, EX1);
				file_e2 = strstr(file_s, EX2);
				if (file_e1 || file_e2) { 
					
					
					
					
					final = removeQuotes(file_s); /* removing quotes from filename */
					
					/* extracting path from filename and if paht is not null then connet it to founded file and checking if file exist*/
					if (final) {
						path = extract_path(filename);
						if (path) {
						full_path = connect_path(path, final);
		                    if (is_file_set(usedFiles, full_path) == 0 && is_file_exist(full_path) == 1) {
		                        addFilename(fqueue, full_path);
		                        addFilename(usedFiles, full_path);
		                         
		                    }
							free(full_path);  	
						} else {
							if (is_file_set(usedFiles, final) == 0 && is_file_exist(final) == 1) {
		                        addFilename(fqueue, final);
		                        addFilename(usedFiles, final);
		                    }
						}
					}
					
					
					
				
					
					
                    /* creating of .c file from .h file */
                    if(file_e2){
                    	
                    	
                    	
                    	dotC_file = (char *) malloc(strlen(final) + 1);
                    	
                    	if (!dotC_file) {
                    		printf("Failed to alocated the memory for file");
                    		exit(2);
						}
						
						
						
						strncpy(dotC_file, final, strlen(final) - 2);
						dotC_file[strlen(final) - 2] = '\0';
						strcat(dotC_file, EX1);
						dotC_file[strlen(final)] = '\0';
						
						free(final);
						
						/* same like with the .h file */
						if (path) {
							full_path = connect_path(path, dotC_file);
							if (is_file_set(usedFiles, full_path) == 0 && is_file_exist(full_path) == 1) {
		                        addFilename(fqueue, full_path);
		                        addFilename(usedFiles, full_path);
		                        
	                    	}
	                    	free(full_path);
						} else {
							if (is_file_set(usedFiles, dotC_file) == 0 && is_file_exist(dotC_file) == 1) {
		                        addFilename(fqueue, dotC_file);
		                        addFilename(usedFiles, dotC_file);
		                        
		                    }
						}	
						free(dotC_file); 
											
					} 
				free(path); 
				}
			}
		}	
	}
	
	
	/* file closing*/
	fclose(file);
	
	

	
}


/**
 * @brief najde komentare.
 *
 * Funkce pro nacteni souboru a zpracovani
 * komentaru a kokotu
 *
 * @param commentQueue *queue fronta souboru
 * @param char * filename jmeno souboru.
 * @return void nic.
 */
void findComments(commentQueue *queue, char *filename) {
	char line[LINE_LEN];
    char commentBuffer[5 * LINE_LEN];
    int insideComment = 0;
    int store_last = 0;
	
	
	/* argument check */
	if (!queue || !filename) {
		printf("Wrong arguments of findComments");
		exit(EXIT_FAILURE);
	}
	
	/* open file check */
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Can not open the inpitfile %s.\n", filename);
        exit(2);  
    }

    
	/* iterating through file and finding comments */
    while (fgets(line, sizeof(line), file)) {
    	
    	
    	
        /* finding of comments */
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
	
	/* closing of file */
    fclose(file);
}







/**
 * main function of the program
 *
 * @param int argc pocet argumentu
 * @param char * argv[] pole argumentu.
 *
 * @author \textcopyright{} Filip Křenek
 * @version 1.0
 */
int main(int argc, char *argv[]) {
	char *inputFile = NULL;	
    char *outputFile = NULL;
    FILE *tex_file;
    
    
    char *dotC; 
    char *dotH;
    char *dotTex;
    
    char *dotC_file;
    
    int inputLen;
    char *lastslash = NULL;
    char *lastbslash = NULL;
    char *dotPosition;
    char *path;
    
    commentQueue *queue;
    fileQueue *fqueue;
    fileQueue *usedFiles;
    char *newname;
    char *nextname;
    
    char *file_we1;
	char *file_we2;	
    
    int exit_code = 0;
	int cur_exit = 0;

	
    /* inputfile handling */
    if (argc < 2) {
        printf("Inputfile in missing.\n");
        exit(1);  
    }
    else{
    	inputFile = argv[1];
	}
    
    dotC = strstr(inputFile,EX1);
    dotH = strstr(inputFile,EX2);
     
    /* checking for .c or .h ending */
    if(!dotC && !dotH){
    	printf("Wrong extension of the Inputfile\n");
    	exit(1);
	}
	
	/* checking file existantace */
	if(is_file_exist(inputFile) == 0){
		printf("Inputfile does not exists\n");
		exit(2);
	}
    

	/* outputfile handling */
    if (argc == 3) {
    	outputFile = argv[2];
    	
    	dotTex = strstr(outputFile, EX3);
    	/* checking for .tex ending  */
    	if(!dotTex){
    		printf("Wrong extension of the Outputfile\n");
    		exit(2);
		}	
	} else {
		/* makeing -doc.tex file */
		dotPosition = strrchr(inputFile, '.');
	
		path = extract_path(inputFile);
		
	

		if(path){
			lastslash = strrchr(inputFile, '/') + 1;
			lastbslash = strrchr(inputFile, '\\') + 1;
			
			
		
			
			
			if (lastbslash) {
			
				inputLen = strlen(lastbslash);	
			}
			else if (lastslash) {
				
				inputLen = strlen(lastslash);	
				
			}
	
		} else{
			inputLen = strlen(inputFile);
		}
		
	
		
	    if (dotPosition != NULL) {
	   
	    	
	        outputFile = (char *)malloc(inputLen + strlen(TEX_EX) + 1);  
	        
	        if (outputFile == NULL) {
	            printf("Failed to alocate memory for file\n");
	            exit(EXIT_FAILURE);
	        }
	        
	    	
	
	        
	        if (path) {
	        	if (lastbslash) {
	        		strncpy(outputFile, lastbslash, inputLen - 2);	
				}
				else if (lastslash) {
					strncpy(outputFile, lastslash, inputLen - 2);	
				}
	        	
	        	outputFile[inputLen - 2] = '\0';
	        	strcat(outputFile, TEX_EX);
	        	outputFile = connect_path(path, outputFile);
	        
			}
			else{
				strncpy(outputFile, inputFile, inputLen - 2);
				outputFile[inputLen - 2] = '\0';
				strcat(outputFile, TEX_EX);	
			}
			
	 
	        
	    } else {
	        printf("Wrong extension of InputFile\n");
	        exit(EXIT_FAILURE);
	    }
	    
	    free(path);
	}


	
	
  

	/* alocation memory for comqueue */
    queue = (commentQueue *) malloc(sizeof(commentQueue));
    if (queue == NULL) {
        printf("Failed to alocate memory for Comment queue\n");
        exit(EXIT_FAILURE);
    }
    
    initializeQueue(queue);
    
    /* alocation memory for filenamequeue */
    fqueue = (fileQueue *) malloc(sizeof(fileQueue));
     if (fqueue == NULL) {
        printf("Failed to alocate memory for File queue\n");
        exit(EXIT_FAILURE);
    }
    
    initializeFileQueue(fqueue);
    
    /* alocation memory for filenamequeue to save used files */
    usedFiles = (fileQueue *) malloc(sizeof(fileQueue));
     if (usedFiles == NULL) {
        printf("Failed to alocate memory for UsedFiles queue\n");
        exit(EXIT_FAILURE);
    }
    
    initializeFileQueue(usedFiles);
    
    /* add inputfile to both queues */
    addFilename(fqueue, inputFile);
	addFilename(usedFiles, inputFile);
	
    
    /* if first file is header, find .c file to it */
    if (dotH) {
    	dotC_file = (char *) malloc(strlen(inputFile));
                    	
        if (!dotC_file){
            printf("Failed to alocated the memory");
            exit(EXIT_FAILURE);
		}
						
		strncpy(dotC_file, inputFile, strlen(inputFile) - 1);
		dotC_file[strlen(inputFile) - 2] = '\0';
		strcat(dotC_file, EX1);
		
		
		if (is_file_set(usedFiles, dotC_file) == 0 && is_file_exist(dotC_file)) {
 	       	addFilename(fqueue, dotC_file);
		    addFilename(usedFiles, dotC_file);
		}
		else {
			free(dotC_file);	
		}
		
		
	}
    
    /* tex file open check */
    tex_file = fopen(outputFile, "w");
    
    if(!tex_file){
    	printf("Faile to open tex file\n");
    	exit(2);
	}
	
	/* initial print */
	print_section(tex_file);	
	
	/* iterating through filequeue */
	while (fqueue->start != NULL) {
		
		/* peek first filename and find files in that file */
		newname = peek(fqueue);
			
		findFiles(fqueue, usedFiles, newname);
		
		/* checking if next filename has same name  */
		if (fqueue->start != NULL) {
			
			file_we1 = extractExtension(newname);
			file_we2 = extractExtension(fqueue->start->name);
			
		
			/* if yes peek that file and merge comments of both files */
			if(strcmp(file_we1, file_we2) == 0) {
			
				findComments(queue, newname);
				
				nextname = peek(fqueue);
			
				findComments(queue, nextname);
				
				print_module(tex_file, file_we1);    
				
				processComments(queue);
				
				mergeComments(queue);
				
				cur_exit = printComments(tex_file, queue);
			
				freeQueue(queue);
				
				free(nextname);
				free(newname);
				
			} /* if not normally find comments and print them */
			else {
				
				print_module(tex_file, newname);
			
				findComments(queue, newname);
			
				processComments(queue);
		
				cur_exit = printComments(tex_file, queue);
			
				freeQueue(queue);
			
				free(newname);
			
			}
		} /* normally find comments and print them */
		else {
			print_module(tex_file, newname);
			
			findComments(queue, newname);
		
			processComments(queue);
		
			cur_exit = printComments(tex_file, queue);
		
			freeQueue(queue);
		
			free(newname);
		}
		
		if (exit_code <= cur_exit) {
			exit_code = cur_exit;
		}
		
	}
	
	
	/* final print to the tex file */
	print_end(tex_file);
	
	/* close of the tex file */ 
	fclose(tex_file);
	
	
	
	/* freeing memory */
	if(argc == 2) {
		free(outputFile);	
	}
	
	if (dotH) { 
		free(dotC_file);	
	}	
	
   
    
    freeFileQueue(fqueue);
    freeFileQueue(usedFiles);
  	free(queue);
  	free(fqueue);
  	free(usedFiles);

   	printf("hotovo");
    return exit_code;
}



