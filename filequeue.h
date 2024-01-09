/* file queue.h */


#ifndef __FILEQUEUE__
#define __FILEQUEUE__

/**
 * structure of filename
 */
typedef struct thefileName{
	char *name;
	struct thefileName *next;
} fileName;

/**
 * structure of file queue
 */
typedef struct thefileQueue{
	struct thefileName *start;
	struct thefileName *end;
} fileQueue;


/**
 * this function is initializing filequeue
 *
 * @param fileQueue *queue file queue
 * @param char *newname name of the file
 */
void initializeFileQueue(fileQueue *queue);


/**
 * this function is adding new filename to the queue
 *
 * @param fileQueue *queue file queue
 * @param char *newname name of the file
 */
void addFilename(fileQueue *queue, char *newname);

/**
 * this function is printing every name of file
 *
 * @param fileQueue *queue file queue
 */
void printFileQueue(fileQueue *queue);

/**
 * this function is freeing the queue
 *
 * @param fileQueue *queue file queue
 */
void freeFileQueue(fileQueue *queue);

/**
 * this function is peeking first name of file
 *
 * @param fileQueue *queue file queue
 */
char* peek(fileQueue *queue);

/**
 * this function is chekcing if newname is already in queue
 *
 * @param fileQueue *queue file queue
 * @param char const *newname name of file
 */
int is_file_set(fileQueue *queue, char const *newname);






#endif