#include "stdio.h"
#include "stdlib.h"
#define file_name "brani.txt"
#define len_char 255 +1
#define n_max_film 5
typedef struct {
    int n_film;
    char **l_film;
}amico;

int riempi_lista_da_file(amico **lista);
void genera_playlist(amico *lista,int n_amici);
int combinazioni_playlist(amico* lista, int len,int pos,int *sol,int cnt);
int main(){
    int n_amici;
    amico *lista_amici;
    n_amici=riempi_lista_da_file(&lista_amici);
    genera_playlist(lista_amici,n_amici);
}
int riempi_lista_da_file(amico **lista){
    amico *tmp_lista;
    FILE *fp;
    int n_amici=0;
    fp=fopen(file_name,"r");
    if(fp!=NULL){
        fscanf(fp,"%d",&n_amici);
        tmp_lista=malloc(n_amici*sizeof(amico));
        for(int i=0;i<n_amici;i++){//ciclo in cui popolo struct rappresentante ogni amico
            amico t;
            fscanf(fp,"%d",&(t.n_film));
            //salvo tutti i film 
            t.l_film=(char **)malloc(t.n_film*sizeof(char*));
            for(int j=0;j<t.n_film;j++){
                t.l_film[j]=(char *)malloc(len_char*sizeof(char));
                fscanf(fp,"%s",t.l_film[j]);
            }
            tmp_lista[i]=t;
        }



    }
    *lista=tmp_lista;
    return n_amici;
}
void genera_playlist(amico *lista,int n_amici){
    int*sol=malloc(n_amici*sizeof(int));//vettore contenente una possibile playlist
    int cnt=0;
    cnt=combinazioni_playlist(lista,n_amici,0,sol,cnt);
    printf("Totale playlist generate: %d",cnt);
}
int combinazioni_playlist(amico* lista, int len,int pos,int *sol,int cnt){
    if(pos==len){
        printf("Playlist %d: \n",cnt+1);
        for(int i=0;i<len;i++){
            printf("%s\n",lista[i].l_film[sol[i]]);
        }
        printf("\n");
        return cnt+1;
    }
    for(int j=0;j<lista[pos].n_film;j++){
        sol[pos]=j;
        cnt=combinazioni_playlist(lista,len,pos+1,sol,cnt);
    }
    return cnt;
}