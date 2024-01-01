/* comment.h */ 

#ifndef __COMMENT__
#define __COMMENT__

/**
 * struktura komentare
 */
typedef struct thecom {
	char *text;
	

	
	char *head;
	char *description;
	char *author;
	char *param;
	char *details;
	char *return_val;
	char *version;
	char *brief;
	
	struct thecom *next;	
	
} comment;


/**
 * struktura fornty
 */
typedef struct comqueue {
	struct thecom *start;
	struct thecom *end;
} commentQueue;


/**
 * kokotbbb
 */
void initializeQueue(commentQueue *queue);

void add(commentQueue *queue, char  *text);

void printComments(commentQueue *queue);

void freeQueue(commentQueue *queue);

/**
 * process
 */
void process(comment *current);

/**
 * zprocesuje veechny komenty
 */
void processComments(commentQueue *queue);

/**
 * spojeni komenraru
 */
void mergeComments(commentQueue *queue);



#endif