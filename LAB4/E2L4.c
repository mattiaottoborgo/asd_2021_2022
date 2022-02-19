#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#define file "anag1.txt"
#define N_COM 6
#define MAX_CHAR 50
#define L_MAX_COMANDO 50
#define OUTFILE "log.txt"
typedef struct{
    char *cod;
    char *name;
    char *surname;
    char *date;
    char *address;
    char *city;
    int cap;
}item;
typedef char* Key;
typedef struct node *link;
enum {acq_tast,acq_file,ricerca,canc,canc_int,stampa_file};
char *l_com[N_COM]={"acq_tastiera","acq_file","ricerca","canc","canc_int","stampa_file"};
struct node {
    item val;
    link next;
};

//funzioni su item
item find(link h,Key k);
item extract(link *hp,Key k);
item fill_item(char* tmp_name,char*tmp_cognome,char* tmp_data,char* tmp_citta,char* tmp_via,int tmp_cap,char *tmp_cod);
item nullItem();
item fill_item_from_keyboard();
Key data_get(item Item);
Key cod_get(item Item);
Key name_get(item Item);
Key name_get(item Item);
Key surname_get(item Item);
Key city_get(item Item);
Key address_get(item Item);
int cap_get(item Item);
int keycmp(Key k1, Key k2);
int checkValidItem(item i);
char *dateChangeFormat(char*oldData);

//funzioni lista
link fill_list_from_file(link head);
link fill_list_from_keyboard(link head);
link newNode(item val,link next);
link sortListIns(item Item,link h);
link extractNode(link *hp,Key k);
link nullNode();
link extractNode(link *hp,Key k);
void print_item(item i);
void print_lista(link h);

int main(){
    link head=NULL,node;
    int i;
    char key_search[MAX_CHAR],data1[MAX_CHAR],data2[MAX_CHAR],*d1,*d2,comando[L_MAX_COMANDO];
    printf("1) <acq_tastiera> ---->inserisci manualmente i dati.\n");
    printf("2) <acq_file> --->lettura dati da file\n");
    printf("scegli metodo di acquisizione:\n");
    scanf("%s",comando);
    for(i=0;i<N_COM;i++){
        if(!strcmp(comando,l_com[i])) break;
    }
    switch(i){
        case acq_tast:
            head=fill_list_from_keyboard(head);
            break;
        case acq_file:
            head=fill_list_from_file(head);
            break;
        break;
    }
    printf("scrivi comando da eseguire:");
    scanf("%s",comando);
    for(i=0;i<N_COM;i++){
        if(!strcmp(comando,l_com[i])) break;
    }
    switch(i){
        case acq_tast:
            break;
        case acq_file:
            head=fill_list_from_file(head);
            break;
        case ricerca:
            printf("inserisci codice del tipo AXXXX da cercare:");
            scanf("%s",key_search);
            item found=find(head,key_search);
            if(checkValidItem(found)) print_item(found);
            else printf("Item associato alla chiave data non trovato!\n");
            break;
        case canc:
            printf("inserisci codice del tipo AXXXX da eliminare:");
            scanf("%s",key_search);
            item extracted=extract(&head,key_search);
            if(checkValidItem(extracted)) print_item(extracted);
            else printf("Item associato alla chiave data non trovato!\n");
            break;
        case canc_int:
            printf("inserisci intervallo di date in cui cancellare elementi\nNota: utilizzare il formato <gg/mm/aaaa gg/mm/aaaa>\nInserisci intervallo:");
            scanf("%s %s",data1,data2);
            d1=dateChangeFormat(data1);
            d2=dateChangeFormat(data2);
            node=extractNode(&head,d2); //estraggo primo nodo(poiche in ordine decrescente, il primo sarà il + giovane)
            if(checkValidItem(node->val)){
                print_item(node->val);
                node=node->next;
                while(node!=NULL && keycmp(data_get(node->val),d1)>0){
                    node=extractNode(&head,data_get(node->val));
                    print_item(node->val);
                    node=node->next;
                }
            }
            else printf("non ho trovato alcun elemento nell'intervallo indicato!\n");
            break;
        case stampa_file:
            print_lista(head);     
            break;
        break;
    }
}
//funzioni su lista
link fill_list_from_file(link head){
    item tmp_item;
    FILE *fp;
    int tmp_cap;
    char tmp_name[MAX_CHAR];
    char tmp_surname[MAX_CHAR];
    char tmp_date[MAX_CHAR];
    char tmp_city[MAX_CHAR];
    char tmp_cod[MAX_CHAR];
    char tmp_address[MAX_CHAR];
    fp=fopen(file,"r");


    while(fscanf(fp,"%s %s %s %s %s %s %d",&tmp_cod,&tmp_name,&tmp_surname,&tmp_date,&tmp_address,&tmp_city,&tmp_cap)==7){
        tmp_item=fill_item(tmp_name,tmp_surname,tmp_date,tmp_city,tmp_address,tmp_cap,tmp_cod);
        head=sortListIns(tmp_item,head);
    }
    return head;
}
link fill_list_from_keyboard(link head){
    int n;
    printf("inserisci numero di elementi da inserire: ");
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        item tmp=fill_item_from_keyboard();
        head=sortListIns(tmp,head);
    }
    return head;
}
link sortListIns(item Item,link h){
    link x,p;
    Key key_item=data_get(Item);
    if (h==NULL || keycmp(key_item,data_get(h->val))>0 ){
        //inserimento in testa solo se più giovane
        return newNode(Item,h);
    }
    for(x=h->next,p=h;x!=NULL && keycmp(data_get(x->val),key_item)>0;p=x,x=x->next);
    p->next=newNode(Item,x);
    return h;
}
link newNode(item val,link next){
    link x=malloc(sizeof(*x));
    if (x==NULL) return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}
