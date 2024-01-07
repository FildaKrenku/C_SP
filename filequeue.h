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

void initializeFileQueue(fileQueue *queue);


/**
 * pridani souboru do
 * fronty a
 */
void addFilename(fileQueue *queue, char *newname);

/**
 * vypise frontu souboru
 */
void printFileQueue(fileQueue *queue);

/**
 * uvoleneni fronty
 */
void freeFileQueue(fileQueue *queue);

/**
 * vybere soubor
 */
char* peek(fileQueue *queue);

/**
 * je soubor ulozedddddn
 */
int is_file_set(fileQueue *queue, char const *newname);






#endif