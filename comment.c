/* comment.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comment.h"
#include "check.h"
#include "modifier.h"
#include "printer.h"

#define ARGUMENTY "Argumenty: "
#define RET "Návratová Hodnota: "
#define POPIS "Popis: "
#define AUTOR "Autor: "
#define VERZE "Verze: "
#define BRIEF "Brief: "
#define DET "Detaily: "
#define FUNC "Funkce "
#define STRUCT "Struktura "



/**
 * kokot
 */
void initializeQueue(commentQueue *queue) {
	if(!queue) {
		printf("wrong arguments");
		exit(EXIT_FAILURE);
	}
	
    queue->start = NULL;
    queue->end = NULL;
}


/**
 * kokot
 *
 * @param char *text kokot
 * @param commentQueue *queue fronta
 */
void add(commentQueue *queue, char textt[]) {
	if(!queue || !textt){
		printf("wrong arguments\n");
		exit(EXIT_FAILURE);
	}
	
	
    comment *newComment = (comment *)malloc(sizeof(comment));
    
    if (newComment == NULL) {
        printf("Chyba: Nepodarilo se alokovat pamat pro komentar.\n");
        exit(EXIT_FAILURE);
    }
    
    newComment->text = NULL;
    newComment->author = NULL;
    newComment->param = NULL;
    newComment->brief = NULL;
    newComment->description = NULL;
    newComment->details = NULL;
    newComment->head = NULL;
    newComment->struct_head = NULL;
    newComment->return_val = NULL;
    newComment->version = NULL;
    
    newComment->next = NULL;
    

    /* Kopírování textu komentáře do nově alokované paměti */
    newComment->text = strdup(textt);
    if (newComment->text == NULL) {
	    printf("Error: Failed to allocate memory for comment text.\n");
	    free(newComment);
	    exit(EXIT_FAILURE);
    }

    


    /* Pokud je fronta prázdná, nastavíme frontu tak, aby obsahovala pouze nový komentář */
    if (queue->end == NULL) {
        queue->start = newComment;
        queue->end = newComment;
    } else {
        /* Jinak přidáme komentář na konec fronty */
        queue->end->next = newComment;
        queue->end = newComment;
    }
    
  
}


void processComments(commentQueue *queue) {
	
	if(!queue){
		printf("wrong argument");
		exit(EXIT_FAILURE);
	}
	
	comment *current = queue->start;
    while (current != NULL) {
		process(current);
		
		current = current->next;
		
	}

}



void printComments(FILE *file, commentQueue *queue) {
    comment *current = queue->start;
    
    paramLine *par;
    returnLine *ret;
    
    while (current != NULL) {
    	
    	if(current->struct_head != NULL){
    		print_subsubsection(file, "Struktura: ",current->struct_head);
    		/*
    		printf("STRUKTURA: %s\n",current->struct_head);
    		*/		
		}
    
 
		if(current->head != NULL){
			print_subsubsection(file, FUNC, current->head);
			printf("FUNKCE: %s\n",current->head);
			
			if(current->param != NULL) {
				par = current->param;
				printf("ARGUMENTY:");
				fprintf(file, "\\textbf{%s}", ARGUMENTY);
    			while (par != NULL) {
    				printf("%s", par->line);
    				
    				printf_verb(file, par->line);
    				
        			par = par->next;
    			}
    			fprintf(file, "\\\\\n");
    			print_space(file);
    			printf("\n");
			}
			if(current->return_val != NULL){
				ret = current->return_val;
				/*
				fprintf(file, "\\textbf{%s}", RET);
				printf_verb(file, current->return_val);
				fprintf(file, "\\\\\n");
    			print_space(file);
    			*/
				printf("RETURN:");
					while (ret != NULL) {
    				
    				printf("%s", ret->line);
    				/*
    				printf_verb(file, ret->line);
    				*/
        			ret = ret->next;
    			}
    			printf("\n");
			}
			if(current->description != NULL){
				print_textbf(file, POPIS, current->description);
				print_space(file);
				
				printf("POPIS: %s\n",current->description);
			}
			if(current->brief != NULL){
				print_textbf(file, BRIEF, current->brief);
				print_space(file);
				
				printf("Brief:%s\n",current->brief);	
			}
			if(current->details != NULL){
				print_textbf(file, DET, current->details);
				print_space(file);
				
				printf("Version:%s\n",current->details);	
			}
			if(current->author != NULL){
				print_textbf(file, AUTOR, current->author);
				print_space(file);
				printf("Autor:%s\n",current->author);	
			}
			if(current->version != NULL){
				print_textbf(file, VERZE, current->version);
				print_space(file);
				printf("Version:%s\n",current->version);	
			}
			
			printf("\n");
		}
		
	
        current = current->next;
    }
    
}


