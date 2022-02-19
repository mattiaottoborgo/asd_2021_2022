#ifndef ITEM_HEADER
#define ITEM_HEADER


typedef struct item{
    int val;
    int key;
}Item;
int getKey(Item i);
void ITEMstore(Item i);
int KEYcmp(int k1,int k2);
#endif