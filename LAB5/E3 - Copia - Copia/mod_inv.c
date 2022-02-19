#include "mod_inv.h"
#define MAX_INV 100
item* init_list_inv(char* filename,int *n_inv){
    FILE *fp;
    fp=fopen(filename,"r");
    fscanf(fp,"%d",n_inv);
    item* lista_inv=(item*) malloc((*n_inv)*sizeof(item));
    for(int i=0;i<*n_inv;i++){
        item tmp;
        fscanf(fp,"%s %s",&tmp.nome,&tmp.tipo);
        tmp.stat=riempi_stat(fp);
        lista_inv[i]=tmp;
    }
    return lista_inv;
}
item nullItem(){
    item t;
    strcpy((t.nome),"NULL");
    strcpy((t.tipo),"NULL");
    t.stat=nullStat();
    return t;

}
Stat nullStat(){
    Stat t;
    t.hp=INT_MAX;
    t.mp=INT_MAX;
    t.atk=INT_MAX;
    t.def=INT_MAX;
    t.mag=INT_MAX;
    t.spr=INT_MAX;
    return t;
}

Stat riempi_stat(FILE *fp){
    Stat tmp;
    fscanf(fp,"%d %d %d %d %d %d",&tmp.hp,&tmp.mp,&tmp.atk,&tmp.def,&tmp.mag,&tmp.spr);
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
item searchObj_byName(tab_inv_p t,char *name){
    item Item=nullItem();
    item *vett_inv=t->vett_inv;
    for(int i=0;i<t->n_inv;i++){
        if(strcmp(name,vett_inv[i].nome)){
            Item=vett_inv[i];
            break;
        } 
        return  vett_inv[i];
    }
}
void printObjInfo(item Item){
    printf("nome : %s\n",Item.nome);
    printf("tipo : %s\n",Item.tipo);
    printStat(Item.stat);

}
void printStat(Stat stat){
    printf("hp: %d, mp; %d, atk: %d\n",stat.hp,stat.mp,stat.atk);
    printf("def:%d, mag: %d, spr: %d\n",stat.def,stat.mag,stat.spr);
}
