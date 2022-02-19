#include "stack.h"
#include "stdio.h"
#include "stdlib.h"
#define L 10
int main(){
    Item i1;
    Item i2;
    i1.value=1;
    i1.code=1;
    i2.value=13;
    i2.code=2;
    STACK s=STACKinit(10);
    STACKpush(s,i1);
    STACKpush(s,i2);
    Item tmp;
    tmp=STACKpop(s);
    printf("stack vuoto: %d\n",STACKempty(s));
    tmp=STACKpop(s);
    printf("stack vuoto: %d\n",STACKempty(s));


}