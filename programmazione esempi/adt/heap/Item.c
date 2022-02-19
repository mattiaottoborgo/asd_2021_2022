#include "Item.h"
#include "stdlib.h"
#include "stdio.h"

int getKey(Item i){
    return i.key;
}
void ITEMstore(Item i){
    printf("%d %d",i.val,i.key);
}
int KEYcmp(int k1,int k2){
    if(k1>k2)return 1;
    else if(k1<k2)return -1;
    else return 0;
}