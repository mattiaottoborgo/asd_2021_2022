#include "Item.h"

int GETindex(Key k){
    int i;
    i=k-'a';
    return i;
}
Key KEYget(Item val){
    return val.key;
}
Item ITEMsetvoid(){
    Item tmp;
    tmp.key='.';
    tmp.value=-1;
    return tmp;
}
int KEYcmp(Key k1,Key k2){
    if(k1>k2) return 1;
    else if(k1==k2) return 0;
    else if(k1<k2) return -1;
}
void ITEMstore(Item i){
    printf("Key: %c value: %d\n",i.key,i.value);
}
//ritorna 1 se vuoto
int ITEMcheckvoid(Item item){
    int result=KEYcmp(KEYget(item),'.');
    return !result;
}
Item createItem(Key k,int value){
    Item tmp;
    tmp.key=k;
    tmp.value=value;
    return tmp;
}