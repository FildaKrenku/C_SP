/* file queue.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "filequeue.h"


void initializeFileQueue(fileQueue *queue) {
    queue->start = NULL;
	queue->end = NULL;
}

void addFilename(fileQueue *queue, char newname[]) {
	


	
    /* Allocate memory for a new file name */
    fileName *newFileName = (fileName *)malloc(sizeof(fileName));
    if (newFileName == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Copy the name into the structure */
  
    strncpy(newFileName->name, newname, strlen(newname));
    
    
    newFileName->name[strlen(newname)] = '\0';
    
  	
	

    newFileName->next = NULL;

    /* Update the queue */
    if (queue->end == NULL || queue->start == NULL) {
        /* If the queue is empty, set both start and end to the new name */
        queue->start = queue->end = newFileName;
    } else {
        /* Otherwise, add the new name to the end and update the end */
        queue->end->next = newFileName;
        queue->end = newFileName;
    }
    
}

void printFileQueue(fileQueue *queue) {
	printf("fronta souboru\n");
	
    fileName *current = queue->start;
    while (current != NULL) {
        printf("%s\n", current->name);
        current = current->next;
    }
}

void freeFileQueue(fileQueue *queue) {
    fileName *current = queue->start;
    while (current != NULL) {
        fileName *next = current->next;
        free(current);
        current = next;
    }

    /* Reset the queue */
    initializeQueue(queue);
}

char* peek(fileQueue *queue) {
    if (queue->start != NULL) {
        /* Allocate memory for the name */
        char *firstname = strdup(queue->start->name);
        if (firstname == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        /* Move to the next element in the queue */
       
        
        queue->start = queue->start->next;
	
        return firstname;
    } else {
        return NULL;  /* Indicate that the queue is empty */
    }
}

int is_file_set(fileQueue *queue, char const *newname){
	fileName *current = queue->start;
		
	while(current != NULL){
		if(strcmp(current->name,newname) == 0){
			return 1;
		}
		else{
			current = current->next;
		}
	} 
	return 0;
}




