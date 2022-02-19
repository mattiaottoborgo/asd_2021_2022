#include "stdio.h"
#include "stdlib.h"
#include "heap.h"
#include "Item.h"

struct heap{Item*A;int heapsize;};

int LEFT(int i){return (2*i+1);};
int RIGHT(int i){return (2*i+2);};
int PARENT(int i){return (i-1)/2;};
void Swap(Heap h,int i, int largest){//scambio gli item di largest e di i
    Item tmp=h->A[i];
    h->A[i]=h->A[largest];
    h->A[largest]=tmp;
}
Heap HEAPinit(int maxN){
    Heap h=malloc(sizeof(*h));
    h->A=malloc(maxN*sizeof(Item));
    h->heapsize=0;
    return h;
}
void HEAPfree(Heap h){
    free(h->A);
    free(h);
}
void HEAPfill(Heap h,Item item){
    int i;
    i=h->heapsize++;
    h->A[i]=item;
    return;
}
void HEAPdisplay(Heap h){
    int i;
    for(int i=0;i<h->heapsize;i++){
        ITEMstore(h->A[i]);
    }
}
void HEAPify(Heap h,int i){
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
void HEAPbuild(Heap h){
    //1)Parto da padre ultimo elemento e continuo ad iterare HEAPify fino a quando non raggiungo radice
    int i;
    for(i=PARENT(h->heapsize-1);i>0;i--){
        HEAPify(h,i);
    }
}
void HEAPsort(Heap h){
    //applico heapbuild
    //scambio radice con ultimo 
    //applico heapify sulla radice
    //itero su tutti i nodi dell'heap
    int i,j;
    HEAPbuild(h);
    j=h->heapsize;
    for(i=h->heapsize-1;i>0;i--){
        Swap(h,0,i);
        HEAPify(h,0);
    }
    h->heapsize=j;
}