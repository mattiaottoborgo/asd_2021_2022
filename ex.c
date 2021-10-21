#include <stdio.h>
#include <stdlib.h>
int majority( int *a, int N); 
void majorityR(int *a, int l, int r, int *b);
int research(int *b, int n);
int main(void) {
  int n=7,a[7]={3,3,9,4,3,5,3};
  int ret = majority(a, n);
  printf("il valore più ricorrente è %d",ret-1);
  return 0;
}

int majority( int *a, int N) {
  int max=1;
  int *b;
  for(int i=0;i<N;i++){
    if(a[i]>max)
      max=a[i];
  }
  b=(int*)calloc(max+1,sizeof(int));

  majorityR(a, 0, N, b);

  int r=research(b,max+1);
  if(r>(N/2))
    return r;
  else
    return -1;
}

void majorityR(int *a, int l,int r,int *b){
  int m = (l + r)/2;
    if (l == r){
      b[a[l]]=b[a[l]]+1;
      printf("numero occ %d numero :%d -->",b[a[l]],l);
      for(int i=0;i<10;i++){
        printf("%d ",b[i]);
      }
      printf("\n");
      return ;
    }
    majorityR(a, l, m, b);
    majorityR(a, m+1, r, b);
    
    return;
}


int research(int *b,int n){
  int max=1,vet=0;
  for(int i=0;i<n;i++){
    if(b[i]>max)
      vet=i+1;
  }
  return vet;
}





















