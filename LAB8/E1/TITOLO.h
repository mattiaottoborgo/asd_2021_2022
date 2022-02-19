#ifndef TITOLO_HEADER
#define TITOLO_HEADER
#define MAXC 20+1
 #include "QUOTA.h"

typedef struct titolo *TITOLO;
typedef struct bst *BST;
void BST_insert(BST bst,Quota x);
BST BSTinit();
TITOLO TITOLOinit(char nome[MAXC],int n_transazioni);
TITOLO TITOLOnull();
int TITOLOcheckNull(TITOLO titolo);
char* TITOLOgetname(TITOLO titolo);
void TITOLOupdateQuote(TITOLO titolo, Data k,int valore,int n_scambi);
Quota TITOLOgetQuota(TITOLO titolo,Data data);
Quota TITOLOgetIntervallminQUOTA(TITOLO titolo,Data data_i,Data data_f);
Quota TITOLOgetIntervallmaxQUOTA(TITOLO titolo,Data data_i,Data data_f);
Quota TITOLOgetminQUOTA(TITOLO titolo);
Quota TITOLOgetmaxQUOTA(TITOLO titolo);
void TITOLObalance(TITOLO titolo,float S);
#endif 