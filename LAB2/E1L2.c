#include "stdio.h"
int gcd(int a, int b);
int main(){
    int a,b,gcd_n;
    printf("inserisci due numeri interi positivi: ");
    scanf("%d %d",&a,&b);
    gcd_n=gcd(a,b);
    printf("gcd è %d",gcd_n);
}
int gcd(int a, int b){
    if (a<b){
        int temp=a;
        a=b;
        b=temp;
    }
    if(a==b) return a;

    if(b==1) return b;

    if (a%2==0 && b%2==0){
        return 2*gcd(a/2,b/2);
    }
    else if (a%2!=0 && b%2==0) return gcd(a,b/2);
    else if (a%2==0 && b%2!=0) return gcd(a/2,b);
    else if (a%2!=0 && b%2!=0) return gcd((a-b)/2,b);
}