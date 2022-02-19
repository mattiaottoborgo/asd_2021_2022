#include "stdlib.h"
#include "Item.h"
#include "PQ.h"

struct pqueue{Item *A;int heapsize;};
static int LEFT(int i) {return(2*i+1);}
static int RIGHT(int i) {return(2*i+2);}
static int PARENT(int i) {return((i-1)/2);}
static void Swap(PQ pq, int i1,int i2){
    Item tmp=pq->A[i1];
    pq->A[i1]=pq->A[i2];
    pq->A[i2]=tmp;
}
PQ PQinit(int maxN){
    PQ pq=malloc(sizeof(*pq));
    pq->A=malloc(maxN*sizeof(Item));
    pq->heapsize=0;
    return pq;
}
void PQfree(PQ pq){
    free(pq->A);
    free(pq);
}
static void HEAPify(PQ h,int i){
    //1)cerco + grande tra i,sx,dx
    //2)scambio i con largest
    //3)itero sull'item passato da posizione i a quella di largest
    int l,r,largest;
    l=LEFT(i);
    r=RIGHT(i);
    if(l<h->heapsize && KEYcmp( getKey(h->A[l]),getKey(h->A[i]) )==1 ){
        largest=l;
    }
    else largest=i;
    if(r<h->heapsize && KEYcmp( getKey(h->A[l]),getKey(h->A[i]) )==1 ){
        largest=r;
    }
    if(largest!=i){
        Swap(h,i,largest); //scambia i con largest
        HEAPify(h,largest); //largest adesso non contiene più il + grande dopo lo scambio ma contiene i,quindi continuo ricorsione
    }
}
int PQempty(PQ pq){return pq->heapsize==0;}
int PQsize(PQ pq){return pq->heapsize;}
Item PQshowMax(PQ pq){return pq->A[0];}
void PQdisplay(PQ pq){
    int i;
    for(int i=0;i<pq->heapsize;i++){
        ITEMstore(pq->A[i]);
    }
}



void PQinsert(PQ pq,Item val){
    //1)creo nuova foglia in cui virtualmente inserisco nuovo valore
    //2)controllo se è maggiore del padre, se è cosi li scambio
    //3)itero fino a quando non arrivo alla radice oppure non soddisfo più 2)

    int i=pq->heapsize++;
    while(i>0 && KEYcmp(getKey(val),getKey(pq->A[PARENT(i)]))==1 ){
        pq->A[i]=pq->A[PARENT(i)];
        i=PARENT(i);
    }
    pq->A[i]=val;
    return;
}

Item  PQextractMax(PQ pq){
    //1)prendi valore massimo
    //2)scambialo con l'ultimo e riduci heapsize
    //3)applica HEAPify alla radice
    Item val;
    val=pq->A[0];
    Swap(pq,0,pq->heapsize-1);
    pq->heapsize--;
    HEAPify(pq,0);
    return val;
}
void PQchange( PQ pq, Item val){
    //1)scansione lineare per cercare valore
    //2)applico strategia del PQinsert da posizione trovata
    //3) applico heapify su posizione corrente di val
    int i,found=0;
    for( i=0;i<pq->heapsize&& found==0;i++){
        if(IDcmp(getId(val),getId(pq->A[i]))==0) found=1;
    }
    if(found==1){
        while(i>0 && KEYcmp(getKey(val),getKey(pq->A[PARENT(i)]))==1){
            pq->A[i]=pq->A[PARENT(i)];
            i=PARENT(i);
        }
        pq->A[i]=val;
        HEAPify(pq,i);
    }
    else printf("key not found!\n");
    return;
    
}