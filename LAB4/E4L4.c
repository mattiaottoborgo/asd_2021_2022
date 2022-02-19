 #include "stdio.h"
 #include "stdlib.h"
 #define diff_pietre 4
// #define max_rip 5
#define file "test_set.txt"
enum{zaffiro=0,rubino=1,topazio=2,smeraldo=3};
char pietre[diff_pietre]={'z','r','t','s'};
int val_pietre[diff_pietre];
int max_rip;
 int generaCollane(int z,int r, int t, int s);
 int n_rip(int *vet,int pos,int val);
int disp_rip(int *sol, int k, int n,int pos,int z,int s,int r,int t,int *mark,int max_coll, int **sol_max,int *length_max);

 int main(){
     int z=6,r=5,t=7,s=2,l;
    int length_file;
    int *mark=calloc(diff_pietre,sizeof(int));
    FILE *fp;
    fp=fopen(file,"r");
    fscanf(fp,"%d",&length_file);
    for(int i=0;i<length_file;i++){
        printf("TEST #%d\n",i+1);
        fscanf(fp,"%d %d %d %d %d %d %d %d %d",&z,&r,&t,&s,&val_pietre[0],&val_pietre[1],&val_pietre[2],&val_pietre[3],&max_rip);
        l=generaCollane(z,r,t,s);
        printf("la collana di valore massimo è %d\n",l);
    }

 }
 int generaCollane(int z,int r, int t, int s){
     int *sol=calloc((z+t+r+s),sizeof(int));
     int *mark=calloc(diff_pietre,sizeof(int));
     int *sol_max;
     int length=z+t+r+s;
     int length_curr=0;
     int length_max=0;
     int rip=1;
     int max_val=0;
     int max_curr=0;
     int *best_solution=malloc((z+t+r+s)*sizeof(int));
        for(int i=length;i>0;i--){
            max_curr=disp_rip(sol,i,z+r+t+s,0,z,s,r,t,mark,max_val,&sol_max,&length_curr); 
            if(length_max==length_curr&& length_max>0)break;
            if (max_curr>max_val) {
                max_val=max_curr;
                best_solution=sol_max;
                length_max=length_curr;
                }
            
        }
        printf("soluzione massima: %d, valore: %d\n",length_max,max_val);
            for(int i=0;i<length_max;i++){
                printf("%c ",pietre[best_solution[i]]);
            }
            printf("\n");  
     return max_val;
 }
 int disp_rip(int *sol, int k, int n,int pos,int z,int s,int r,int t,int *mark,int max_coll, int **sol_max,int *length_max){
    int i;
    int end=0;
    int prec;
     if(pos>=k){
         if(mark[zaffiro]<=mark[smeraldo]){
            int max_curr=0;
            for(i=0;i<diff_pietre;i++){
               max_curr+=mark[i]*val_pietre[i];
            }
            if(max_curr>max_coll ) {
                int *tmp=malloc(k*sizeof(int));
                max_coll=max_curr;
                for(i=0;i<k;i++){
                    tmp[i]=sol[i];
                }
                *sol_max=tmp;
                *length_max=k;
            }
         }
         return max_coll;
     }
     for(i=0;i<diff_pietre ;i++){
         if(pos!=0) {
            int flag=0;
            prec=sol[pos-1];
            if(prec==zaffiro && ( ( i==zaffiro &&mark[i]<z  ) || (i==rubino && mark[i]<r))  ) {
                flag=1;
                
                
            }
            else if(prec==smeraldo && ((i==smeraldo && mark[i]<s) || (i==topazio && mark[i]<t))  ) {
                flag=1;
                
                
            }
            else if(prec==rubino && ((i==smeraldo && mark[i]<s) || (i==topazio && mark[i]<t)) ) {
                flag=1;
                
            }
            else if(prec==topazio && ((i==zaffiro && mark[i]<z) || (i==rubino && mark[i]<r))) {
                flag=1;
         }
         if (flag){
             if(n_rip(sol,pos,i)<=max_rip){
                sol[pos]=i;
                mark[i]++;
                max_coll=disp_rip(sol,k,n,pos+1,z,s,r,t,mark,max_coll,sol_max,length_max);
                mark[i]--;
                }
         }
         }
         else {
             prec=sol[pos]=i;
             mark[i]++;
             max_coll=disp_rip(sol,k,n,pos+1,z,s,r,t,mark,max_coll,sol_max,length_max);
             mark[i]--;
         }
     }
     return max_coll;

 }
 int n_rip(int *vet,int pos,int val){//funzione che calcola quante volte è stato inserito un elemento di fila compreso il corrente
     int cnt=1;
     while(pos>0 &&val==vet[pos-1]){
         cnt++;
         pos--;
     }
     return cnt;
 }
