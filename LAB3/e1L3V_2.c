#include "stdio.h"
#include "stdlib.h"
#define n 7
int majority(int *a,int N);
int majorityR(int *a, int l, int r,int* cnt);
int find(int *a,int c,int l,int r);
int maxV(int *v,int len){ //cerco il valore massimo del vettore

    int max=0;
    for(int i=0;i<len;i++)
        if (v[i]>max) max=v[i];
    return max;

}
int main(){
    int vet[n]={9,3,3,4,3,3,7};
    int magg=majority(vet,n);
    if(magg!=-1)
    printf("elemento maggioritario è: %d",magg);
    else printf("non ho trovato nulla!");
}
int majority(int *a,int N){
    int l=0,r=N-1,max_occ,cnt=0;
    max_occ=majorityR(a,l,r,&cnt);
    return max_occ;

}
int majorityR(int *a, int l, int r,int* cnt){
    if(l==r){
        *cnt+=1;
        return a[l];
    }
    int m=(l+r)/2;
    int cnt1=0,cnt2=0;
    int c1=majorityR(a,l,m,&cnt1);
    int c2=majorityR(a,m+1,r,&cnt2);
    if(c1==c2) {
        *cnt=cnt1+cnt2;
        return c1;
    }
    if(find(a,c1,l,r)>(r-l+1)/2) return c1;
    if(find(a,c2,l,r)>(r-l+1)/2) return c2;
    return -1;


}

int find(int *a,int c,int l,int r){
    int cnt=0;
    for(int i=l;i<r;i++){

        if(a[i]==c) cnt++;
    }
    return cnt;


}
