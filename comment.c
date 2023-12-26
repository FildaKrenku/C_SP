/* comment.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comment.h"



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

/* Výpis komentářů ve frontě */
void printComments(commentQueue *queue) {
	
    comment *current = queue->start;
    while (current != NULL) {
    	
    	process(current);
		printf("\n");
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
        free(current);
        current = next;
    }
    /* Nastavení fronty na prázdnou */
    initializeQueue(queue);
}


void process(comment *currnet){
	
	char *text = currnet->text;
	
	char *copy = (char *)malloc(strlen(text)+1);
	
	if (copy == NULL) {
        printf("Chyba při alokaci paměti.\n");
        exit(EXIT_FAILURE);
    }
	 copy[strlen(text)] = '\0';

 	strncpy(copy, text, strlen(text));
	
	
	char *line = strtok(copy, "\n");

   
    while (line != NULL) {
     
	char *zav = strchr(line, '@');
     
        if(zav){
        	char *space = strchr(zav, ' ');
        	
        	if(strstr(zav,"param")){
        		if(currnet->param = (char *) malloc(strlen(space)+1)){
        			strncpy(currnet->param, space, strlen(space));
        			currnet->param[strlen(space)] = '\0';
        			printf("%s\n", currnet->param);
				}
        		
			} else if(strstr(zav,"details")){
				if(currnet->details = (char *) malloc(strlen(space)+1)){
        			strncpy(currnet->details, space, strlen(space));
        			currnet->details[strlen(space)] = '\0';
        			printf("%s\n", currnet->details);
				}
				
			} else if(strstr(zav,"brief")){
				if(currnet->brief = (char *) malloc(strlen(space)+1)){
        			strncpy(currnet->brief, space, strlen(space));
        			currnet->brief[strlen(space)] = '\0';
        			printf("%s\n", currnet->brief);
				}
				
			} else if(strstr(zav,"return")){
				if(currnet->retun_val = (char *) malloc(strlen(space)+1)){
        			strncpy(currnet->retun_val, space, strlen(space));
        			currnet->retun_val[strlen(space)] = '\0';
        			printf("%s\n", currnet->retun_val);
				}
				
			} else if(strstr(zav,"author")){
				if(currnet->author = (char *) malloc(strlen(space)+1)){
        			strncpy(currnet->author, space, strlen(space));
        			currnet->author[strlen(space)] = '\0';
        			printf("%s\n", currnet->author);
				}
				
			} else if(strstr(zav,"version")){
				if(currnet->version = (char *) malloc(strlen(space)+1)){
        			strncpy(currnet->version, space, strlen(space));
        			currnet->version[strlen(space)] = '\0';
        			printf("%s\n", currnet->version);
				}
				
			}
        	
        	
		}
	     		
     
     	/*
        printf("%s\n", line);
		*/
      
        line = strtok(NULL, "\n");
    }
	
	
	
	
	
}




