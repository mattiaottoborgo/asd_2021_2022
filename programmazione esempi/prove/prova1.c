#include "stdlib.h"
#include "stdio.h"
typedef int Key;
typedef struct node *link;
typedef struct{
    int value;
    Key key;
}Item;

struct node{
    Item val;
    link next;
};
link SortListIns(Item item,link h);
Item SortListSearch(Key key,link h);
link SortListDel(link h,Key k);
int main(){
    Item item1;
    Item item2;
    Item item4;
    Key search=2;
    Item Toinsert;
    item1.value=1;
    item1.key=1;
    item2.value=2;
    item2.key=2;
    item4.value=4;
    item4.key=4;
    Toinsert.value=3;
    Toinsert.key=3;
    link h=NULL;
    h=SortListIns(item1,h);
    h=SortListIns(item4,h);
    h=SortListIns(item2,h);
    h=SortListIns(Toinsert,h);
    Item searched=SortListSearch(search,h);
    h=SortListDel(h,search);
    printf("\n");
}

Key KEYget(Item item){
    return item.key;
}
int KEYeq(Key key1,Key key2){
    return key1==key2;
}
int KEYgr(Key key1, Key key2){
    return key1>key2;
}
Item Itemsetvoid(){
    Item d;
    d.value=-1;
    d.key=-1;
    return d;

}
link newNode(link next,Item item){
    link x=malloc(sizeof(*x));
    if(x==NULL) return NULL;
    x->val=item;
    x->next=next;
    return x;
}
link SortListIns(Item item,link h){
    link x,p;
    Key key_item=KEYget(item);
    if (h==NULL || KEYgr(KEYget(h->val),key_item)){
        //inserimento in testa
        return newNode(h,item);
        
    }
    for(x=h->next,p=h;x!=NULL && KEYgr(key_item,KEYget(x->val));p=x,x=x->next);
    p->next=newNode(x,item);
    return h;
}

Item SortListSearch(Key key,link h){
    link x;
    Item item;
    for(x=h;x!=NULL && !KEYeq(key,KEYget(x->val));x=x->next);
    if(x!=NULL) return x->val;
    return Itemsetvoid();
}
link SortListDel(link h,Key k){
    link x,p;
    if (h==NULL) return NULL;
    for(x=h,p=NULL;x!=NULL;p=x,x=x->next){
        if(KEYeq(k,KEYget(x->val))){
            if(x==h) h=x->next;
            else p->next=x->next;
            free(x);
            break;
        }

    }
    return h;
}
