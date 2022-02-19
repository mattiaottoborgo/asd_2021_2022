#include "stdlib.h"
#include "stdio.h"
#define file "grafo.txt"


int main(){
    FILE *fp;
    fp=fopen("grafo.txt","r");
    int N,E;

    fscanf(fp,"%d %d",&N,&E);
    int *u=malloc(E*sizeof(int));
    int *v=malloc(E*sizeof(int));
    //int *v=calloc(N,sizeof(int));
    for(int i=0;i<E;i++){
        fscanf(fp,"%d %d",&u[i],&v[i]);
    }
    printf("\n");
    vertex_cover(N,u,v,E);


}
void vertex_cover(int N,int *u, int *v, int E){
    int *vett=calloc(N,sizeof(int));
    int *sol=malloc(N*sizeof(int));
    int cnt=0;
    cnt= powerset_divide_impera(0,sol,N,0,cnt,u,v,E);
}


int powerset_divide_impera(int pos, int *sol,int k ,int start, int cnt,int*u,int *v,int E){
    //k-->numero elementi
    //start-->posizione a cui si è arrivato ad analizzare val
    //pos  -->indice corrente del vettore sol
    int i;
    if(start>=k){ // terminazione: ho finito gli elementi
        if(check(u,v,sol,pos,E)==1){
            printf("{");
            for(i=0; i<pos;i++) printf("%d ",sol[i]); //stampa soluzione
            printf("}");
            printf("\n");
            return cnt+1;
        }
        return cnt;
    }
    for(i=start;i<k;i++){
        sol[pos]=i;
        cnt=powerset_divide_impera(pos+1,sol,k,i+1,cnt,u,v,E);
    }
    cnt=powerset_divide_impera(pos,sol,k,k,cnt,u,v,E); // non aggiungere nulla e ricorri
    return cnt;
}

int check(int *u, int*v, int *sol,int len_sol, int E){
    int ok=1;
    for(int i=0;i<E&&ok;i++){// ciclo coppie di vertici
        ok=0;
        for(int j=0;j<len_sol&& !ok;j++){ //ciclo valori
            if(sol[j]==u[i] || sol[j]==v[i]) ok=1;
        }

    }
    
    return ok;

}

//0123