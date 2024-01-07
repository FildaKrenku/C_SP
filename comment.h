/* comment.h */ 

#ifndef __COMMENT__
#define __COMMENT__

/**
 * strukture of param line 
 */
typedef struct theparam {
    char *line;
    struct theparam *next;
} paramLine;

/**
 * structure of return line
 */
typedef struct thereturn {
	char *line;
	struct thereturn *next;
} returnLine;


/**
 * structure of comment 
 */
typedef struct thecom {
	char *text;
	
	char *head;
	char *struct_head;
	char *description;
	char *author;
	char *details;
	char *version;
	char *brief;
	
	struct thereturn *return_val;
	struct theparam *param;
		
	struct thecom *next;	
	
} comment;



/**
 * structure of comment queue
 */
typedef struct comqueue {
	struct thecom *start;
	struct thecom *end;
} commentQueue;


/**
 * kokotbbb
 *
 * @param commentQueue * queue fronta
 */
void initializeQueue(commentQueue *queue);


/**
 * prida komentaaa
 *
 * @param commentQueue *queue fronta
 */
void add(commentQueue *queue, char textt[]);

/**
 * kokot
 *
 * @param commentQueue * queue fronta
 * @param FIlE *file vystupni soubor
 */
int printComments(FILE *file, commentQueue *queue);

void freeQueue(commentQueue *queue);

/**
 * kokotbbb
 */
void process(comment *current);

/**
 * zprocesuje veechny komenty
 *
 * @param commentQueue * queue fronta souborufewefwfew
 */
void processComments(commentQueue *queue);

/**
 * spojeni komenraru
 */
void mergeComments(commentQueue *queue);

void add_param(comment *current, const char *line);

void add_return(comment *current, const char *line);


#endif