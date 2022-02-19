//ADT vettore
#include "queue.h"
struct queue{
    Item *q;
    int N,head,tail;
};

QUEUE QUEUEinit(int maxN){
    QUEUE q=malloc(sizeof*q);
    q->q=malloc(maxN*sizeof(Item));
    q->N=maxN+1;
    q->head=q->N; //parto da N perchè cosi se rinizio la lista non ho problemi
    q->tail=0;
    return q;
}
void QUEUEput(QUEUE q,Item val){
    q->q[q->tail++]=val;
    q->tail=q->tail%(q->N);
    return;
}
Item QUEUEget(QUEUE q){
    q->head=(q->head)%(q->N); //siccome head è messo su N per prevenire errori quando controllo se è vuota prima di un QUEUEget, devo posizionarlo su 0.
    return q->q[q->head++];
}
int QUEUEempty(QUEUE q){return ((q->head)%(q->N))==(q->tail);}