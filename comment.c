/* comment.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "comment.h"
#include "check.h"
#include "modifier.h"





/**
 * kokot
 */
void initializeQueue(commentQueue *queue) {
    queue->start = NULL;
    queue->end = NULL;
}

void add(commentQueue *queue, char  *text) {
    comment *newComment = (comment *)malloc(sizeof(comment));
    
    if (newComment == NULL) {
        printf("Chyba: Nepodarilo se alokovat pamat pro komentar.\n");
        exit(EXIT_FAILURE);
    }

    /* Kopírování textu komentáře do nově alokované paměti */
    newComment->text = strdup(text);
    
    
    newComment->author = NULL;
    newComment->param = NULL;
    newComment->brief = NULL;
    newComment->description = NULL;
    newComment->details = NULL;
    newComment->head = NULL;
    newComment->return_val = NULL;
    newComment->version = NULL;
    
    
    newComment->next = NULL;


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
	comment *current = queue->start;
    while (current != NULL) {
		process(current);
		current = current->next;
	}
}



/* Výpis komentářů ve frontě */
void printComments(commentQueue *queue) {
	
    comment *current = queue->start;
    while (current != NULL) {
    
    	
 
		if(current->head != NULL){
			printf("FUNKCE: %s\n",current->head);
			
			if(current->description != NULL){
				printf("POPIS: %s\n",current->description);
			}
			if(current->param != NULL){
				printf("PARAM:%s\n",current->param);
			}
			if(current->return_val != NULL){
				printf("Return:%s\n",current->return_val);	
			}
			if(current->brief != NULL){
				printf("Brief:%s\n",current->brief);	
			}
			if(current->author != NULL){
				printf("Autor:%s\n",current->author);	
			}
			if(current->version != NULL){
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
    while (current != NULL) {
        next = current->next;
        
        free(current->text);
       	free(current->author);
       	free(current->param);
       	free(current->brief);
       	free(current->description);
       	free(current->details);
       	free(current->head);
       	free(current->return_val);
       	free(current->version);
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
	
	char *copy = (char *)malloc(strlen(current->text) + 1);
	
	if (copy == NULL) {
        printf("Chyba při alokaci paměti.\n");
        exit(EXIT_FAILURE);
    }
    
 	strncpy(copy, current->text, strlen(current->text));
 	copy[strlen(current->text)] = '\0';
 	
 	
 
 	
 	
	
	
	 char *line = strtok(copy, "\n");
	
  	
    while (line != NULL) {
    	/*
    	printf("%s\n",line);
    	*/
    	
 		
		char *zav = strchr(line, '@');

		char *func_head = strstr(line, ") {");
		char *struct_head = strstr(line, "typedef struct");
		char *H_file_head = strstr(line, ");");
	
     
        if(zav != NULL) {
        	char *space = strchr(zav, ' ');
        	
        	if(strstr(zav, "param")) {
        		
        		int currentLength = current->param ? strlen(current->param) : 0;
        		int newLength = currentLength + strlen(space) + 1;
        		
        		
        		if(strchr(space, '.')){
        			newLength += 1;
				}
				
		        if (current->param) {
		        	current->param = (char *)realloc(current->param, newLength);
		        	current->param[currentLength + 1] = '\0';
		        	
		        } else {
		        	current->param = (char *)malloc(newLength);
		            current->param[0] = '\0';
				}
		        
		        if (current->param) {
		            /* Concatenate the content of d to the existing description */
		            strncat(current->param, space, strlen(space));
		
		            /* Ensure null-termination */
		            current->param[newLength] = '\0';
		               
		        } else {
		            printf("Memory allocation/reallocation for description failed.\n");
		            exit(EXIT_FAILURE);
		        }
				
        		
			} else if(strstr(zav,"details")) {
				if(current->details = (char *) malloc(strlen(space) + 1)) {
        			strncpy(current->details, space, strlen(space));
        			current->details[strlen(space)] = '\0';
				}
			} else if(strstr(zav,"brief")) {
				if(current->brief = (char *) malloc(strlen(space) + 1)) {
        			strncpy(current->brief, space, strlen(space));
        			current->brief[strlen(space)] = '\0';
				}
			} else if(strstr(zav,"return")) {
				if(current->return_val = (char *) malloc(strlen(space) + 1)) {
        			strncpy(current->return_val, space, strlen(space));
        			current->return_val[strlen(space)] = '\0';
				}
			} else if(strstr(zav,"author")) {
				if(current->author = (char *) malloc(strlen(space) + 1)) {
        			strncpy(current->author, space, strlen(space));
        			current->author[strlen(space)] = '\0';	
				}
			} else if(strstr(zav,"version")) {
				if(current->version = (char *) malloc(strlen(space) + 1)) {
        			strncpy(current->version, space, strlen(space));
        			current->version[strlen(space)] = '\0';	
				}
			}
        	
        	
		} else if(func_head) {
			if(current->head = (char *) malloc(strlen(line) - 1)) {
				strncpy(current->head, line, strlen(line) - 1);
				current->head[strlen(line) - 2] = '\0';
			}	
		} else if(struct_head){
			/*
			if(current->head = (char *) malloc(strlen(line) - 1)) {
				strncpy(current->head, line, strlen(line) - 1);
				current->head[strlen(line) - 1] = '\0';
			}	
			*/
		} else if(H_file_head){
			if(current->head = (char *) malloc(strlen(line) - 1)) {
				strncpy(current->head, line, strlen(line) - 1);
				current->head[strlen(line) - 1] = '\0';
			}	
		} else if(linecheck(line, " *") || linecheck(line, "/**") || linecheck(line, "/*!")){
			dest = 1;  
		} else if(dest == 1 && !linecheck(line, " *")){
			char *d = strstr(line," * ");
			if(d){
					
				remove_spaces(d);
			
				int currentLength = current->description ? strlen(current->description) : 0;
        		int newLength = currentLength + strlen(d) + 2;
		
		        if (current->description) {
		        	current->description = (char *)realloc(current->description, newLength);
		        	current->description[currentLength + 1] = '\0';
		        	current->description[currentLength] = ' ';
		        } else {
		        	current->description = (char *)malloc(newLength);
		            current->description[0] = '\0';
				}
		        
		        if (current->description) {
		            /* Concatenate the content of d to the existing description */
		            strncat(current->description, d, strlen(d));
		
		            /* Ensure null-termination */
		            current->description[newLength] = '\0';
		               
		        } else {
		            printf("Memory allocation/reallocation for description failed.\n");
		            exit(EXIT_FAILURE);
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


    while (current != NULL) {
    	
    	compare = current->next;
    	prev = current;
    	
        while (compare != NULL) {
        	
        
	        
	        /* Iterate through each field of the comments and merge if different */
	        if (current->head != NULL && compare->head != NULL && strcmp(current->head, compare->head) == 0) {
	        	
	        		
	        		printf(" cur %s com %s \n",current->head, compare->head);
	        		printf(" cur %i com %i \n",strlen(current->head), strlen(compare->head));
	        	
	        	
	        	
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
	                    strcat(current->author, " "); 
	                    strcat(current->author, compare->author);
	                }
	            }
	            if (compare->param != NULL) {
	                if (current->param == NULL) {
	                    current->param = strdup(compare->param);
	                } else {
	                    strcat(current->param, " "); 
	                    strcat(current->param, compare->param);
	                }
	            }
	            if (compare->details != NULL) {
	                if (current->details == NULL) {
	                    current->details = strdup(compare->details);
	                } else {
	                    strcat(current->details, " "); 
	                    strcat(current->details, compare->details);
	                }
	            }
	            if (compare->return_val != NULL) {
	                if (current->return_val == NULL) {
	                    current->return_val = strdup(compare->return_val);
	                } else {
	                    strcat(current->return_val, " "); 
	                    strcat(current->return_val, compare->return_val);
	                }
	        	}
	            if (compare->version != NULL) {
	                if (current->version == NULL) {
	                    current->version = strdup(compare->version);
	                } else {
	                    strcat(current->version, " ");
	                    strcat(current->version, compare->version);
	                }
	            }
	            if (compare->brief != NULL) {
	                if (current->brief == NULL) {
	                    current->brief = strdup(compare->brief);
	                } else {
	                    strcat(current->brief, " "); 
	                    strcat(current->brief, compare->brief);
	                }
	            }
	            
	          	comment *temp = compare->next;
				prev->next = temp;

                /* Free the memory of the merged comment */
                free(compare->text);
                free(compare->head);
                free(compare->description);
                free(compare->author);
                free(compare->param);
                free(compare->details);
                free(compare->return_val);
                free(compare->version);
                free(compare->brief);
                free(compare);
                
                 compare = temp;
	
				
	            /*
	            comment *temp = compare;
	
	          	free(temp->text);
	            free(temp->head);
	            free(temp->description);
	            free(temp->author);
	            free(temp->param);
	            free(temp->details);
	            free(temp->return_val);
	            free(temp->version);
	            free(temp->brief);
	            free(temp);
	            
	            current = current->next;
				compare = compare->next;
				*/
	            
	            
	        } 
			else {
				prev = compare;
	          	compare = compare->next;
	        }
        }
        
    	current = current->next;
    }
}





