#ifndef ITEM_HEADER
#define ITEM_HEADER


typedef struct item{
    int val;
    int key;
}Item;
int getKey(Item i);
int getId(Item i);
void ITEMstore(Item i);
int IDcmp(int id1,int id2);
int KEYcmp(int k1,int k2);
#endif