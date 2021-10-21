#include "stdio.h"
#include "stdlib.h"
#define n 7
int majority(int *a,int N);
int maxV(int *v,int len){ //cerco il valore massimo del vettore

    int max=0;
    for(int i=0;i<len;i++)
        if (v[i]>max) max=v[i];
    return max;

}
int main(){
    int vet[n]={3,3,9,4,3,3,7};
    int magg=majority(vet,n);
    if(magg!=-1)
    printf("elemento maggioritario è: %d",magg);
    else printf("non ho trovato nulla!");
}
int majority(int *a,int N){
    int l=0,r=N-1,max_occ;
    int size_vett=maxV(a,N)+1; //considero anche lo 0
    int *b=(int*)calloc(size_vett,sizeof(int));//vettore occorrenze
    majorityR(a,b,l,r);
    max_occ=find_magg(b,size_vett);
    return max_occ;
    printf("eccomi qua!");

}
void majorityR(int *a,int *b, int l, int r){
    if(l==r){
        b[a[l]]=b[a[l]]+1;
        return;
    }
    int m=(l+r)/2;
    majorityR(a,b,l,m);
    majorityR(a,b,m+1,r);
    return;
}
int find_magg(int *v,int len){
    int max_index=0,max=0;
    for(int i=0;i<len;i++){
        if (v[i]>max){
            max=v[i];max_index=i;
        }
    }
    return max_index;
}