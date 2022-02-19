#include "mod_inv.h"
#define MAX_INV 100

struct item{
    char nome[MAX_C];
    char tipo[MAX_C];
    STAT stat;

};
struct stat{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
};
ITEM init_list_inv(char* filename,int *n_inv){
    FILE *fp;
    fp=fopen(filename,"r");
    fscanf(fp,"%d",n_inv);
    ITEM lista_inv= malloc((*n_inv)*sizeof(*lista_inv));
    for(int i=0;i<*n_inv;i++){
        ITEM tmp=malloc(sizeof(*tmp));
        fscanf(fp,"%s %s",tmp->nome,tmp->tipo);
        tmp->stat=riempi_stat(fp);
        lista_inv[i]=*tmp;
    }
    return lista_inv;
}
ITEM nullItem(){
    ITEM t=malloc(sizeof(*t));
    strcpy((t->nome),"NULL");
    strcpy((t->tipo),"NULL");
    t->stat=nullStat();
    return t;

}
char *getObjName(ITEM i){
    return i->nome;
}
int checkNullItem(ITEM i){ //1 se vuoto,
    return !(strcmp(i->nome,"NULL") && strcmp(i->tipo,"NULL"));
}
STAT nullStat(){
    STAT t=malloc(sizeof(*t));
    t->hp=INT_MAX;
    t->mp=INT_MAX;
    t->atk=INT_MAX;
    t->def=INT_MAX;
    t->mag=INT_MAX;
    t->spr=INT_MAX;
    return t;
}

STAT creaStat(){
     STAT t=nullStat();
     printf("inserisci hp: ");
     scanf("%d",&t->hp);
     printf("inserisci mp: ");
     scanf("%d",&t->mp);
     printf("inserisci atk: ");
     scanf("%d",&t->atk);
     printf("inserisci def: ");
     scanf("%d",&t->def);
     printf("inserisci mag: ");
     scanf("%d",&t->mag);
     printf("inserisci spr: ");
     scanf("%d",&t->spr);
     return t;
 }

STAT riempi_stat(FILE *fp){
    STAT tmp=malloc(sizeof(*tmp));
    fscanf(fp,"%d %d %d %d %d %d",&tmp->hp,&tmp->mp,&tmp->atk,&tmp->def,&tmp->mag,&tmp->spr);
    return tmp;
}
tab_inv_p createTab(char *filename){
    tab_inv_p x=malloc(sizeof *x);
    int n_inv;
    if (x==NULL)return NULL;
    x->vett_inv=init_list_inv(filename,&n_inv);
    x->n_inv=n_inv;
    x->max_inv=MAX_INV;
    return x;
}
ITEM searchObj_byName(tab_inv_p t,char *name){//controlla se funziona
    ITEM Item=nullItem();
    ITEM vett_inv=t->vett_inv;
    for(int i=0;i<t->n_inv;i++){
        if(strcmp(name,t->vett_inv[i].nome)==0){
            Item=&t->vett_inv[i];
            break;
        } 
    }
    return  Item;
}
void printObjInfo(ITEM Item){
    printf("nome : %s\n",Item->nome);
    printf("tipo : %s\n",Item->tipo);
    printStat(Item->stat);

}
void printStat(STAT stat){
    printf("hp: ");
    if(stat->hp<0) printf("0, ");
    else printf("%d, ",stat->hp);
     printf("mp: ");
    if(stat->mp<0) printf("0, ");
    else printf("%d, ",stat->mp);
     printf("atk: ");
    if(stat->atk<0) printf("0, ");
    else printf("%d, ",stat->atk);
     printf("def: ");
    if(stat->def<0) printf("0, ");
    else printf("%d, ",stat->def);
     printf("mag: ");
    if(stat->mag<0) printf("0, ");
    else printf("%d, ",stat->mag);
     printf("spr: ");
    if(stat->spr<0) printf("0, ");
    else printf("%d, ",stat->spr);
    printf("\n");
}
STAT updateStat(STAT t,ITEM i){
    t->hp+=i->stat->hp;
    t->mp+=i->stat->mp;
    t->atk+=i->stat->atk;
    t->def+=i->stat->def;
    t->mag+=i->stat->mag;
    t->spr+=i->stat->spr;
    return t;
}
