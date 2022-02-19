#include "Item.h"

Item ITEMsetNull(){
    Item tmp;
    tmp.k=-1;
    tmp.value=-1;
    return tmp;
}
void ITEMstore(Item item){
    printf("%d %d\n",item.value,item.k);
}
int KEYcmp(Key k1,Key k2){
    if (k1<k2) return -1;
    else if(k1>k2) return 1;
    return 0;
}
Key KEYget(Item item){
    return item.k;
}