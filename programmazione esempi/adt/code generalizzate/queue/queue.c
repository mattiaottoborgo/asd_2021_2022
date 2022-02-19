//ADT vettore
#include "queue.h"

#define QUEUE_V 1
#define QUEUE_L 0

#if QUEUE_V
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
    if(q->tail==q->N-1){printf("coda piena!\n");return;}
    q->q[q->tail++]=val;
    q->tail=q->tail%(q->N);
    return;
}
Item QUEUEget(QUEUE q){
    if(QUEUEempty(q)){printf("coda vuota!\n");return -1;}
    q->head=(q->head)%(q->N); //siccome head è messo su N per prevenire errori quando controllo se è vuota prima di un QUEUEget, devo posizionarlo su 0.
    return q->q[q->head++];
}
int QUEUEempty(QUEUE q){return ((q->head)%(q->N))==(q->tail);}
#endif

#if QUEUE_L
    typedef struct node *link;
    struct node{Item val;link next;};
    struct queue{
        link head;
        link tail;
    };
    static link newNode(Item val, link next){
        link x=malloc(sizeof(*x));
        x->val=val;
        x->next=next;
        return x;
    }
    QUEUE QUEUEinit(int maxN){
        QUEUE q=malloc(sizeof(*q));
        q->head=NULL;
        q->tail=NULL;
        return q;
    }
    int QUEUEempty(QUEUE q){
        return (q->head)==(q->tail);
    }
    void QUEUEput(QUEUE q,Item val){
        //se coda è vuota
        if(q->head==NULL){
            q->head=newNode(val,q->head);
            q->tail=q->head;
            return;
        }
        q->tail->next=newNode(val,NULL);
        q->tail= q->tail->next;
        return;
    }
    Item QUEUEget(QUEUE q){
        Item tmp=q->head->val;
        link x=q->head;
        q->head=q->head->next;
        free(x);
        return tmp;

    }

#endif