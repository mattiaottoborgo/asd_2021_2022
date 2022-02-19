
#include "PQv2.h"
#include "stdlib.h"
typedef struct{int index;int prio;}heapItem;
struct pqueue{heapItem *A;int heapsize;int *qp};
static int LEFT(int i) {return(2*i+1);}
static int RIGHT(int i) {return(2*i+2);}
static int PARENT(int i) {return((i-1)/2);}
PQ PQinit(int maxN){
    // ho aggiunto vettore  qp che mi salva indici
    PQ pq=malloc(sizeof(*pq));
    pq->A=malloc(maxN*sizeof(heapItem));
    pq->qp=malloc(maxN*sizeof(int));//qp tiene traccia della posizione nell'heap dell'index-esimo elemento
                                    //(item.index=0--->la sua posizione nell'heap è contenuta in qp[0]) e cosi via
    pq->heapsize=0;
    for(int i=0;i<maxN;i++){
        pq->A[i].index=-1;pq->qp[i]=-1;
    }
    return pq;
}
void PQfree(PQ pq){
    free(pq->A);
    free(pq->qp);
    free(pq);
}
void PQinsert(PQ pq,int index,int prio){
    //index-->id oggetto
    //i posizione nell'heap

    int i=pq->heapsize++;
    while(i>0 && pq->A[PARENT(i)].prio<prio){
        pq->A[i]=pq->A[PARENT(i)];//tiro giù parent
        pq->qp[pq->A[i].index]=i;// dell'index-iesimo elemento, salvo la i-esima posizione nell'heap
        i=PARENT(i);
    }
    pq->A[i].index=index;
    pq->A[i].prio=prio;
    pq->qp[index]=i;

    return;
}

static void Swap(PQ pq, int pos1,int pos2){

    //effettuo scambio
    int index1,index2;
    heapItem tmp=pq->A[pos1];
    pq->A[pos1]=pq->A[pos2];
    pq->A[pos2]=tmp;

    //adesso in pos1 ci sarà l'item che era in pos2, quindi otterrò il suo indice e viceversa
    index1=pq->A[pos1].index;
    index2=pq->A[pos2].index;
    pq->qp[index1]=pos1;
    pq->qp[index2]=pos2;
}