#include "stdlib.h"
#include "stdio.h"
#define N 4
#define K 2
int disp_semp(int pos,int *val, int *sol, int *mark, int n, int k,int cnt);
int main(){
    int val[N]={1,2,3,4};
    int val2[2]={0,1};
    int *sol=malloc(N*sizeof(int));
    int *mark=calloc(N,sizeof(int));
    int mark2[4]={2,1,1,1};
    int cnt=0;
    //printf("numero di disposizioni semplici : %d",disp_semp(0,val,sol,mark,N,K,cnt));
    //printf("numero di disposizioni ripetute : %d",disp_rip(0,4,2,val2,sol,cnt));
    //printf("numero di permutazioni semplici: %d",perm_semp(0,N,val,sol,mark,cnt));
    //printf("numero di permutazioni ripetute: %d",perm_rip(0,5,4,val,sol,mark2,cnt));
    //printf("numero di combinazioni semplici: %d",comb_semp(0,0,N,2,val,sol,cnt));
    printf("numero di combinazioni ripetute: %d",comb_rip(0,0,N,2,val,sol,cnt));





}
int disp_semp(int pos,int *val, int *sol, int *mark, int n, int k,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=val[i];
            cnt=disp_semp(pos+1,val,sol,mark,n,k,cnt);
            mark[i]=0;
        }
    }
    return cnt;

}
int disp_rip(int pos,int k,int n, int *val, int *sol,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;

    }
    for(i=0;i<n;i++){
        sol[pos]=val[i];
        cnt=disp_rip(pos+1,k,n,val,sol,cnt);
    }
    return cnt;
}
int perm_semp(int pos,int n, int *val,int *sol,int *mark,int cnt){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=val[i];
            cnt=perm_semp(pos+1,n,val,sol,mark,cnt);
            mark[i]=0;
        }
    }
    return cnt;
}
int perm_rip(int pos,int n,int n_dist, int *val_dist, int *sol, int *mark, int cnt){
    int i;
    if(pos>=n){
        for(int i=0;i<n;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n_dist;i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=val_dist[i];
            cnt=perm_rip(pos+1,n,n_dist,val_dist,sol,mark,cnt);
            mark[i]++;
        }
    }
    return cnt;
}
int comb_semp(int pos,int start, int n,int k,int *val, int *sol,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++){
            printf("%d ",sol[i]);
        }
        printf("\n");
        return cnt+1;


    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt=comb_semp(pos+1,i+1,n,k,val,sol,cnt);
    }
    return cnt;
}
int comb_rip(int pos,int start,int n,int k, int *val, int *sol,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt=comb_rip(pos+1,i,n,k,val,sol,cnt);
        start++;
    }
    return cnt;
}