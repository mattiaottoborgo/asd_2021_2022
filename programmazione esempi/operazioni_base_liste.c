#include "stdio.h"
#include "stdlib.h"

//definizione di Item
typedef struct {
    float value;
    int key;
}Item;

//definizionw di Key
typedef int Key;


//definizione di nodo

typedef struct node *link;
struct node{
    Item val;
    link next; //puntatore a prossimo nodo
};

//funzioni su Item e key
Key KEYget(Item item){
    return item.key;
}
int KEYeq(Key key1,Key key2){
    return key1==key2;
}
Item Itemsetvoid(){
    Item d;
    d.value=-1;
    d.key=-1;
    return d;
}
int KEYgr(Key key1, Key key2){
    return key1>key2;
}

//funzioni sui nodi

link newNode(Item val,link next){
    link x=malloc(sizeof(*x));
    if (x==NULL) return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

link ListInHead(Item val,link h){
    h=newNode(val,h); //creo nuovo nodo che avrà come successore il vecchio head
    return h;

}
void ListInHead2(Item val, link *hp){ //modifica direttamente head
    *hp=newNode(val,*hp);
}
link ListInTail(Item val, link h){ //soluzione 1
    link x;
    if(h==NULL){
        return newNode(val,NULL);
    }
    for(x=h;x->next!=NULL;x=x->next); //scorri fino alla fine
    x->next=newNode(val,NULL);
    return h;

}
void ListInTail2(Item val,link *hp){//soluzione 2 puntatore  ad h
    link x;
    if(*hp==NULL){
        *hp=newNode(val,NULL);
    }
    for(x=*hp;x->next!=NULL;x=x->next);
    x->next=newNode(val,NULL);
}
void ListInTail3(Item val,link *hp){//soluzione 3 puntatore a puntatore per unificare i casi
    link *xp=hp;
    while(*xp!=NULL){
        xp=&((*xp)->next);//arrivo fino all'ultimo next nella lista, dopodichè 
                          //intervengo direttamente sul campo next e non sul nodo intero
    }
    *xp=newNode(val,NULL);
}
void ListInTail4(Item val,link *hp, link *tp){ //soluzione 4: uso puntatore a coda e testa
    if(*hp==NULL) *hp=*tp=newNode(val,NULL);
    (*tp)->next=newNode(val,NULL);//aggiungo elemento dopo la coda
    *tp=(*tp)->next;//coda diventa nodo aggiunto al vecchio valore di coda


}
Item ListSearch(link h,Key k){
    link x;
    for(x=h;x!=NULL;x=x->next){
        if(KEYeq(KEYget(x->val),k)) return x->val;
    }
    return Itemsetvoid();
}
link ListDelHead(link h){
    if(h==NULL) return NULL;
    link t=h;
    h=h->next;
    free(t);
    return h;
}
void ListDelHead2(link *hp){
    if(*hp==NULL) return;
    link t=*hp;
    *hp=(*hp)->next;
    free(t);
}
Item ListExtractHead(link *hp){
    if (*hp==NULL) return Itemsetvoid();
    link t=*hp;
    Item tmp=t->val;
    *hp=(*hp)->next;
    free(t);
    return tmp;
}
link ListDelKey(link h,Key k){
    link x,prev;
    if(h==NULL) return NULL;
    
    for(x=h,prev=NULL;x!=NULL;prev=x,x=x->next){
        if(KEYeq(KEYget(x->val),k)){
            if(x==h)// se nodo è in testa
            h=x->next;
            else prev->next=x->next;
            free(x);
            break;
        }
    }
    return h;
    //cerco nodo con chiave corrsp.
    //connetto prev a next di nodo da eliminare
    //faccio free e ritono HEAD
}

void ListDelKey2(link *hp,Key k){
    link x=*hp,prev;
    if(*hp==NULL) return;
    for(prev=NULL;x!=NULL;prev=x,x=x->next){
        if(KEYeq(KEYget(x->val),k)){
            if(x==*hp) *hp=x->next;
            else prev->next=x->next;
            free(x);
            return;
        }
    }
}
Item ListExtrKeyP(link *hp,Key k){
    link *xp,t;// puntatore al campo next del nodo corrente
    //(*xp)->val = accedo all'item del nodo successivo a me tramite il campo next
    //uso tecnica del puntatore a puntatore
    Item i=Itemsetvoid();
    for(xp=hp;(*xp)!=NULL;xp=&((*xp)->next)){
        if(KEYeq(KEYget((*xp)->val),k)){
            t=*xp;
            i=(*xp)->val;
            *xp=(*xp)->next;
            i=t->val;
            free(t);
            break;
        }
    }
    return i;

}

Item ListKeExtrP2(link *hp,Key k){// copia fatta per ripasso
    link *xp=hp,t;
    Item i;
    for(;*xp!=NULL;xp=&((*xp)->next)){
        if(KEYeq(KEYget((*xp)->val),k)){
            t=*xp;
            i=(*xp)->val;
            *xp=(*xp)->next;
            free(t);
            break;

        }
    }
    return i;
}
link ListDelKeyR(link x,Key k){
    //caso terminale x==NULL->sono arrivato alla fine
    link t; // variabile in cui mi salvo il successivo di quello da eliminare, 
    //così posso agganciarlo al ritorno
    if (x==NULL) return NULL;
    if(KEYeq(KEYget(x->val),k)){
        t=x->next;
        free(x);
        return t;
    }
    x->next=ListDelKeyR(x->next,k);
    return x; // se non trovo  nulla, la chiamata ricorsiva restituirà lo stesso valore
     // senza operare alcun bypass

}

link SortListIns(Item item,link h){
    link x,p;
    Key key_item=KEYget(item);
    if (h==NULL || KEYgr(KEYget(h->val),key_item)){
        //inserimento in testa
        return newNode(item,h);
        
    }
    for(x=h->next,p=h;x!=NULL && KEYgr(key_item,KEYget(x->val));p=x,x=x->next);
    p->next=newNode(item,x);
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
link ListSortF(link h){
    //ordinamento tramite insertion sort
    link y=h,r=NULL;
    Item tmp;
    while(y!=NULL){
        tmp=ListExtractHead(&y);
        r=SortListIns(tmp,r);
    }
    return r;
}
link ListSortI(link h){
    link t,u,x;
    //t=valore corrente da sistemare
    if(h==NULL) return NULL;
    for(t=h->next,h->next=NULL;t!=NULL;t=u){ //parto da secondo elemento, perchè in insertion sort considero il primo come ordinato
         u=t->next; //mi salvo il next del nodo corrente, altrimenti lo perdo
        //inserimento in testa
        if(KEYgr(KEYget(h->val),KEYget(t->val))){
            t->next=h;
            h=t;
        }
        else{       
            //inserimento in mezzo 
            for(x=h;x->next!=NULL;x=x->next){ //scorro su lista che si sta creando
                if(KEYgr(KEYget(x->next->val),KEYget(t->val))){
                    break; //t verrà inserito prima di x->next
                }

            }
            t->next=x->next; // t punterà al successivo di x
            x->next=t;       // x punterà a t
        }
    }
    return h;
}

link SortListI(link h){
    link t,u,x;
    if (h==NULL) return NULL;
    for(t=h->next,h->next==NULL;t!=NULL;t=u){
        //ins testa
        u=t->next;
        if(KEYgr(KEYget(h->val),KEYget(t->val))){
            t->next=h;
            h=t;
        }
        else{
            for(x=h;x->next!=NULL;x=x->next){//scorre su lista nuova che si sta creando
                if(KEYgr(KEYget(x->next->val),KEYget(t->val))){
                    break;
                }
            }
            t->next=x->next;
            x->next=t;
        }
    }



    return h;
}


int main(){
    link HEAD=NULL;
    link tail;
    link h_sorted=NULL;
    Item d1;d1.key=1;d1.value=10.0;
    Item d2;d2.key=2;d2.value=20.0;
    Item d3;d3.key=3;d3.value=66.6;
    Item d4;d4.key=4;d4.value=26.6;
    Item d5;d5.key=5;d5.value=0.72;
    HEAD=ListInHead(d1,HEAD);
    ListInHead2(d2,&HEAD);
    HEAD=ListInTail(d3,HEAD);
    //ListInTail2(d1,&HEAD);  
    ListInTail3(d5,&HEAD); 
    tail=HEAD->next->next->next;
           //                      HEAD 
           //                       |
           //                       v
    ListInTail4(d4,&HEAD,&tail);  //d2->d1->d3->d5->->d4->NULL
    Key key1=2,key2=-10;
    Item found=ListSearch(HEAD,key1);
    Item notfound=ListSearch(HEAD,key2);
    HEAD=ListDelHead(HEAD);
    //ListDelHead2(&HEAD); //provata per esercizio
    Item extr_h=ListExtractHead(&HEAD);
    Key keydel= 5;
    Key keyext= 4;
    //HEAD=ListDelKey(HEAD,keydel);// d3->d4->NULL
    //ListDelKey2(&HEAD,keydel);
    //HEAD=ListDelKeyR(HEAD,keydel);
    //Item extr_k=ListExtrKeyP(&HEAD,keyext); //estrazione data una chiave
    //HEAD=ListSortF(HEAD);
    HEAD=ListSortI(HEAD);

    printf("ciao");


    

    
      

}