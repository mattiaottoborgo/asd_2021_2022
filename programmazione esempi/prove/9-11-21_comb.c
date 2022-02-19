#include "stdlib.h"
#include "stdio.h"
#define K 3
#define N 4
int disp_rip(int *vett, int*sol,int pos,int n,int k,int cnt);
int disp_semp(int *vett, int*sol,int*mark,int pos,int n,int k,int cnt);
int perm_semp(int *vett, int*sol,int*mark,int pos,int n,int cnt);
int perm_rip(int *vett, int*sol,int*mark,int pos,int n,int cnt);
int comb_semp(int *vett,int *sol,int pos,int start,int cnt,int n,int k);
int comb_rip(int *vett,int *sol,int pos,int start,int cnt,int n,int k);
int powerset_1(int *vett,int *sol,int n,int cnt,int start,int pos);
int powerset_2(int *vett,int *sol,int n,int cnt,int pos);
int powerset_3(int *vett, int n);
int powerset_3r(int *vett,int *sol,int start,int pos,int n,int cnt,int j);
int main(){
    int vett[N]={0,1,2,3};
    int *sol=malloc(K*sizeof(int));
    int *mark=calloc(N,sizeof(int));
    int mark2[N]={1,2,1,3};
    int cnt;
    //cnt=disp_semp(vett,sol,mark,0,N,K,cnt);
    //cnt=disp_rip(vett,sol,0,N,5,cnt);
    //cnt=perm_semp(vett,sol,mark,0,N,cnt);
    //cnt=perm_rip(vett,sol,mark2,0,N,cnt);
    //cnt=comb_semp(vett,sol,0,0,cnt,N,K);
    //cnt=comb_rip(vett,sol,0,0,cnt,N,K);
    //cnt=powerset_1(vett,sol,N,cnt,0,0);
    //cnt=powerset_2(vett,sol,N,cnt,0);
    cnt=powerset_3(vett,N);
}
int disp_semp(int *vett, int*sol,int*mark,int pos,int n,int k,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=i;
            cnt=disp_semp(vett,sol,mark,pos+1,n,k,cnt);
            mark[i]--;
        }
    }
    return cnt;
}
int disp_rip(int *vett, int*sol,int pos,int n,int k,int cnt){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        sol[pos]=i;
        cnt=disp_rip(vett,sol,pos+1,n,k,cnt);
    }
    return cnt;
}
int perm_semp(int *vett, int*sol,int*mark,int pos,int n,int cnt){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        if(mark[i]==0){
            mark[i]=1;
            sol[pos]=i;
            cnt=perm_semp(vett,sol,mark,pos+1,n,cnt);
            mark[i]--;
        }
    }
    return cnt;
}
int perm_rip(int *vett, int*sol,int*mark,int pos,int n,int cnt){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++)printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=0;i<n;i++){
        if(mark[i]>0){
            mark[i]--;
            sol[pos]=i;
            cnt=perm_rip(vett,sol,mark,pos+1,n,cnt);
            mark[i]++;
        }
    }
    return cnt;
}
int comb_semp(int *vett,int *sol,int pos,int start,int cnt,int n,int k){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=i;
        cnt=comb_semp(vett,sol,pos+1,i+1,cnt,n,k);
    }
    return cnt;
}
int comb_rip(int *vett,int *sol,int pos,int start,int cnt,int n,int k){
    int i;
    if(pos>=k){
        for(i=0;i<k;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=i;
        comb_rip(vett,sol,pos+1,i,cnt,n,k);
        start++;
    }
    return cnt;
}
int powerset_1(int *vett,int *sol,int n,int cnt,int start,int pos){
    int i;
    if(start>=n){
        for(i=0;i<pos;i++) printf("%d ",sol[i]);
        printf("\n");
        return cnt+1;
    }
    for(i=start;i<n;i++){
        sol[pos]=vett[i];
        cnt=powerset_1(vett,sol,n,cnt,i+1,pos+1);
    }
    cnt=powerset_1(vett,sol,n,cnt,n,pos);
    return cnt;
}
int powerset_2(int *vett,int *sol,int n,int cnt,int pos){
    int i;
    if(pos>=n){
        for(i=0;i<n;i++){
            if(sol[i]!=0) printf("%d ",vett[i]);
        }
        printf("\n");
        return cnt+1;
    }
    sol[pos]=1;
    cnt=powerset_2(vett,sol,n,cnt,pos+1);
    sol[pos]=0;
    cnt=powerset_2(vett,sol,n,cnt,pos+1);
    return cnt;
}
int powerset_3(int *vett, int n){
    int cnt=0;
    int *sol=malloc(n*sizeof(int));
    for(int i=0;i<=n;i++) cnt+=powerset_3r(vett,sol,0,0,n,cnt,i);
    return cnt;
}
int powerset_3r(int *vett,int *sol,int start,int pos,int n,int cnt,int j){
    int i;
    if(pos>=j){
        for(i=0;i<j;i++) printf("%d ",sol[i]);
        printf("\n");
        return 1;
    }
    for(i=start;i<n;i++) {
        sol[pos]=vett[i];
        cnt+=powerset_3r(vett,sol,i+1,pos+1,n,cnt,j);
    }
    return 0;
}