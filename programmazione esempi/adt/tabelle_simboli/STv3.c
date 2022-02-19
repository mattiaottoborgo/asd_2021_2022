#include "STv3.h"

typedef struct STnode *link;
struct STnode {Item val;link next;};
typedef struct{link head;int size;}list;
struct symbtab{list tab;};
static link NEW(Item val,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL) return NULL;
    x->val=val;
    x->next=next;
    return x;
}
ST STinit(int maxN){
    ST st=malloc(sizeof(*st));
    if(st==NULL)return NULL;
    st->tab.head=NULL;
    st->tab.size=0;
    return st;
}
void STfree(ST st){
    link x=st->tab.head,t;
    for(x=st->tab.head;x!=NULL;x=t){
        t=x->next;
        free(x);
    }
}
int STcount(ST st){
    return st->tab.size;
}
void STdisplay(ST st){
    link x;
    for(x=st->tab.head;x!=NULL;x=x->next){
        ITEMstore(x->val);
    }
}
Item STsearch(ST st,Key k){
    link x;
    if(st==NULL) return ITEMsetvoid();
    if(st->tab.head==NULL) return ITEMsetvoid();
    for(x=st->tab.head;x!=NULL;x=x->next){
        if(KEYcmp(k,KEYget(x->val))==0) return x->val;
    }
    return ITEMsetvoid(); 
}

void STdelete(ST st, Key k){
    link x,p;
    if(st==NULL) return;
    if(st->tab.head==NULL) return;

    for(x=st->tab.head,p=NULL;x!=NULL;p=x,x=x->next){
         if(KEYcmp(k,KEYget(x->val))==0){
             if(x==st->tab.head){
                 st->tab.head=x->next;
             }
             else{
                 p->next=x->next;
             }
             free(x);
             st->tab.size--;
             break;
         }
    }
}
#if ST_IN_ORDER
Item STselect(ST st, int r){
    int i;
    link x=st->tab.head;
    for(i=0;i<r;i++){
        x=x->next;
    }
    return x->val;
}
void STinsert(ST st,Item val){
    link x,p;
    if(st==NULL) return;
    if(st->tab.head==NULL || KEYcmp(KEYget(st->tab.head->val),KEYget(val))==1) st->tab.head=NEW(val,st->tab.head);
    else{
        for(x=st->tab.head->next,p=st->tab.head;x!=NULL && KEYcmp(KEYget(val),KEYget(x->val))==1;p=x,x=x->next);
        p->next=NEW(val,x);
    }
    st->tab.size++;
}
#endif


#if  ST_NOT_IN_ORDER
void STinsert(ST st,Item val){
    if(st==NULL) return ;
    st->tab.head=NEW(val,st->tab.head);
    st->tab.size++;
}
#endif