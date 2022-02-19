
#ifndef _MOD_PERS_HEADER
#define _MOD_PERS_HEADER

#include "mod_inv.h"
#define LEN_CODICE 50
#define MAX_PG 4 //indica su quante cifre si può sviluppare il conteggio dei pg
typedef struct{
 int null;
 //todo metti valori corretti
}Equip;

typedef struct{
    char codice[LEN_CODICE];
    char nome[MAX_C];
    char classe[MAX_C];
    Equip equip;
    Stat stat;  
}pg;
typedef struct node *link;
struct node{
    pg value;
    link next;
};
link newNode(pg Pg,link next);
link initPgList(char *filename);
Stat creaStat();
pg loadPg(FILE *fp);
pg nullPg();
pg createPg(int *N_pg);
int checkValidPg(pg Pg);
int lenListPg(link head);
link addPg(link head,pg Pg);

#endif