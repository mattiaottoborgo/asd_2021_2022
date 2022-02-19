#include "invArray.h"
struct invArray_s{
    inv_t*lista_inv;
    int length_list;
};

invArray_t invArray_init(){
    invArray_t Array_inv=malloc(sizeof(*Array_inv));
    Array_inv->length_list=0;
    return Array_inv;
}
void invArray_read(FILE *fp, invArray_t invArray){
    fscanf(fp,"%d",&invArray->length_list);
    invArray->lista_inv=malloc(invArray->length_list*sizeof(inv_t));
    for(int i=0;i<invArray->length_list;i++){
        inv_t tmp;
        //leggo oggetto e lo metto in tmp
        inv_read(fp,&tmp);
        invArray->lista_inv[i]=tmp;
    }
}
void invArray_print(FILE *fp, invArray_t invArray){
    for(int i=0;i<invArray->length_list;i++){
        inv_print(fp,&(invArray->lista_inv[i]));
    }
}
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index){
    inv_print(fp,invArray_getByIndex(invArray,index));
}


inv_t *invArray_getByIndex(invArray_t invArray, int index){
    if(index<invArray->length_list)
        return &(invArray->lista_inv[index]);
    else {
        return void_inv();
        }
}
int invArray_searchByName(invArray_t invArray, char *name){
    for(int i=0;i<invArray->length_list;i++){
        if(strcmp(invArray->lista_inv[i].nome,name)==0) return i;
    }
    return -1;
}