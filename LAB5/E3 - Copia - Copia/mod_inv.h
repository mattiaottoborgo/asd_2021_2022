
#ifndef _MOD_INV_HEADER
#define _MOD_INV_HEADER
#define MAX_C 50+1
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "limits.h"
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
}Stat;

typedef struct {
    char nome[MAX_C];
    char tipo[MAX_C];
    Stat stat;

}item;
 typedef struct tab_inv {
    item* vett_inv;
    int n_inv;
    int max_inv;
}tab_inv,*tab_inv_p;

item* init_list_inv(char* filename,int *n_inv);
Stat riempi_stat(FILE *fp);
tab_inv_p createTab(char *filename);
item searchObj_byName(tab_inv_p t,char *name);
void printObjInfo(item Item);
void printStat(Stat stat);


//stat function
Stat nullStat();


//item function
item nullItem();
#endif