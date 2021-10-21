#include "stdio.h"
#include "stdlib.h"
#define nome_file "corse.txt"
#define MAX_CHAR 30
#define MAX_CHAR_COMANDO 20 //20+carattere terminatore
#define MAX_RIGHE 1000
#define N_COMANDI 7

typedef struct 
{
    char cod[7],partenza[MAX_CHAR],destinazione[MAX_CHAR],data[MAX_CHAR],orap[MAX_CHAR],orad[MAX_CHAR];
    int ritardo;
}corsa;
corsa *test_vett_din(corsa *arr_tratte,int n_tratte);
int main(){
    corsa arr_corse[MAX_RIGHE];
    corsa *arr_corse_p_data;
    corsa *arr_corse_p_cod;
    corsa *arr_corse_p_staz_p;
    corsa *arr_corse_p_staz_arr;
    int n_linee=0;
    leggi_file(arr_corse,&n_linee);
    arr_corse_p_data=arr_corse_p_cod,arr_corse_p_staz_p=arr_corse_p_staz_arr=test_vett_din(arr_corse,n_linee);
    printf("\n");
}
corsa *test_vett_din(corsa *arr_tratte,int n_tratte){
    corsa *vett= (corsa *)malloc(n_tratte*sizeof(corsa));
    for(int i=0;i<n_tratte;i++){
        vett[i]=arr_tratte[i];
    }
    return vett;
}

void leggi_file(int *n_linee,corsa *arr_corse){
    FILE *f;
    int i=0;
    char nomefile[MAX_CHAR_COMANDO];
    printf("Inserisci nome file: ");
    scanf("%s",nomefile);
    f=fopen(nomefile,"r");
    while ((f=fopen(nomefile,"r"))==NULL)
    {
        printf("Inserisci nome file esistente:");
        scanf("%s",nomefile);
    }
    
    fscanf(f,"%d\n",n_linee);
    printf("n linee %d\n",n_linee);

    // lettura dei dati
    while (fscanf(f,"%s %s %s %s %s %s %s",&arr_corse[i].cod,&arr_corse[i].partenza,&arr_corse[i].destinazione,&arr_corse[i].data,&arr_corse[i].orap,&arr_corse[i].orad,&arr_corse[i].ritardo)==7&& i<n_linee)
    {
        printf(" corsa [%d]  %s %s %s %s %s %s\n",i+1,arr_corse[i].cod,arr_corse[i].partenza,arr_corse[i].destinazione,arr_corse[i].data,arr_corse[i].orap,arr_corse[i].orad,arr_corse[i].ritardo);
        i++;
    }
    fclose(f);

}