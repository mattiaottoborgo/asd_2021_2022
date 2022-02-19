#include "TITOLI.h"
typedef struct node *link;
struct node{
    TITOLO titolo;
    link next;
};
struct list{
    int n_titoli;
    link head;
};
LIST loadCollection(FILE *fp);
static link NewNode(char *nome,link next){
    link x=malloc(sizeof(*x));
    x->titolo=TITOLOinit(nome,0);
    x->next=next;
    return x;
}
LIST loadCollection(FILE *fp){
    LIST list=malloc(sizeof*list);
    list->n_titoli=0;
    list->head=NULL;
    char nome[MAXC];
    int n_transazioni,n_titoli;
    fscanf(fp,"%d",&n_titoli);
    for(int i=0;i<n_titoli;i++){
        fscanf(fp,"%s %d",nome,&n_transazioni);
        list->head=NewNode(nome,list->head);
        list->n_titoli++;
        int giorno,mese,anno,valore,n_scambi;
        for(int j=0;j<n_transazioni;j++){
            fscanf(fp,"%d/%d/%d %*d:%*d %d %d",&anno,&mese,&giorno,&valore,&n_scambi);
            TITOLOupdateQuote(list->head->titolo,DATAcreate(anno,mese,giorno),valore,n_scambi);
        }
    }
    return list;
}
TITOLO TITOLOsearch(LIST list,char*nome){
    link x;
    for(x=list->head;x!=NULL;x=x->next){
        if(strcmp(TITOLOgetname(x->titolo),nome)==0)return x->titolo;
    }
    return TITOLOnull();
}