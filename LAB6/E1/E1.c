#include "stdlib.h"
#include "stdio.h"
#define file "att.txt"
typedef struct {
    int s;
    int f;
    int d;
}att;
int NoSov(att a1,att a2);
void printSolution(att* lista, int*P,int last);
int main(){

    FILE *fp;
    fp=fopen(file,"r");
    int length;
    
    fscanf(fp,"%d",&length);
    length++;
    //inizializzo strutture dati
    att* lista_att=malloc(length*sizeof(att));
    int* L=malloc(length*sizeof(int)); //contiene le lunghezze fino a quella cella
    int* P=malloc(length*sizeof(int)); //contiene il precedente di quella cella
    int* maxval=calloc(length,sizeof(int));
    int last=0;
    int ris=1;
    for(int i=0;i<length;i++){
        fscanf(fp,"%d %d",&lista_att[i].s,&lista_att[i].f);
        lista_att[i].d=lista_att[i].f-lista_att[i].s;
    }
    //inizializzo primi valori
    L[0]=lista_att[0].d;
    P[0]=-1;
    int max=0;
    int i,j;
    for(i=0;i<length;i++){//faccio crescere lunghezza del sottoproblema
        L[i]=lista_att[i].d;
        P[i]=-1;
        //confronto con le attività considerate fino a quel momento
        for(j=0;j<i;j++){
            if(NoSov(lista_att[j],lista_att[i])==1 && max<lista_att[i].d+L[j]) 
            {
                L[i]=L[j]+lista_att[i].d;
                last=i;
                max=L[i];
                P[i]=j;
            }
        }


    }
     printSolution(lista_att,P,last);

    return 1;
}
int NoSov(att a1,att a2){
    int s=!( (a2.s<a1.f) && (a1.s<a2.f));
    return s;
}
void printAtt(att a){
    printf("{(%d,%d): %d} ",a.s,a.f,a.d);
}
void printSolution(att* lista, int*P,int i){
    if(P[i]==-1){
    printAtt(lista[i]);
    return;
    }
    printSolution(lista,P,P[i]);
    printAtt(lista[i]);
}

