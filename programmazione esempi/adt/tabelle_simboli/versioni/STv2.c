#include "STv2.h"
struct symbtab{Item *a;int maxN;int size;};
ST STinit(int maxN){
    ST st;int i;
    st=malloc(sizeof(*st));
    st->a=malloc(maxN*sizeof(Item));
    for(i=0;i<maxN;i++){
        st->a[i]=ITEMsetvoid();
    }
    st->maxN=maxN;
    st->size=0;
    return st;
}
int STcount(ST st){
    return st->size;
}

void STfree(ST st){
    free(st->a);
    free(st);
}

void STdisplay( ST st){
    int i;
    for(i=0;i<st->size;i++){
        if(ITEMcheckvoid(st->a[i])==0) 
        ITEMstore(st->a[i]);
    }
}

void STdelete(ST st,Key k){

    //1) cerco posizione
    //2) faccio scorrere verso sx gli elementi dopo quello da eliminare
    int i,j=0;
    while(KEYcmp(k,KEYget(st->a[j]) )!=0) j++;
    for(int i=j;i<st->size-1;i++){
        st->a[i]=st->a[i+1];
    }
    st->size--; //attenzione! se non implementi controllo, decrementa size anche se non trova nulla
}

#if ST_NOT_IN_ORDER
void STinsert(ST st,Item val){
    int i=st->size++;
    //se dimensione non è sufficiente
    if(st->size>=st->maxN){
        st->a=realloc(st->a,(2*st->maxN)*sizeof(Item));
        if(st->a==NULL) return;
        st->maxN=2*st->maxN;
    }
    st->a[i]=val;
}
Item STsearch(ST st, Key k){
    int i;
    if(st->size==0) return ITEMsetvoid();
    for(i=0;i<st->size;i++){
        if(KEYcmp(k,KEYget(st->a[i]))==0) return st->a[i];
    }
    return ITEMsetvoid();
}
#endif

#if ST_IN_ORDER
void STinsert(ST st,Item val){
    int i=st->size++;
    //se dimensione non è sufficiente
    if(st->size>=st->maxN){
        st->a=realloc(st->a,(2*st->maxN)*sizeof(Item));
        if(st->a==NULL) return;
        st->maxN=2*st->maxN;
    }
    while(i>0 && KEYcmp(KEYget(st->a[i-1]),KEYget(val))==1){
        st->a[i]=st->a[i-1];
        i--;
    }
    st->a[i]=val;
}
// restituisce r-esimo elemento
Item STselect(ST st, int r){
    return st->a[r];
}
static Item searchR(ST st, int l, int r, Key k){
    int m=(l+r)/2;
    if(l>r) return ITEMsetvoid();
    if(KEYcmp(k,KEYget(st->a[m]))==0) return st->a[m];
    if(l==r) return ITEMsetvoid();
    if(KEYcmp(k,KEYget(st->a[m]))==-1) return searchR(st,l,m-1,k);
    else return searchR(st,m+1,r,k);
}

Item STsearch(ST st, Key k){
    return searchR(st,0,st->size-1,k);
}


#endif


