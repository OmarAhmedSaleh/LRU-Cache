#include"lru.h"



QNode* initQNode(unsigned pageNumber)
{
    QNode* temp = (QNode *)malloc( sizeof( QNode ) );
    temp->pageNumber = pageNumber;
    temp->prev = temp->next = NULL;
    return temp;
}
 
Queue* initQueue( int numberOfFrames )
{
    Queue* queue = (Queue *)malloc(sizeof(Queue)); 
    queue->size = 0;
    queue->front = queue->rear = NULL;
    queue->numberOfFrames = numberOfFrames;
 
    return queue;
}
 

Hash* initHash( int capacity )
{
    Hash* hash = (Hash *) malloc(sizeof( Hash ));
    hash->capacity = capacity;
    hash->array = (QNode **) malloc( hash->capacity * sizeof(QNode*));
    int i;
    for( i = 0; i < hash->capacity; ++i )
        hash->array[i] = NULL;
 
    return hash;
}
 
bool isQueueFull(Queue* queue)
{
    return queue->size == queue->numberOfFrames;
}
 

bool isQueueEmpty(Queue* queue)
{
    return queue->size == 0;
}
 
void deQueue(Queue* queue, Hash* hash)
{
    if( isQueueEmpty(queue)){
        return;    	
    }

    hash->array[ queue->rear->pageNumber ] = NULL;
    if (queue->front == queue->rear){
        queue->front = NULL;
    }
 
    QNode* temp = queue->rear;
    queue->rear = queue->rear->prev;
 
    if (queue->rear){
        queue->rear->next = NULL;
    }
 
    free( temp );

    queue->size--;
}
 
void Enqueue( Queue* queue, Hash* hash, unsigned pageNumber )
{

    if (isQueueFull(queue))
    {
        deQueue(queue, hash);
    }
 
    QNode* temp = initQNode( pageNumber );
    temp->next = queue->front;
 
    if (isQueueEmpty(queue)){
    	queue->rear = temp;
    }else 
    {
        queue->front->prev = temp;
    }

    queue->front = temp;
    hash->array[ pageNumber ] = temp;
 
 
    queue->size++;
}
 

void ReferencePage( Queue* queue, Hash* hash, unsigned pageNumber )
{
    QNode* reqPage = hash->array[ pageNumber ];
 
    if ( reqPage == NULL )
        Enqueue( queue, hash, pageNumber );
 
    else if (reqPage != queue->front)
    {
        reqPage->prev->next = reqPage->next;
        if (reqPage->next)
           reqPage->next->prev = reqPage->prev;
         if (reqPage == queue->rear)
        {
           queue->rear = reqPage->prev;
           queue->rear->next = NULL;
        }
        reqPage->next = queue->front;
        reqPage->prev = NULL;
        reqPage->next->prev = reqPage;
 
        queue->front = reqPage;
    }
}


int main()
{
   
    Queue* q = initQueue(4);        
    Hash* hash = initHash(10);
    ReferencePage(q, hash, 1);
    ReferencePage(q, hash, 2);
    ReferencePage(q, hash, 3);
    ReferencePage(q, hash, 1);
    ReferencePage(q, hash, 4);
    ReferencePage(q, hash, 5);
    printf ("%d ",q->front->pageNumber);
    printf ("%d ",q->front->next->pageNumber);
    printf ("%d ",q->front->next->next->pageNumber);
    printf ("%d ",q->front->next->next->next->pageNumber);
 
    return 0;
}