/* Uvolnění paměti použité pro komentáře ve frontě */
void freeQueue(commentQueue *queue) {
    comment *current = queue->start;
    comment *next;
    paramLine *par;
    paramLine *next_par;
    returnLine *ret;
    returnLine *next_ret;
    
    while (current != NULL) {
    	
        next = current->next;
    	
       	
       	par = current->param;
    	while (par != NULL) {
        	next_par = par->next;
        	free(par->line);
        	free(par);
        	par = next_par;
    	}
    
    	ret = current->return_val;
    	while (ret != NULL) {
        	next_ret = ret->next;
        	free(ret->line);
        	free(ret);
        	ret = next_ret;
    	}
    	
    	free(current->brief);
    	free(current->version);
    	free(current->details);
    	free(current->author);
    	free(current->description);	
       	free(current->struct_head);
       	free(current->head);
       	free(current->text);
       	
       	
    	
    	
    	
    	
    	
    	
        
        free(current);
        
      
        
        current = next;
        
    }
    /* Nastavení fronty na prázdnou */
    
    initializeQueue(queue);
    
}




/**
 * process com
 */
void process(comment *current) {
	
	int dest = 0;

	
	if (!current || !current->text) {
		printf("wrong argument");
		exit(EXIT_FAILURE);
	}
	

	
	char* copy = strdup(current->text);
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed for copy.\n");
        exit(EXIT_FAILURE);
    }
 	

	char *line = strtok(copy, "\n");
	
  	
    while (line != NULL) {
    	/*
    	printf("%s\n",line);
    	*/
    	
 		
		char *zav = strchr(line, '@');

		char *func_head = strstr(line, ") {");
		char *struct_head = strstr(line, "typedef struct ");
		char *H_file_head = strstr(line, ");");
	
     
        if (zav != NULL) {
        	char *space = strchr(zav, ' ');
        	
        	if (strstr(zav, "param")) {
        		add_param(current, space);
			} else if (strstr(zav,"details")) {
				current->details = (char *) malloc(strlen(space) + 1);
				if(current->details) {
        			strncpy(current->details, space, strlen(space));
        			current->details[strlen(space)] = '\0';
				} else {
					printf("memory alocation failed\n");
					exit(EXIT_FAILURE);
				}
			} else if (strstr(zav,"brief")) {
				current->brief = (char *) malloc(strlen(space) + 1);
				if(current->brief) {
        			strncpy(current->brief, space, strlen(space));
        			current->brief[strlen(space)] = '\0';
				}
				else {
					printf("memory alocation failed\n");
					exit(EXIT_FAILURE);
				}
			} else if (strstr(zav,"return")) {
				add_return(current, space);
			} else if (strstr(zav,"author")) {
				current->author = (char *) malloc(strlen(space) + 1);
				if(current->author) {
        			strncpy(current->author, space, strlen(space));
        			current->author[strlen(space)] = '\0';	
				}
				else {
					printf("memory alocation failed\n");
					exit(EXIT_FAILURE);
				}
			} else if (strstr(zav,"version")) {
				current->version = (char *) malloc(strlen(space) + 1);
				if(current->version) {
        			strncpy(current->version, space, strlen(space));
        			current->version[strlen(space)] = '\0';	
				}
				else {
					printf("memory alocation failed\n");
					exit(EXIT_FAILURE);
				}
			}
		} else if (func_head != NULL) {
			
			current->head = (char *) malloc(strlen(trim_white_spaces(line)) - 1);
			if(current->head) {
				strncpy(current->head, trim_white_spaces(line), strlen(trim_white_spaces(line)) - 1);
				current->head[strlen(trim_white_spaces(line)) - 2] = '\0';
			}
			else {
				printf("memory alocation failed\n");
				exit(EXIT_FAILURE);
			}
				
		} else if (struct_head != NULL) {
			current->struct_head = (char *) malloc(strlen(struct_head + 15) - 1);
			if(current->struct_head) {
				strncpy(current->struct_head, trim_white_spaces(struct_head + 15), strlen(struct_head + 15) - 1);
				current->struct_head[strlen(struct_head + 15) - 1] = '\0';
			}
			else {
				printf("memory alocation failed\n");
				exit(EXIT_FAILURE);
			}	
			
		} else if (H_file_head != NULL) {
			current->head = (char *) malloc(strlen(trim_white_spaces(line)) - 1);
			if(current->head) {
				strncpy(current->head, trim_white_spaces(line), strlen(trim_white_spaces(line)) - 1);
				current->head[strlen(trim_white_spaces(line)) - 1] = '\0';
			}	
			else {
				printf("memory alocation failed\n");
				exit(EXIT_FAILURE);
			}
		} else if (linecheck(line, " *") || linecheck(line, "/**") || linecheck(line, "/*!")) {
			dest = 1;  
		} else if (dest == 1 && !linecheck(line, " *")) {
			char *d = strstr(line," * ");
			if (d != NULL) {
					
				
				remove_spaces(d);
				
				
			
				int currentLength = current->description ? strlen(current->description) : 0;
    			int newLength = currentLength + strlen(d) + 2;
	
		        if (current->description != NULL) {
		        	current->description = (char *)realloc(current->description, newLength);
		        	if (current->description != NULL) {
		        		strcat(current->description, " ");
		        		strcat(current->description, d);
		        		current->description[newLength - 1] = '\0';
					}
					else {
						printf("Memory reallocation for description failed.\n");
		            	exit(EXIT_FAILURE);
					}
		        } else {
		        	current->description = (char *)malloc(newLength);
		        	if (current->description) {
		        		strcpy(current->description, d);
		        		current->description[newLength - 1] = '\0';
					}
					else {
						printf("Memory allocation for description failed.\n");
		            	exit(EXIT_FAILURE);
					}
		           
				}
			
				
				
				
			}
		} 
			
        line = strtok(NULL, "\n"); 
          
	}
	
	
	
	free(copy);

	
}



