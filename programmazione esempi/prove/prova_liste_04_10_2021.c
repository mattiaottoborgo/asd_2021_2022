#include "stdio.h"
#include "stdlib.h"
typedef struct node *link;
typedef int Key;
typedef struct {
    int value;
    Key key;
} Item;
struct node{
    Item val;
    link next;
};

link newNode(Item item, link next);
Item newItem(int value, int k);
link ListInHead(link h,Item value);
link ListInTail(link h, Item value);
Item ListSearch(Key k, link h);
link ListDelHead(link h);
Item ListExtrHead(link *hp);
link ListDelKey(Key k, link h);
Item ListExtrKey(link *hp, Key k);
Item ListExtrKeyP(link *hp, Key k);

int main(){
 Item item1=newItem(1,1);
 Item item2=newItem(2,2);
 Item item3=newItem(3,3);
 Item item4=newItem(4,4);
 Item item5=newItem(5,5);

 link head=NULL;
 head=ListInHead(head,item1);
 head=ListInTail(head,item2);
 ListInTail_UP(&head,item3);
 Item search=ListSearch(2,head);
 head=ListInTail(head,item4);
 head=ListDelHead(head);
 //Item Extr=ListExtrHead(&head);
head=ListInTail(head,item5);
 //head=ListDelKey(5,head);
 link h=NULL;
 Item del=ListExtrKeyP(&head,5);
 
 printf("\n");
}

Item Item_void(){
    Item d;
    d.value=-1;
    d.key=-1;
    return d;
}
Key getKey(Item item){
    return item.key;
}
int Keyeq(Key key1,Key key2){
    return key1==key2;
}
int Keygr(Key key1,Key key2){
    return key1>key2;
}
int Keyl(Key key1,Key key2){
    return key1<key2;
}
link newNode(Item item, link next){
    link x= malloc(sizeof(*x));
    if (x==NULL) return NULL;
    x->val=item;
    x->next=next;
    return x;
}
Item newItem(int value,int k){
    Item t;
    t.value=value;
    t.key=k;
    return t;
}

link ListInHead(link h,Item value){
    h=newNode(value,h);
    return h;
}
link ListInTail(link h, Item value){
    link x;
    if (h==NULL) {
        return newNode(value,NULL);
    }
    for(x=h;x->next!=NULL;x=x->next);
    x->next=newNode(value,NULL);
    return h;
}
void ListInTail_UP(link *hp,Item value){
    link *xp=hp; //xp è puntatore a campo next del nodo che analizzo
    while(*xp!=NULL){ //fino a quando non vedo che next==NULL
        xp= &((*xp)->next);
    }
    //for(*xp=hp;*xp!=NULL;xp= &((*xp)->next));
    *xp=newNode(value,NULL);
}

Item ListSearch(Key k, link h){
    link x;
    for(x=h;x!=NULL;x=x->next){
        if( Keyeq(getKey(x->val),k))
        return x->val;
    }
    return Item_void();
}
link ListDelHead(link h){
    link t=h;
    if(h==NULL) return NULL;
    h=h->next;
    free(t);
    return h;
}
Item ListExtrHead(link *hp){
    Item d;
    link t=*hp;
    if(*hp==NULL) return Item_void();
    d=(*hp)->val;
    (*hp)=(*hp)->next;
    free(t);
    return d;
}
link ListDelKey(Key k, link h){
    link x,p;
    if(x==NULL) return NULL;
    for(x=h,p=NULL;x!=NULL;p=x,x=x->next){
        if(Keyeq(getKey(x->val),k)){
            p->next=x->next;
            free(x);
            break;
        }
    }
    return h;
}
link ListDelKeyR(link x,Key k){
    link t;
    if(x==NULL) return NULL;
    if(Keyeq(getKey(x->val),k)){
        t=x->next;
        free(x);
        return t;
    }
    x->next=ListDelKeyR(x->next,k);
    return x;
}
Item ListExtrKey(link *hp, Key k){
    link x,p;
    Item item=Item_void();

    for(x=*hp,p=NULL;x!=NULL;p=x,x=x->next){
        if(Keyeq(getKey(x->val),k)){
            item=x->val;
            p->next=x->next;
            free(x);
            break;

        }
    }
    return item;
}


Item ListExtrKeyP(link *hp, Key k){
    link *xp,t;
    Item item=Item_void();

    for(xp=hp;*xp!=NULL;xp=&((*xp)->next)){
        if(Keyeq(getKey((*xp)->val),k)){
            item=(*xp)->val;
            t=*xp;
            *xp=(*xp)->next;
            free(t);
            break;

        }
    }
    return item;
}

