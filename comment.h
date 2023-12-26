/* comment.h */ 

#ifndef __COMMENT__
#define __COMMENT__
                                                                                                                                                                                                      
typedef struct thecom{
	char *text;
	struct thecom *next;	
	
	char *head;
	char *description;
	char *param;
	char *author;
	char *details;
	char *retun_val;
	char *version;
	char *brief;
	
} comment;

/**
 * struktura fornty
 */
typedef struct comqueue{
	struct thecom *start;
	struct thecom *end;
} commentQueue;


void init(commentQueue *queue);

void add(commentQueue *queue, char  *text);

void printComments(commentQueue *queue);

void freeQueue(commentQueue *queue);

void process(comment *currnet);



#endif