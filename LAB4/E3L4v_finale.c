 #include "stdio.h"
 #include "stdlib.h"
 #define diff_pietre 4
#define file "easy_test_set.txt"
//versione definitiva
enum{zaffiro=0,rubino=1,topazio=2,smeraldo=3};
char pietre[diff_pietre]={'z','r','t','s'};
int val_pietre[diff_pietre];
int max_rip;
 int generaCollane(int*mark);
 int n_rip(int *vet,int pos,int val);
 void piazzaPietre(int *sol, int k, int n,int pos,int *mark, int **sol_max,int *length_max,int *max_mark,int i);
void disp_rip(int *sol, int k, int n,int pos,int *mark, int **sol_max,int *length_max,int *max_mark);

 int main(){
     int z=6,r=5,t=7,s=2,l;
    int length_file;
    int *mark=calloc(diff_pietre,sizeof(int));
    FILE *fp;
    fp=fopen(file,"r");
    fscanf(fp,"%d",&length_file);
    for(int i=0;i<length_file;i++){
        printf("TEST #%d\n",i+1);
        fscanf(fp,"%d %d %d %d",&mark[0],&mark[1],&mark[2],&mark[3]);
        l=generaCollane(mark);
    }

 }
 int generaCollane(int*max_mark){
     int length=0;
     for(int j=0;j<diff_pietre;j++)length+=max_mark[j];
     int *sol=calloc(length,sizeof(int));
     int *mark=calloc(diff_pietre,sizeof(int));
     int *sol_max;
     int length_curr=0;
     int length_max=0;
     int rip=1;
     int *best_solution=malloc(length*sizeof(int));
        for(int i=length;i>0;i--){
            disp_rip(sol,i,length,0,mark,&sol_max,&length_curr,max_mark); 
            if(length_max==length_curr&& length_max>0)break;
            if(length_curr>length_max ){
                best_solution=sol_max;
                length_max=length_curr;
            } 
                
            
        }
        printf("soluzione massima: %d:\n",length_max);
            for(int i=0;i<length_max;i++){
                printf("%c ",pietre[best_solution[i]]);
            }
            printf("\n");  
     return length_max;
 }
 void disp_rip(int *sol, int k, int n,int pos,int *mark, int **sol_max,int *length_max,int *max_mark){
    int i;
    int end=0;
    int prec;
     if(pos>=k){
            if(k>*length_max ) {
                int *tmp=malloc(k*sizeof(int));
                for(i=0;i<k;i++){
                    tmp[i]=sol[i];
                }
                *sol_max=tmp;
                *length_max=k;
            }

         return ;
     }
     for(i=0;i<diff_pietre ;i++){
         if(pos!=0) {
            int flag=0;
            prec=sol[pos-1];
            if(prec==zaffiro && ( ( i==zaffiro &&mark[i]<max_mark[i]  ) || (i==rubino && mark[i]<max_mark[i]))  ) {
                flag=1;
                
                
            }
            else if(prec==smeraldo && ((i==smeraldo && mark[i]<max_mark[i]) || (i==topazio && mark[i]<max_mark[i]))  ) {
                flag=1;
                
                
            }
            else if(prec==rubino && ((i==smeraldo && mark[i]<max_mark[i]) || (i==topazio && mark[i]<max_mark[i])) ) {
                flag=1;
                
            }
            else if(prec==topazio && ((i==zaffiro && mark[i]<max_mark[i]) || (i==rubino && mark[i]<max_mark[i]))) {
                flag=1;
         }
         if (flag){

            piazzaPietre(sol,k,n,pos,mark,sol_max,length_max,max_mark,i);
         }
         }
         else {
             piazzaPietre(sol,k,n,pos,mark,sol_max,length_max,max_mark,i);
             
         }
     }
     return ;

 }

void piazzaPietre(int *sol, int k, int n,int pos,int *mark, int **sol_max,int *length_max,int *max_mark,int i){
    sol[pos]=i;
    mark[i]++;
    disp_rip(sol,k,n,pos+1,mark,sol_max,length_max,max_mark);
    mark[i]--;
    return ;
}