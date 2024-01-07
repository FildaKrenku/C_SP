/* file queue.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "filequeue.h"
#include "comment.h"

/**
 * init fronty
 */
void initializeFileQueue(fileQueue *queue) {
	/* arguments check */
	if (!queue) {
        printf("Wrong arguments");
        exit(EXIT_FAILURE);
    }
    
    queue->start = NULL;
	queue->end = NULL;
}

void addFilename(fileQueue *queue, char *newname) {
	/* arguments check */
	if (!queue || !newname) {
		printf("wrong arguments");
		exit(EXIT_FAILURE);
	}

	
    /* Allocate memory for a new file name */
    fileName *newFileName = (fileName *)malloc(sizeof(fileName));
    
    /* checking if allcating was successfull */
    if (newFileName == NULL) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    
    newFileName->name = NULL;
    newFileName->next = NULL;

    /* Copy the name into the structure */
    newFileName->name = (char *) malloc(strlen(newname) + 1);
    
    /* checking if allcating was successfull */
    if (newFileName->name == NULL) {
    	printf("Memory allocation failed.\n");
    	free(newFileName);
        exit(EXIT_FAILURE);	
	}
    
  
    strncpy(newFileName->name, newname, strlen(newname));
    newFileName->name[strlen(newname)] = '\0';
    
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

/**
 * vypsani fronty
 */
void printFileQueue(fileQueue *queue) {
	fileName *current;
	
	/* argument check */
	if (!queue ) {
		printf("Wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	
    current = queue->start;
    while (current != NULL) {
    	
        printf("%s\n", current->name);
        current = current->next;
    }
    
}

/**
 * uvgv
 */
void freeFileQueue(fileQueue *queue) {
	fileName *current;
	fileName *next;
	
	/* argument check */
	if (!queue) {
		printf("Wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	
    current = queue->start;
    while (current != NULL) {
        next = current->next;
        free(current->name);
        free(current);
        current = next;
    }

    /* Reset the queue */
    initializeFileQueue(queue);
}


/**
 * vybere prvni soubor
 */
char* peek(fileQueue *queue) {
	char *firstname;
	fileName *temp;
	
	/* argument check */
	if (!queue) {
		printf("Wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	
    if (queue->start != NULL) {
        /* Allocate memory for the name */
        firstname = strdup(queue->start->name);
        if (firstname == NULL) {
            printf("Memory allocation failed.\n");
            exit(EXIT_FAILURE);
        }

        /* Move to the next element in the queue */
       
        temp = queue->start;
        
        queue->start = queue->start->next;
        
        /* free the first name in the queue */
        free(temp->name);
        free(temp);
	
        return firstname;
    } else {
        return NULL;  /* Indicate that the queue is empty */
    }
}

/**
 * je soubor ulozen
 */
int is_file_set(fileQueue *queue, char const *newname) {
	fileName *current;
	
	/* arguments check */
	if (!queue || !newname) {
		printf("Wrong arguments");
		exit(EXIT_FAILURE);
	}
	
	current = queue->start;
	
	/* iterating through the queue and trying to find the same file */	
	while (current != NULL) {
		if (strcmp(current->name,newname) == 0) {
			return 1;
		}
		else {
			current = current->next;
		}
	} 
	return 0;
}
 