link nullNode(){
    return newNode(nullItem(),NULL);
}
link extractNode(link *hp,Key k){
    link x,p;
    link t=nullNode();
    for(x=*hp,p=NULL;x!=NULL;p=x,x=x->next){
        if(keycmp(k,data_get(x->val))>=0) {
            t=x;
            if(x==*hp) *hp=x->next;
            else p->next=x->next;
            break;
        }
    }
    return t;
}
void print_item(item i){
    printf("codice: %s\nnome: %s\ncognome: %s\ndata di nascita: %s\nvia: %s\ncittà: %s\ncap: %d\n\n",i.cod,i.name,i.surname,i.date,i.address,i.city,i.cap);
    return;
}
void print_lista(link h){
    FILE *fpout;
    link x;
    fpout=fopen(OUTFILE,"w");
            for(x=h;x!=NULL;x=x->next){
                fprintf(fpout,"%s %s %s %s %s %s %d\n",cod_get(x->val),name_get(x->val),surname_get(x->val),data_get(x->val),address_get(x->val),city_get(x->val),cap_get(x->val));
            }
    fclose(fpout);
    printf("lista stampata correttamente su %s",OUTFILE);
    return;
}

//funzioni su item
item fill_item(char* tmp_name,char*tmp_surname,char* tmp_date,char* tmp_city,char* tmp_address,int tmp_cap,char *tmp_cod){
    item tmp;
    tmp.name=strdup(tmp_name);
    tmp.surname=strdup(tmp_surname);
    tmp.date=dateChangeFormat(tmp_date);
    tmp.city=strdup(tmp_city);
    tmp.address=strdup(tmp_address);
    tmp.cap=tmp_cap;
    tmp.cod=strdup(tmp_cod);
    return tmp;

}
item fill_item_from_keyboard(){
    char tmp_cod[MAX_CHAR];
    char tmp_name[MAX_CHAR];
    char tmp_surname[MAX_CHAR];
    char tmp_date[MAX_CHAR];
    char tmp_city[MAX_CHAR];
    char tmp_address[MAX_CHAR];
    int tmp_cap;
    printf("inserisci codice: ");
    scanf("%s",&tmp_cod);
    printf("inserisci nome: ");
    scanf("%s",&tmp_name);
    printf("inserisci cognome: ");
    scanf("%s",&tmp_surname);
    printf("inserisci data nel formato aaaa/mm/gg: ");
    scanf("%s",&tmp_date);
    printf("inserisci indirizzo: ");
    scanf("%s",&tmp_address);
    printf("inserisci città: ");
    scanf("%s",&tmp_city);
    printf("inserisci cap: ");
    scanf("%d",&tmp_cap);
    return fill_item(tmp_name,tmp_surname,tmp_date,tmp_city,tmp_address,tmp_cap,tmp_cod);

}
char *dateChangeFormat(char*oldData){
    char *separ="/";
    char *giorno;
    char *mese;
    char *anno=NULL;
    giorno = strtok(oldData, "/");
    mese = strtok(NULL, "/");
    anno = strtok(NULL, "/");
    strcat(anno,"/");
    strcat(anno,mese);
    strcat(anno,"/");
    strcat(anno,giorno);
    return strdup(anno);
}
Key data_get(item Item){
    return Item.date;
}
Key cod_get(item Item){
    return Item.cod;
}
Key name_get(item Item){
    return Item.name;
}
Key surname_get(item Item){
    return Item.surname;
}
Key city_get(item Item){
    return Item.city;
}
Key address_get(item Item){
    return Item.address;
}
int cap_get(item Item){
    return Item.cap;
}
item nullItem(){
    item t;
    t.name="NULL";
    t.surname="NULL";
    t.date="NULL";
    t.city="NULL";
    t.address="NULL";
    t.cap=-1;
    t.cod="NULL";
    return t;
}
int keycmp(Key k1, Key k2){
    return strcmp(k1,k2);
}
int checkValidItem(item i){
    if(!strcmp(i.name,"NULL") || !strcmp(i.surname,"NULL") ||  !strcmp(i.cod,"NULL") || !strcmp(i.date,"NULL") || !strcmp(i.address,"NULL") || !strcmp(i.city,"NULL") || i.cap==-1 ) return 0;
    return 1;
}
item find(link h,Key k){
    link x;
    item t=nullItem();
    for(x=h;x!=NULL;x=x->next){
        if(!keycmp(k,cod_get(x->val))) {
            t=x->val;
            break;
        }
    }
    return t;
}
item extract(link *hp,Key k){
    link x,p;
    item t=nullItem();
    for(x=*hp,p=NULL;x!=NULL;p=x,x=x->next){
        if(!keycmp(k,cod_get(x->val))) {
            t=x->val;
            if(x==*hp){
                *hp=x->next;
            }
            else p->next=x->next;
            free(x);
            break;
        }
    }
    return t;
}
