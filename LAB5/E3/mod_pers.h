
#ifndef _MOD_PERS_HEADER
#define _MOD_PERS_HEADER
#include <stdio.h>
#include <stdlib.h>
#include "mod_inv.h"
#define LEN_CODICE 50
#define MAX_PG 4 //indica su quante cifre si può sviluppare il conteggio dei pg
typedef struct equip *EQUIP;

typedef struct pg *PG;
typedef struct list *LIST;
LIST initPgList(char *filename);
LIST DelPg(char *codice ,LIST list);
PG loadPg(FILE *fp);
PG nullPg();
PG createPg(LIST list);
int checkValidPg(PG Pg);
int lenListPg(LIST head);
LIST addPg(LIST head,PG Pg);
EQUIP initEquip();
void calcolaStat(char *n_p,LIST list,tab_inv_p inv);
void addObjToPg(char *nome_ogg,char *nome_pers,LIST list,tab_inv_p inv);
void delObjFromPg(char *nome_ogg,char *nome_pers,LIST list,tab_inv_p inv);
void freePgList(LIST pgList);
#endif