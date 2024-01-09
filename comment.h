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
 * this function is using to initialize queue
 *
 * @param commentQueue *queue queue of comments
 */
void initializeQueue(commentQueue *queue);


/**
 * this function is adding new comment
 *
 * @param commentQueue *queue queue of comments
 */
void add(commentQueue *queue, char textt[]);

/**
 * this function is printing comments to output file
 *
 * @param commentQueue * queue queue of comments
 * @param FIlE *file output file
 */
int printComments(FILE *file, commentQueue *queue);

/**
 * this function frees the queue
 *
 * @param commentQueue *queue queue of comments
 */
void freeQueue(commentQueue *queue);

/**
 * this function is processing current comment
 *
 * @param comment *current current comment
 */
void process(comment *current);

/**
 * this function is processing every comment
 *
 * @param commentQueue *queue queue of comments 
 */
void processComments(commentQueue *queue);

/**
 * this function is merging comments
 *
 * @param commentQueue *queue queue of comments
 */
void mergeComments(commentQueue *queue);

/**
 * this function is add new param line
 *
 * @param comment *current current comment
 * @param const char *line param line
 */
void add_param(comment *current, const char *line);

/**
 * this function is adding new return line
 *
 * @param comment *current current comment
 * @param const char *line return line
 */
void add_return(comment *current, const char *line);


#endif