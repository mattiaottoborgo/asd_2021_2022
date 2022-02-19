//versione con vettore

#ifndef STV2_HEADER
#define STV2_HEADER
#include "Item.h"
#define ST_IN_ORDER 1
#define ST_NOT_IN_ORDER 0
typedef struct symbtab *ST;
ST STinit(int maxN);
void STfree(ST st);
int STcount(ST st);
void STinsert(ST st, Item val);
Item STsearch( ST st,Key k);
void STdelete(ST st,Key k);
#if ST_IN_ORDER
Item STselect(ST st, int r);
#endif
void STdisplay(ST st); 
#endif