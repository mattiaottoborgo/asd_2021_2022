#include "mod_pers.h"
#include <stdio.h>
#include <stdlib.h>
typedef struct node *link;
struct pg{
    char codice[LEN_CODICE];
    char nome[MAX_C];
    char classe[MAX_C];
    EQUIP equip;
    STAT stat;  
};
struct equip {
 int inUso;
 ITEM* equiplist;
 //todo metti valori corretti
};
struct list{
    link head;link tail; int N;
};

struct node{
    PG value;
    link next;
};

int KEYcompare(char *k1,char *k2){
    return strcmp(k1,k2);

}
char *KEYget(PG pg){
    return pg->codice;
}
char *getName(PG pg){
    return pg->nome;
}
int getDimEquip(EQUIP e){
    return e->inUso;
}
int getFreeSlotIndex(EQUIP e){
    if(e->inUso==0) return 0;
    for(int i=0;i<=e->inUso;i++){
        if (e->equiplist[i]==NULL) return i;
    }
    return -1;
}
link newNode(PG Pg,link next);
 static char* creaCodice(LIST list);

link newNode(PG Pg,link next){
    link x=malloc(sizeof *x);
    if(x==NULL)return NULL;
    x->value =Pg;
    x->next=next;
    return x;
}
LIST initPgList(char *filename){//inserimento in testa
    FILE *fp;
    fp=fopen(filename,"r");
    LIST List=malloc(sizeof(*List));
    List->head=newNode(loadPg(fp),NULL);
    List->tail=List->head;
    int flag=0;
    if(checkValidPg(List->head->value)==0) return NULL;
    else flag=1;
    while(flag!=0){
        PG t=loadPg(fp);
        flag=checkValidPg(t);
        if(flag!=0)
        List->head=newNode(t,List->head);
    }
    List->N=lenListPg(List);
    return List;
}
LIST DelPg(char *codice ,LIST list){
    link x,p;
    if ((list->head)==NULL) return NULL;
    for(x=list->head,p=NULL;x!=NULL;p=x,x=x->next){
        if(KEYcompare(codice,KEYget(x->value))==0)

        {
            if(x==list->head){
                list->head=x->next;
            }
            else if(x==list->tail){
                list->tail=p;


            }
            else{
                p->next=x->next;

            }
            free(x);
            break;
        }

    }
    return list;
}
PG loadPg(FILE *fp){
    PG t=malloc(sizeof(struct pg));
    //if(fscanf(fp,"%s %s %s %d %d %d %d %d %d",(t.codice),(t.nome),(t.classe),&t.stat.hp,&t.stat.mp,&t.stat.atk,&t.stat.def,&t.stat.mag,&t.stat.spr)==9);
    if(fscanf(fp,"%s %s %s",(t->codice),(t->nome),(t->classe))==3){
        t->stat=riempi_stat(fp);
        t->equip=initEquip();
    }
    else t=nullPg();
    return t;
}
int lenListPg(LIST list){
    link x;
    int cnt=0;
    for(x=list->head;x!=NULL;x=x->next,cnt++);
    return cnt;

}
EQUIP initEquip(){
    EQUIP e=malloc(sizeof(*e));
    e->inUso=0;
    e->equiplist=calloc(MAX_OBJ_INV,sizeof(ITEM));
    return e;
}
PG createPg(LIST list){
    PG t=malloc(sizeof(*t));

    list->N=lenListPg(list);
    strcpy(t->codice,creaCodice(list));
    printf("inserisci nome: ");
    scanf("%s",t->nome);
    printf("inserisci classe: ");
    scanf("%s",t->classe);
    t->stat=creaStat();
    t->equip=initEquip();
    return t;
}
PG nullPg(){
    PG t=malloc(sizeof(struct pg));
    strcpy(t->nome,"\0");
    strcpy(t->codice,"\0");
    strcpy(t->classe,"\0");
    t->stat=nullStat();
    return t;
}
 int checkValidPg(PG Pg){
     return strcmp(Pg->codice,"\0");
 }
LIST addPg(LIST list,PG Pg){
     if (checkValidPg(Pg)!=0) {
         list->head=newNode(Pg,list->head);
     }
     return list;
 }
 char *itoa(int num, char *str,int _Radix)
{
        if(str == NULL)
        {
                return NULL;
        }
        sprintf(str, "%d", num);
        return str;
}
 char* creaCodice(LIST list){
    char codice[LEN_CODICE]="PG";
    char num[MAX_PG];
    //assegna in automatico il numero al pg (migliorabile calcolando potenza di 10)
    if ((list->N)<=9 && (list->N)>=0) strcat(codice,"000");
    else if ((list->N)>=10 && (list->N)<=99) strcat(codice,"00");
    else if ((list->N)>=100 && (list->N)<=999) strcat(codice,"0");
    list->N++;
    itoa(list->N,num,10);
    
    strcat(codice,num);
    return strdup(codice);
 }
 void addObjToPg(char *nome_ogg,char *nome_pers,LIST list,tab_inv_p inv){
     ITEM ToBeAdd=searchObj_byName(inv,nome_ogg);
     if(checkNullItem(ToBeAdd)){
         printf("errore oggetto non trovato!\n");
         return;
     }
     link x;
     for(x=list->head;x!=NULL;x=x->next){
         if(KEYcompare(getName(x->value),nome_pers)==0){
             int pos=getFreeSlotIndex(x->value->equip);
             if(pos!=-1){
             x->value->equip->equiplist[pos]=ToBeAdd;
             x->value->equip->inUso++;
             printf("%s inserito nell'equipaggiamento di %s\n",nome_ogg,nome_pers);   
             }
             else printf("equipaggiamento pieno\n");
             break;
         }
     }
     return;
 }
 int findObjInEquip(EQUIP e,char *nome_ogg){
     for(int i=0;i<e->inUso;i++){
         if(KEYcompare(getObjName(e->equiplist[i]),nome_ogg)==0)
         return i;
     }
     return -1;
 }
 void delObjFromPg(char *nome_ogg,char *nome_pers,LIST list,tab_inv_p inv){
     ITEM ToBeDel=searchObj_byName(inv,nome_ogg);
     if(checkNullItem(ToBeDel)){
         printf("errore oggetto non trovato!\n");
         return;
     }
     link x;
     for(x=list->head;x!=NULL;x=x->next){
         if(KEYcompare(getName(x->value),nome_pers)==0){
             int pos=findObjInEquip(x->value->equip,nome_ogg);
             if(pos!=-1){
             x->value->equip->equiplist[pos]=NULL;
             x->value->equip->inUso--;
             printf("%s eliminato dall'equipaggiamento di %s\n",nome_ogg,nome_pers);   
             }
             else printf("oggetto non presente nell'equipaggiamento di %s!\n",x->value->nome);
             break;
         }
     }
     return;
 }

void freePgList(LIST pgList){
    link x,t;
    for (x=pgList->head;x!=NULL;x=t){
        t=x->next;
        free(x);
    }
}
 PG getPg(char *codPg,LIST list){
     link x;
     for(x=list->head;x!=NULL;x=x->next){
         if(KEYcompare(KEYget(x->value),codPg)==0) return x->value;
     }
     return nullPg();
 }



 
 void calcolaStat(char *c_p,LIST list,tab_inv_p inv){
     PG pg=getPg(c_p,list);//da scrivere
     STAT t=pg->stat;
    for(int i=0;i<getDimEquip(pg->equip);i++){
        t=updateStat(t,pg->equip->equiplist[i]);
    }
    printf("statistiche di %s:\n",pg->nome);
    printStat(t);//da scrivere in modo che sia 0 se stat<0
 }
 