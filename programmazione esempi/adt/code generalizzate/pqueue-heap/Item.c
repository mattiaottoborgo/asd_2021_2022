#include "Item.h"
#include "stdlib.h"
#include "stdio.h"

int getKey(Item i){//priorità
    return i.key;
}
int getId(Item i){
    return i.val;
}
void ITEMstore(Item i){
    printf("%d %d",i.val,i.key);
}
int KEYcmp(int k1,int k2){
    if(k1>k2)return 1;
    else if(k1<k2)return -1;
    else return 0;
}
int IDcmp(int id1,int id2){
    if(id1>id2)return 1;
    else if(id1<id2)return -1;
    else return 0;
}