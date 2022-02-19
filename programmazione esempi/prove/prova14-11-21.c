#include "stdlib.h"
#include "stdio.h"
#define N 4
#define K 3
int disp_semp(int *val,int *sol,int *mark,int cnt, int n,int k,int pos);
int compare (const void * a, const void * b);
int perm_rip(int *val,int n);
int disp_rip(int *val, int *sol,int cnt, int n,int k,int pos);
int perm_ripR(int *val,int *sol, int *mark,int pos, int n_dist,int n,int cnt);
int comb_semp(int *val,int *sol,int n,int k,int pos, int start,int cnt);
int comb_rip(int *val,int *sol,int n,int k, int pos, int start,int cnt);
int pwr_disp(int *val,int *sol,int n,int start,int pos, int cnt);
int pwr_R(int *val,int *sol,int n,int k,int pos, int start, int cnt);
int pwr(int *val,int n);
void part1(int *val,int *sol, int n,int k, int pos);
int main(){
    int cnt;
    int *sol=malloc(N*sizeof(int));
    int *mark=calloc(N,sizeof(int));
    int val[]={1,2,3,4};
    int val2[]={1,2,3,1};
    //cnt=perm_rip(val2,4);
    //cnt=disp_semp(val,sol,mark,cnt,N,K,0);
   // cnt=disp_rip(val,sol,cnt,N,K,0);
    //cnt=comb_rip(val,sol,N,4,0,0,cnt);
    //cnt=pwr_d(val,sol,N,0,0,cnt);
    //cnt=pwr_disp(val,sol,N,0,0,cnt);
    //cnt=pwr(val,N);
    part1(val,sol,N,3,0);

     return 0;


}

int disp_semp(int *val,int *sol,int *mark,int cnt, int n,int k,int pos){
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
            mark[i]++;
            sol[pos]=val[i];
            cnt=disp_semp(val,sol,mark,cnt,n,k,pos+1);
            mark[i]--;
            }
    }
    return cnt;
}
int disp_rip(int *val, int *sol,int cnt, int n,int k,int pos){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        sol[pos]=val[i];
        cnt=disp_rip(val,sol,cnt,n,k,pos+1);
    }
    return cnt;
}
int perm_sem(int *val,int *sol,int cnt,int n,int pos){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++) printf("%d ", sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        sol[pos]=i;
        perm_sem(val,sol,cnt,n,pos+1);
    }
    return cnt;
}
int compare (const void * a, const void * b)
{
  return ( *(int*)a - *(int*)b );
}
int perm_rip(int *val,int n){
    int j=0;//
    int k=0;
    int cnt=0;
    int flag=0;
    int *tmp_vett=malloc(n*sizeof(int));
    int *tmp_occ=calloc(n,sizeof(int));
    qsort(val,n,sizeof(int),compare);
    for(int i=0;i<n;i++){ //ciclo su vettore ordinato
        flag=0;
        for( k=0;k<n && flag==0;k++){//ciclo su vettore pulito
            if(val[i]==tmp_vett[k]){
                tmp_occ[k]++;
                flag=1;
            }
            
        }
        if (flag==0){
            tmp_vett[j]=val[i];
            tmp_occ[j]++;
            j++;
        }
    }
    int *sol=malloc(n*sizeof(int));
    cnt=perm_ripR(tmp_vett,sol,tmp_occ,0,j,n,cnt);
    printf("\n");
    return cnt;

}
int perm_ripR(int *val,int *sol, int *mark,int pos, int n_dist,int n,int cnt){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n_dist;i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=val[i];
            cnt=perm_ripR(val,sol,mark,pos+1,n_dist,n,cnt);
            mark[i]++;
        }
    }
    return cnt;
}

int comb_semp(int *val,int *sol,int n,int k,int pos, int start,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt=comb_semp(val,sol,n,k,pos+1,i+1,cnt);
    }
    return cnt;
}
int comb_rip(int *val,int *sol,int n,int k, int pos, int start,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt=comb_semp(val,sol,n,k,pos+1,i,cnt);
        start++;
    }
    return cnt;
}
int pwr_d(int *val,int *sol,int n, int start,int pos,int cnt){
    int i=0;
    if(start>=n){
        for(i=0;i<pos;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt=pwr_d(val,sol,n,i+1,pos+1,cnt);
    }
    cnt=pwr_d(val,sol,n,n,pos,cnt);
    return cnt;
}
int pwr_disp(int *val,int *sol,int n,int start,int pos, int cnt){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++)
            if(sol[i]) printf("%d ",val[i]);
        printf("\n");
        return cnt+1;
    }
    sol[pos]=1;
    cnt=pwr_disp(val,sol,n,i+1,pos+1,cnt);
    sol[pos]=0;
    cnt=pwr_disp(val,sol,n,i+1,pos+1,cnt);
    return cnt;
}
int pwr(int *val,int n){
    int cnt=0;
    int *sol=malloc(n*sizeof(int));
    for(int i=0;i<=n;i++){
        cnt+=pwr_R(val,sol,n,i,0,0,cnt);
    }
    return cnt;
}
int pwr_R(int *val,int *sol,int n,int k,int pos, int start, int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<pos;i++) printf("%d ",sol[i]);
        printf("\n");
        return 1;
    }
    for(i=start;i<n;i++){
        sol[pos]=val[i];
        cnt+=pwr_R(val,sol,n,k,pos+1,i+1,cnt);
    }
    return 0;
}
void part1(int *val,int *sol, int n,int k, int pos){
    //n---> numero di elementi vettore
    //k--> numero di partizioni
    //sol -->vettore in cui in ogni cella è contenuto la partizione in cui si trova l'i-esimo elemento
    int i,j;
    if(pos>=n){
        int *occ=calloc(n,sizeof(int));
        for(i=0;i<pos;i++){
            occ[sol[i]]++;
        }
        for(i=0;i<k;i++){
            if(occ[i]==0) return ;
        }
        for(i=0;i<n;i++) printf("%d----> %d ",val[i],sol[i]);
        printf("\n");
        return ;
    }
    for(i=0;i<k;i++){
        sol[pos]=i;
        part1(val,sol,n,k,pos+1);
    }
}