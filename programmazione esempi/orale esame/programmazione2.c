#define DIM 3
#include "string.h"
#include"stdlib.h"
void initvect(char **vett,char ***a,char ***b);
int check(char *string);
void divideConsVoc(char **vett,char ***a,char ***b);
int main(){

    char **a;
    char **b;
    char *vett[DIM]={"aiuola","cadavere","ultra"};
    initvect(vett,&a,&b);
    divideConsVoc(vett,&a,&b);
    return 0;
}
int check(char *string){
    char *vocals="aeiou";
    char*p=vocals;
    while((*p!='\0')){
        if((*p)==*string)return 0;
        p++;
    }
    return 1;
}
void initvect(char **vett,char ***a,char ***b){
    int dim_a=0;
    int dim_b=0;

    for(int i=0;i<DIM;i++){
        if(check(vett[i])==0)// vocali
            dim_a+=strlen(vett[i]);
        else dim_b+=strlen(vett[i]);
            }
    (*a)=malloc(dim_a*sizeof(char*));
    (*b)=malloc(dim_b*sizeof(char*));
}
void divideConsVoc(char **vett,char ***a,char ***b){
    int j=0,k=0;
    for(int i=0;i<DIM;i++){
        if(check(vett[i])==0)// vocali
            (*a)[j++]=strdup(vett[i]);
        else (*b)[k++]=strdup(vett[i]);
            }
}