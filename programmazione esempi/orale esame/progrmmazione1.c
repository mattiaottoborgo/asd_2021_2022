////scrivere ina fin

#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#define MAXCHAR 40
typedef struct node *link;
struct node{
    char substring[MAXCHAR];
    link next;
};
void parse(char *string,char DELIMITER);
int main(){
   char string[MAXCHAR]="ciao,bello,come,stai";
   parse(string,',');

   
}
link NEW(char *substring,link next){
    link x=malloc(sizeof(*x));
    if(x==NULL)return NULL;
    strcpy(x->substring,substring);
    x->next=next;
    return x;
}
void parse(char *string,char DELIMITER){
    char *p=string,*oldp=p;
    char tmp[MAXCHAR];
    link head=NULL;
    while((*p)!='\0'){
        if((*p)==DELIMITER){
            strncpy(tmp,oldp,p-oldp);
            head=NEW(tmp,head);
            oldp=++p;
        }
        else p++;
    }
    if((*p)=='\0'){
        strncpy(tmp,oldp,p-oldp);
        head=NEW(tmp,head);
        }
    return;
}