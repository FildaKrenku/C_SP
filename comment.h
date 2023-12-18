/* comment.h */ 

#ifndef __COMMENT__
#define __COMMENT__

typedef struct thecom{
	char *text;
	struct thecom *next;	
} comment;

/**
 * struktura fornty
 */
typedef struct comqueue{
	struct thecom *start;
	struct thecom *end;
} commentQueue;


void init(commentQueue *queue);

void add(commentQueue *queue, char const *text);

void printComments(commentQueue *queue);

void freeQueue(commentQueue *queue);

/*
void process(commentQueue *queue);
*/



#endif