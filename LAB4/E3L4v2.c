 #include "stdio.h"
 #include "stdlib.h"
 #define diff_pietre 4
 #define file "easy_test_set.txt"
enum{zaffiro=0,rubino=1,topazio=2,smeraldo=3};
char pietre[diff_pietre]={'z','r','t','s'};
 int generaCollane(int z,int r, int t, int s);
 int disp_rip(int *sol, int k, int n,int pos,int z,int s,int r,int t,int *mark);

 int main(){
     int z=10,r=7,t=8,s=1,l;
    int length_file;
    FILE *fp;
    fp=fopen(file,"r");
    fscanf(fp,"%d",&length_file);
    for(int i=0;i<length_file;i++){
        printf("TEST #%d\n",i+1);
        fscanf(fp,"%d %d %d %d",&z,&r,&t,&s);
        l=generaCollane(z,r,t,s);
        printf("la collana di valore massimo è %d\n",l);
    }

 }
 int generaCollane(int z,int r, int t, int s){
     int *sol=calloc((z+t+r+s),sizeof(int));
     int *mark=calloc(diff_pietre,sizeof(int));
     int flag=0;
     int length=z+t+r+s;
     while(flag==0){
         flag=disp_rip(sol,length,z+r+t+s,0,z,s,r,t,mark);
         length--;
     }
     return length+1;
 }
 int disp_rip(int *sol, int k, int n,int pos,int z,int s,int r,int t,int *mark){
    int i;
    int end=0;
    int prec;
     if(pos>=k){
         for(i=0;i<k;i++){
             printf("%c ",pietre[sol[i]]);
         }
         printf("\n");
        return 1;
     }
     for(i=0;i<n && end==0;i++){
         if(pos!=0) {
            prec=sol[pos-1];
            if(prec==zaffiro && ( ( i==zaffiro &&mark[i]<z ) || (i==rubino && mark[i]<r)) ) {
                sol[pos]=i;
                mark[i]++;
                end=disp_rip(sol,k,n,pos+1,z,s,r,t,mark);
                mark[i]--;
            }
            else if(prec==smeraldo && ((i==smeraldo && mark[i]<s) || (i==topazio && mark[i]<t))) {
                sol[pos]=i;
                mark[i]++;
                end=disp_rip(sol,k,n,pos+1,z,s,r,t,mark);
                mark[i]--;
            }
            else if(prec==rubino && ((i==smeraldo && mark[i]<s) || (i==topazio && mark[i]<t))) {
                sol[pos]=i;
                mark[i]++;
                end=disp_rip(sol,k,n,pos+1,z,s,r,t,mark);
                mark[i]--;
            }
            else if(prec==topazio && ((i==zaffiro && mark[i]<z) || (i==rubino && mark[i]<r))) {
                sol[pos]=i;
                mark[i]++;
                end=disp_rip(sol,k,n,pos+1,z,s,r,t,mark);
                mark[i]--;
            }
         }
         else {
             prec=sol[pos]=i;
             mark[i]++;
             end=disp_rip(sol,k,n,pos+1,z,s,r,t,mark);
             mark[i]--;
         }
     }
     return end;

 }
