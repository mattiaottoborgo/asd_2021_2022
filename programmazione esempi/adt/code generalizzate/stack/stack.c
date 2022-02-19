#include "stack.h"

#include "stdio.h"
#include "stdlib.h"


#define STACK_V 0
#define STACK_L 1
#if STACK_V
struct stack{Item *s;int N;};
STACK STACKinit(int maxN){
    STACK sp=malloc(sizeof(*sp));
    sp->s=malloc(maxN*sizeof(Item));
    sp->N=0;
    return sp;
}
int STACKempty(STACK sp){
    return sp->N==0;
}
void STACKpush(STACK sp, Item val){ //inserisce elemento
    //inserimento in coda per essere O(1)
    sp->s[sp->N++]=val;
}
Item STACKpop(STACK sp){ //restituisce ultimo elemento inserito
    return sp->s[--(sp->N)];
}
#endif
#if STACK_L
    typedef struct STACKnode *link;
    struct STACKnode{Item val;link next;};
    struct stack{
        link head;
    };
    static link NEWnode(Item val,link next){
        link x=malloc(sizeof(*x));
        if(x==NULL)return NULL;
        x->val=val;
        x->next=next;
        return x;

    }
    STACK STACKinit(int maxN){
        STACK s=malloc(sizeof*s);
        s->head=NULL;
        return s;
    }
    int STACKempty(STACK s){
        return s->head==NULL;
    }
    void STACKpush(STACK s,Item val){
        s->head=NEWnode(val,s->head);
    }
    Item STACKpop(STACK s){
        Item t=s->head->val;
        link x=s->head;
        s->head=s->head->next;
        free(x);
        return t;
    }
#endif
