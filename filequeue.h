/* file queue.h */


#ifndef __FILEQUEUE__
#define __FILEQUEUE__

typedef struct thefileName{
	char name[100];
	struct thefileName *next;
} fileName;

typedef struct thefileQueue{
	struct thefileName *start;
	struct thefileName *end;
} fileQueue;

void initializeFileQueue(fileQueue *queue);

void addFilename(fileQueue *queue, char name[100]);

void printFileQueue(fileQueue *queue);

void freeFileQueue(fileQueue *queue);

char* peek(fileQueue *queue);


#endif