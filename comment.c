/* comment.c */ 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "comment.h"



void initializeQueue(commentQueue *queue) {
    queue->start = NULL;
    queue->end = NULL;
}

void add(commentQueue *queue, char const *text) {
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
        printf("%s\n", current->text);
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





