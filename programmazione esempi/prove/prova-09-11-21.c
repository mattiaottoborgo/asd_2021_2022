#include "stdio.h"
#include "stdlib.h"
int primi[2]={0,1};
int secondi[3]={2,3,4};
int dolci[2]={5,6};
typedef struct {
    int *scelte;
    int num_scelte;
}Livello;

int main(){
    Livello *livelli;
    int N=3;
    livelli=malloc(3*sizeof(Livello));
    int *sol=malloc(N*sizeof(int));
    Livello primo, secondo, dolce;
    primo.scelte=malloc(2*sizeof(int));
    secondo.scelte=malloc(3*sizeof(int));
    dolce.scelte=malloc(2*sizeof(int));
    for(int i=0;i<2;i++){
        primo.scelte[i]=primi[i];
    }
    for(int i=0;i<3;i++){
        secondo.scelte[i]=secondi[i];
    }
    for(int i=0;i<2;i++){
        dolce.scelte[i]=dolci[i];
    }
    primo.num_scelte=2;
    secondo.num_scelte=3;
    dolce.num_scelte=2;
    livelli[0]=primo;
    livelli[1]=secondo;
    livelli[2]=dolce;
    int cnt;
    cnt=princ_molt(livelli,N,sol,0,cnt);
    
     printf("\n");
}

princ_molt(Livello *livelli,int N, int*sol, int pos, int cnt){
    int i;
    if(pos>=N){
        for(i=0;i<N;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<livelli[pos].num_scelte;i++){
        sol[pos]=livelli[pos].scelte[i];
        cnt=princ_molt(livelli,N,sol,pos+1,cnt);
    }
    return cnt;
}