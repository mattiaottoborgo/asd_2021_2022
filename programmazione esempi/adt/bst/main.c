#include "BST.h"
#include "Item.h"
int main(){
    Item item1; item1.value=1; item1.k=1;
    Item item2; item2.value=2; item2.k=2;
    Item item3; item3.value=3; item3.k=3;
    Item item4; item1.value=4; item4.k=4;
    Item item5; item5.value=5; item5.k=5;
    BST bst=BSTinit();
    BSTinsert_root(bst,item1);
    BSTinsert_root(bst,item2);
    BSTinsert_root(bst,item3);
    BSTinsert_root(bst,item4);
    BSTinsert_root(bst,item5);
    BSTvisit(bst,PREORDER);
}