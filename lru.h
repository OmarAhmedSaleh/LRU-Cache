#include <stdio.h>
#include <stdlib.h>


typedef struct QNode
{
    struct QNode *prev, *next;
    unsigned pageNumber;  
} QNode;
 
typedef struct Queue
{
    unsigned size;  
    unsigned numberOfFrames; 
    QNode *front, *rear;
} Queue;


typedef struct Hash
{
    int capacity; 
    QNode* *array;
} Hash;


QNode* initQNode( unsigned pageNumber );
Queue* initQueue(int numberOfFrames);
Hash* initHash(int capacity);

bool isQueueFull(Queue* queue);
bool isQueueEmpty(Queue* queue);

void deQueue(Queue* queue, Hash* hash);
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber );
void ReferencePage(Queue* queue, Hash* hash, unsigned pageNumber);
 
