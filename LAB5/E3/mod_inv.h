
#ifndef _MOD_INV_HEADER
#define _MOD_INV_HEADER
#define MAX_C 50+1
#define MAX_OBJ_INV 8
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "limits.h"
typedef struct stat *STAT;
typedef struct item *ITEM;
 typedef struct tab_inv {
    ITEM vett_inv;
    int n_inv;
    int max_inv;
}tab_inv,*tab_inv_p;

ITEM init_list_inv(char* filename,int *n_inv);
STAT riempi_stat(FILE *fp);
STAT creaStat();
tab_inv_p createTab(char *filename);
ITEM searchObj_byName(tab_inv_p t,char *name);
void printObjInfo(ITEM Item);
void printStat(STAT stat);
void freeStat();
int checkNullItem(ITEM i);
char *getObjName(ITEM i);

//stat function
STAT nullStat();
STAT updateStat(STAT t,ITEM i);

//item function
ITEM nullItem();
#endif