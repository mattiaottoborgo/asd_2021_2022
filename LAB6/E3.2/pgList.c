#include "pgList.h"

typedef struct node_pg *link;
struct node_pg{
    pg_t pg;
    link next;
};

link newNode(pg_t val,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)return NULL;
    x->pg=val;
    x->next=next;
    return x;
}
struct pgList_s{
    link head;
    link tail;
};
pgList_t pgList_init(){
    pgList_t pgList=malloc(sizeof(*pgList));
    pgList->head=NULL;
    pgList->tail=NULL;
    return pgList;
}

void pgList_read(FILE *fp, pgList_t pgList){
    int end_file=0;
    while(end_file==0){
        pg_t tmp_pg;
        int success=pg_read(fp,&tmp_pg);
        if(success){
            pgList->head=newNode(tmp_pg,pgList->head);
        }
        else end_file=1;
    }
}
void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray){
    link x;
    for(x=pgList->head;x!=NULL;x=x->next){
        pg_print(fp,&x->pg,invArray);
    }
}
void pgList_insert(pgList_t pgList, pg_t pg){
    pgList->head=newNode(pg,pgList->head);
}
pg_t *pgList_searchByCode(pgList_t pgList, char* cod){
    link x;
    for(x=pgList->head;x!=NULL;x=x->next){
        if(strcmp(x->pg.cod,cod)==0){
            return &(x->pg);
        }
    }
}
void pgList_remove(pgList_t pgList, char* cod){
    link x,t,p;
    for(x=pgList->head,p=NULL;x!=NULL;p=x,x=x->next){
        if(strcmp(x->pg.cod,cod)==0){
           if(x==pgList->head){
               t=pgList->head->next;
               free(x);
               pgList->head=t;
           }
           else{
               p->next=x->next;
               free(x);
           }
        break;
        }
    }
}
void pgList_free(pgList_t pgList){
    link x,t;
    for(x=pgList->head;x!=NULL;x=t){
        t=x->next;
        free(x);
    }
}