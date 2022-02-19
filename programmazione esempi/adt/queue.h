//ADT vettore
#include "stdlib.h"
#include "stdio.h"

typedef struct queue *QUEUE;
typedef int Item;
QUEUE QUEUEinit(int maxN);
int QUEUEempty(QUEUE q);
void QUEUEput(QUEUE q, Item val);
Item QUEUEget(QUEUE q);