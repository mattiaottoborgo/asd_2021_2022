#include "stdio.h"
#include "stdlib.h"
#define N 3
int main(){
    int val[N]={1,2,3};
    int *sol=malloc(N*sizeof(int));
    int m=3;
    Er_alg(val,0,N,sol,0);
}

void Er_alg(int *val, int m, int n,int *sol ,int pos){
    int i,j;
    if(pos>=n){ //stampi per ogni partizione i numeri
        for(i=0;i<m;i++){//ciclo partizioni.
            printf("{ ");
            for(j=0;j<n;j++)//ciclo elementi delle partizioni.
                if (sol[j]==i) printf("%d ",val[j]); 
            printf("}"); 
        }
        printf("\n");
        return;
    }
    for(i=0;i<m;i++){
        sol[pos]=i; //salvo indice partizione dell'elemento pos-esimo.
        Er_alg(val,m,n,sol,pos+1);
    }
    sol[pos]=m;
    Er_alg(val,m+1,n,sol,pos+1);
    return;
}