void mergeComments(commentQueue *queue) {
	
    comment *current = queue->start;
    comment *prev;
    comment *compare;
    paramLine *par;
    paramLine *par_line;
    paramLine *next_par;
    
    returnLine *ret;
    returnLine *ret_line;
    returnLine *next_ret;


    while (current != NULL) {
    	
    	compare = current->next;
    	prev = current;
    	
        while (compare != NULL) {
        	
        
	        
	        /* Iterate through each field of the comments and merge if different */
	        if (current->head != NULL && compare->head != NULL && strcmp(current->head, compare->head) == 0) {
	        	
	        		/*
	        		printf(" cur %s com %s \n",current->head, compare->head);
	        		printf(" cur %i com %i \n",strlen(current->head), strlen(compare->head));
	        		*/
	             if (compare->description != NULL) {
	                if (current->description == NULL) {
	                    current->description = strdup(compare->description);
	                } else {
	                	if(strcmp(current->description, compare->description) != 0){
	                		current->description = (char *)realloc(current->description, strlen(current->description) + strlen(compare->description) + 1);
	                		
	                		if(current->description != NULL){
	                			strcat(current->description, " ");
	                    		strcat(current->description, compare->description);	
							}
							else{
								printf("realokace pameti selhala");
								exit(EXIT_FAILURE);
							}	
						}
	                }
	            }
	            if (compare->author != NULL) {
	                if (current->author == NULL) {
	                    current->author = strdup(compare->author);
	                } else {
	                	if(strcmp(current->author, compare->author) != 0){
	                		current->author = (char *)realloc(current->author, strlen(current->author) + strlen(compare->author) + 1);
	                		
	                		if(current->author != NULL){
	                			strcat(current->author, " ");
	                    		strcat(current->author, compare->author);	
							}
							else{
								printf("realokace pameti selhala");
								exit(EXIT_FAILURE);
							}	
						}
	                }
	            }
	            
	            if (compare->param != NULL) {
	            	if (current->param == NULL) {
	            		par = compare->param;
				    	while (par != NULL) {
				        	add_param(current, par->line);
				        	par = par->next;
				    	}
	                } 
					else {
	                	paramLine *cur_par; 
	                	paramLine *com_par = compare->param;
	                	
	                	while (com_par != NULL) {
	                		cur_par = current->param;
				        	int found = 0; 
				
					        while (cur_par != NULL) {
					            if (strcmp(cur_par->line, com_par->line) == 0) {
					                found = 1; /* Parametr byl nalezen v current */
					                break;
					            }
					
					            cur_par = cur_par->next;
					        }
				
					        /* Pokud parametr nebyl nalezen v current, přidáme ho */
					        if (found == 0) {
					            add_param(current, com_par->line);
					        }
					
					        com_par = com_par->next;
    					}
							
	                }  
	            }
	            
	            if (compare->details != NULL) {
	                if (current->details == NULL) {
	                    current->details = strdup(compare->details);
	                } else {
	                	if(strcmp(current->details, compare->details) != 0){
	                		current->details = (char *)realloc(current->details, strlen(current->details) + strlen(compare->details) + 1);
	                		
	                		if(current->details != NULL){
	                			strcat(current->details, " ");
	                    		strcat(current->details, compare->details);	
							}
							else{
								printf("realokace pameti selhala");
								exit(EXIT_FAILURE);
							}	
						}
	                }
	            }
	            
	            if (compare->return_val != NULL) {
	                if (current->return_val == NULL) {
	            		ret = compare->return_val;
				    	while (ret != NULL) {
				        	add_return(current, ret->line);
				        	ret = ret->next;
				    	}
	                } 
					else {
	                	returnLine *cur_ret; 
	                	returnLine *com_ret = compare->return_val;
	                	
	                	while (com_ret != NULL) {
	                		cur_ret = current->return_val;
				        	int found_ret = 0; 
				
					        while (cur_ret != NULL) {
					            if (strcmp(cur_ret->line, com_ret->line) == 0) {
					                found_ret = 1; 
					                break;
					            }
					
					            cur_ret = cur_ret->next;
					        }
				
					        
					        if (found_ret == 0) {
					            add_return(current, com_ret->line);
					        }
					
					        com_ret = com_ret->next;
    					}
							
	                }  
	        	}
	        	
	            if (compare->version != NULL) {
	                if (current->version == NULL) {
	                    current->version = strdup(compare->version);
	                } else {
	                	if(strcmp(current->version, compare->version) != 0){
	                		current->version = (char *)realloc(current->version, strlen(current->version) + strlen(compare->version) + 1);
	                		
	                		if(current->version != NULL){
	                			strcat(current->version, " ");
	                    		strcat(current->version, compare->version);	
							}
							else{
								printf("realokace pameti selhala");
								exit(EXIT_FAILURE);
							}	
						}
	                }
	            }
	            if (compare->brief != NULL) {
	                if (current->brief == NULL) {
	                    current->brief = strdup(compare->brief);
	                } else {
	                	if(strcmp(current->brief, compare->brief) != 0){
	                		current->brief = (char *)realloc(current->brief, strlen(current->brief) + strlen(compare->brief) + 1);
	                		
	                		if(current->brief != NULL){
	                			strcat(current->brief, " ");
	                    		strcat(current->brief, compare->brief);	
							}
							else{
								printf("realokace pameti selhala");
								exit(EXIT_FAILURE);
							}	
						}
	                }
	            }
	            
	          	comment *temp = compare->next;
				prev->next = temp;
				
				

                /* Free the memory of the merged comment */
		    	par_line = compare->param;
		    	while (par_line != NULL) {
		        	next_par = par_line->next;
		        	free(par_line->line);
		        	free(par_line);
		        	par_line = next_par;
		    	}
		    
		    	ret_line = compare->return_val;
		    	while (ret_line != NULL) {
		        	next_ret = ret_line->next;
		        	free(ret_line->line);
		        	free(ret_line);
		        	ret_line = next_ret;
		    	}
		    	
		    	free(compare->brief);
		    	free(compare->version);
		    	free(compare->details);
		    	free(compare->author);
		    	free(compare->description);	
		       	free(compare->struct_head);
		       	free(compare->head);
		       	free(compare->text);
		    	
		    	
                
                free(compare);
                
                compare = temp;
	
				
	         
	            
	            
	        } 
			else {
				prev = compare;
	          	compare = compare->next;
	        }
        }
        
    	current = current->next;
    }
}

