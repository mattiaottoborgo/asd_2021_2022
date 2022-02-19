#define K 4
#include "stdio.h"
#include "stdlib.h"
int powerset_divide_impera(int pos, int *val, int *sol,int k ,int start, int cnt);
int powerset_disp_ripe(int pos, int*val, int *sol, int k,int cnt);
int powerset_r( int *val,int k,int *sol, int j, int pos, int start);
int main(){
    int v[K]={1,2,3,4};
    int sol[K];
    //int cnt = powerset_divide_impera(0,v,sol,K,0,cnt);
    //int cnt = powerset_disp_ripe(0,v,sol,K,cnt);
    int cnt = powerset_comb_s(v,K,sol);

}
//versione divide et impera --> vettore delle soluzioni viene riempito con gli elementi che costituiranno una delle soluzioni
int powerset_divide_impera(int pos, int *val, int *sol,int k ,int start, int cnt){
    //k-->numero elementi
    //start-->posizione a cui si è arrivato ad analizzare val
    //pos  -->indice corrente del vettore sol
    int i;
    if(start>=k){ // terminazione: ho finito gli elementi
        printf("{");
        for(i=0; i<pos;i++) printf("%d ",sol[i]); //stampa soluzione
        printf("}");
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<k;i++){
        sol[pos]=val[i];
        cnt=powerset_divide_impera(pos+1,val,sol,k,i+1,cnt);
    }
    cnt=powerset_divide_impera(pos,val,sol,k,k,cnt); // non aggiungere nulla e ricorri
    return cnt;
}
//versione disposizioni ripetute--> vettore soluzione corrisponde a "combinazioni" di numeri che prendi, quindi per ogni 
//elemento indichi se lo prendi o no.
int powerset_disp_ripe(int pos, int*val, int *sol, int k,int cnt){
    int j;
    if (pos>=k){
        printf("{");
        for(j=0;j<k;j++)
            if(sol[j]!=0) printf("%d ",val[j]);
        printf("}\n");
        return cnt+1;
    }
    sol[pos]=0;
    cnt=powerset_disp_ripe(pos+1,val,sol,k,cnt);
    sol[pos]=1;
    cnt=powerset_disp_ripe(pos+1,val,sol,k,cnt);
    return cnt;
}
//versione combinazioni semplici--> ogni volta
int powerset_comb_s(int *val, int k, int *sol){
    int cnt=0,j;
    printf("{ }\n"); // insieme vuoto
    cnt++;
    for(j=1;j<=k;j++){
        cnt+= powerset_r(val,k,sol,j,0,0);
    }
    return cnt;
}

int powerset_r( int *val,int k,int *sol, int j, int pos, int start){
    int cnt=0,i;
    if(pos==j){
        printf("{ ");
        for(i=0; i<j;i++)   printf("%d ", sol[i]);
        printf("}\n");
        return 1;
    }
    for(i=start;i<k;i++){
        sol[pos]=val[i];
        cnt+= powerset_r(val,k,sol,j,pos+1,i+1);
        }
    return cnt;
}

