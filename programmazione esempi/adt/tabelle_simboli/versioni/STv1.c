#include"Stv1.h"

struct symbtab{Item *a;int N;int M;}; //M--->dimensione massima tabella, N-->dimensione utilizzata

ST STinit(int maxN){
    ST st;int i;
    st=malloc(sizeof(*st));
    st->a=malloc(maxN*sizeof(Item));
    for(i=0;i<maxN;i++) st->a[i]=ITEMsetvoid();
    st->M=maxN;
    st->N=0;
    return st;
}

int STcount(ST st){
    return st->N;
}

void STfree(ST st){
    free(st->a);
    free(st);
}
void STinsert(ST st,Item val){
    int index= GETindex(KEYget(val));
    st->a[index]=val;
    st->N++;
}
Item STsearch(ST st, Key k){
    int index= GETindex(k);
    return st->a[index];
}
void STdelete(ST st, Key k){
    st->a[GETindex(k)]=ITEMsetvoid();
    st->N--;
}

Item STselect( ST st, int r){ //restituisce l'r-esimo elemento ignorando quelli vuoti
    int i;
    for(i=0;i<st->M;i++){
        if(ITEMcheckvoid(st->a[i])==0 && (r--==0)) return st->a[i];
    }
    return ITEMsetvoid();
}
void STdisplay( ST st){
    int i;
    for(i=0;i<st->M;i++){
        if(ITEMcheckvoid(st->a[i])==0) //se oggetto è valido
        ITEMstore(st->a[i]);
    }
}