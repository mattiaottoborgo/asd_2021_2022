#include "stdlib.h"
#include "stdio.h"

#ifndef ITEM_HEADER
#define ITEM_HEADER
typedef char Key;
typedef struct item {
    Key key;
    int value;
}Item;

int GETindex(Key k);
Key KEYget(Item val);
Item ITEMsetvoid();
Item createItem(Key k,int value);
void ITEMstore(Item i);
int KEYcmp(Key k1,Key k2);
int ITEMcheckvoid(Item item);
#endif