void add_param(comment *current, const char *line) {
	paramLine *newParamLine;
	
	if(!current || !line) {
		printf("Wrong arguments\n");
		exit(EXIT_FAILURE);
	}
	
	
	/* Allocate memory for the new line */
    newParamLine = malloc(sizeof(paramLine));
    if (newParamLine == NULL) {
        /* Handle memory allocation failure */
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newParamLine->line = NULL;
    newParamLine->next = NULL;

    /* Allocate memory for the new line content */
    newParamLine->line = (char *) malloc(strlen(line) + 1);
    if (newParamLine->line == NULL) {
        /* Handle memory allocation failure */
        printf("Memory allocation failed\n");
        free(newParamLine);
        exit(EXIT_FAILURE);
    }

    /* Copy the new line to the allocated memory */
    strncpy(newParamLine->line, line, strlen(line));
    newParamLine->line[strlen(line)] = '\0';

    /* Add the new line to the linked list */
    paramLine *last = current->param;
    if (last == NULL) {
        /* If the list is empty, set the newParamLine as the first element */
        current->param = newParamLine;
    } else {
        /* Otherwise, traverse to the end of the list and add the newParamLine */
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newParamLine;
    }
}


void add_return(comment *current, const char *line) {
	returnLine *newReturn;
	returnLine *last;
	
	
	if(!current || !line) {
		printf("Wrong arguments\n");
		exit(EXIT_FAILURE);
	}
	
	newReturn = malloc(sizeof(returnLine));
	
	if (newReturn == NULL) {
        /* Handle memory allocation failure */
        printf("Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    newReturn->line = NULL;
    newReturn->next = NULL;
	
	newReturn->line = (char *) malloc(strlen(line) + 1);
    if (newReturn->line == NULL) {
        /* Handle memory allocation failure */
        printf("Memory allocation failed\n");
        free(newReturn);
        exit(EXIT_FAILURE);
    }

    /* Copy the new line to the allocated memory */
    strncpy(newReturn->line, line, strlen(line));
    newReturn->line[strlen(line)] = '\0';
    
    
    /* Add the new line to the linked list */
    last = current->return_val;
    if (last == NULL) {
        /* If the list is empty, set the newParamLine as the first element */
        current->return_val = newReturn;
    } else {
        /* Otherwise, traverse to the end of the list and add the newParamLine */
        while (last->next != NULL) {
            last = last->next;
        }
        last->next = newReturn;
    }
	
	
	
	
}














