//#include "Stv1.h"
//#include "STv2.h"
#include "STv3.h"
#include "Item.h"
#include "stdlib.h"
int main(){
    Item item1=createItem('a',1);
    Item item2=createItem('d',2);
    Item item4=createItem('b',4);
    ST st=STinit(26);
    STinsert(st,item1);
    STinsert(st,item2);
    STinsert(st,item4);
    STdisplay(st);
   // Item found=STselect(st,3);
    //ITEMstore(found);
    printf("\n");
    Item found=STsearch(st,'b');
    ITEMstore(found);
    printf("\n");
    STdelete(st,'b');
    STdisplay(st);
}