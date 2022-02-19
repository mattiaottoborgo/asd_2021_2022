#ifndef ITEM_HEADER
#define ITEM_HEADER
#include "string.h"
#include "stdio.h"
typedef int Key;
typedef struct{int value; Key k; }Item;
Item ITEMsetNull();
void ITEMstore(Item item);
int KEYcmp(Key k1,Key k2);
Key KEYget(Item item);
#endif