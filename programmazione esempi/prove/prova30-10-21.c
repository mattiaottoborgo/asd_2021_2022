#include "stdlib.h"
#include "stdio.h"
#define K 4
void Er_alg(int pos ,int m, int n, int *sol, int *val);
int main(){
    int v[K]={1,2,3,4};
     int *sol = calloc(K, sizeof(int));
    //partition_disp_rip(0,3,sol,v,K);
    //Er_alg(0,0,K,sol,v);
    int cnt=0;
    //printf("insieme delle parti: %d",pwr1(0,v,sol,cnt,K,0));
    //printf("insieme delle parti: %d",pwr2(0,v,sol,cnt,K));
    printf("insieme delle parti: %d",pwr3(v,sol,K));


}


void Er_alg(int pos ,int m, int n, int *sol, int *val){
    int i,j;
    if(pos>=n){
        for(j=0;j<m;j++){ //ciclo tutte le partizioni
            printf("{ ");
            for(i=0;i<n;i++) 
                if(sol[i]==j) 
                    printf("%d ",val[i]);
            printf("} ");
        i=0;
        }
        printf("\n");
        return;


    }

    for(int i=0;i<m;i++){
        sol[pos]=i;
        Er_alg(pos+1,m,n,sol,val);
    }
    sol[pos]=m;
    Er_alg(pos+1,m+1,n,sol,val);
}
int pwr1(int pos,int *val,int*sol,int cnt,int n,int start){
    int i;
    if(start>=n){
        for(i=0;i<pos;i++){ //non devi stamparli tutti, percheè sol è sempere lungo n, ma te stampi solo fino al pos che ti è stato passato.
            if(sol[i]!=0) printf("%d",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt=pwr1(pos+1,val,sol,cnt,n,i+1);
    }
    cnt=pwr1(pos,val,sol,cnt,n,n);
    return cnt;

}
int pwr2(int pos ,int *val,int *sol, int cnt,int n){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++){
            if(sol[i]==1) printf("%d ",val[i]);
        }
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<2;i++){
        sol[pos]=i;
        cnt=pwr2(pos+1,val,sol,cnt,n);
    }
    return cnt;
}
int pwr3(int *val,int *sol,int n){
    int cnt=0,start=0;
    //ciclo su combinazioni semplici
    for(int i=0;i<=n;i++){
        cnt+=comb_semp(val,sol,0,0,n,i);
    }
    return cnt;
}
int comb_semp(int *val,int *sol, int pos, int start,int n,int k){
    int i,cnt=0;
    if(pos==k){
        for(i=0;i<k;i++) printf("%d ",sol[i]);
        printf("\n");
        return 1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt+=comb_semp(val,sol,pos+1,i+1,n,k);
    }
    return cnt;
}
void partition_disp_rip(int pos,int n,int *sol, int *val,int k){
    //k--> numero elememti in S
    //n--> numero di partizioni desiderate

    /*

    in sol salvo l'indice della partizione associata a quell'elemento
    */
    int i,j,ok=1,*occ;
    if (pos>=n){
        //creo vettore occorrenze
        occ=calloc(n,sizeof(int));
        for(j=0;j<k;j++) occ[sol[j]]++;
        j=0;
        while(j<n && ok){ //controllo se ho qualche partizione che non è mai uscita.
        //attenzione : cicli vettore delle occorrenze solo fino a numero di partixion idesisderate
            if(occ[j]==0) ok=0;
            j++;
        }
        if(ok==0) return;
        else{
            for (j=0;j<k;j++){
                printf("%d ---->%d ",val[j],sol[j]);
            }
            printf("\n");
            return;

        }

        ///terminazione
    }
    for(i=0;i<n;i++){
        sol[pos]=i;
        partition_disp_rip(pos+1,n,sol,val,k);
    }

}