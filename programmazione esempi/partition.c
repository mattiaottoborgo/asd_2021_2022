#include "stdlib.h"
#include "stdio.h"
#define K 3

int main(){
    int v[K]={1,2,3};
     int *sol = calloc(K, sizeof(int));
    //partition_disp_rip(0,v,sol,K,3);
    Er_alg(K,0,0,sol,v);


}

void partition_disp_rip(int pos ,int *val, int *sol, int n , int k){
    /*
    k--->numero di partizioni
    n--->numero di elementi in insieme S
    vettore val ---> contiene elementi dell'insieme S
    vettore sol ---> contiene in ogni cella la partizione a cui è associato l'i-esimo elemento di val
    vettore occ ---> contiene la cardinalità di ciascuna partizione
    ESEMPIO: partizione 0---> 1,4 ; partizione 1---->2; partizione 2------>3; (questa è una delle possibili soluzioni se  ho k=3 blocchi su un insieme di n=4 elementi)
        val : [1] [2] [3] [4]
        sol : [0] [1] [2] [0]
    /Riduco problema al seguente:
        1) disposizione di k elementi su un vettore di n celle
        2) in condizione di terminazione
            1)salvo in vettore occorrenze quante volte 
              è stata utilizzata ogni partizione
            2)ciclo su vettore occorrenze per vedere se ho utilizzato tutte le partizioni
            3)se occ[i]==0, allora non ho utilizzato tutte le partizioni e devo scartare la soluzione.
            4)altrimenti, la soluzione è valida e sol[i] contiene partizione a cui è associato val[i]  
    */
    int i,j,ok=1,*occ;
    if(pos>=n){
        occ=calloc(k,sizeof(int));
        for(j=0;j<n;j++) occ[sol[j]]++;
        i=0;
        while((i<k)&& ok){
            if(occ[i]==0) ok=0;
            i++;
        }
        free(occ);
        if(ok==0) return ;
        else{
            for(int z=0;z<n;z++){
                printf(" %d--->%d ",val[z],sol[z]);
            }
            printf("\n");
            return;
        }

    }
    for(i=0;i<k;i++){
        sol[pos]=i; // assegna l'elemento i-esimo di val  alla partizione pos-esima
        partition_disp_rip(pos+1,val,sol,n,k);
    }
}

void Er_alg(int n,int m, int pos, int *sol, int *val){
    //m--> numero di blocchi utlilizzabili al passo corrente
    //pos -->indice di scorrimento sugli n oggetti.
    int i,j;
    if(pos>=n){
        printf("partizione in %d blocchi: ", m);
        for(i=0;i<m;i++){
            printf("{ ");
            for(j=0;j<n;j++)
                if(sol[j]==i)
                    printf("%d ",val[j]);
            printf("} ");
        }
        printf("\n");
        return;
    }
    for(i=0;i<m;i++){
        sol[pos]=i;
        Er_alg(n,m,pos+1,sol,val);

    }
    sol[pos]=m; //elemento aggiunto all'ultimo blocco
    Er_alg(n,m+1,pos+1,sol,val);
}