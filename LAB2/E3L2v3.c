#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define nome_file "corse.txt"
#define MAX_CHAR 30
#define MAX_CHAR_COMANDO 20 //20+carattere terminatore
#define MAX_RIGHE 1000
#define N_COMANDI 7
#define LENGTH_COD 7
char lista_comandi[N_COMANDI][MAX_CHAR_COMANDO]={"ord_data","ord_cod","ord_staz_p","ord_staz_arr","leggi_f"};
typedef struct {
    char *cod,*partenza,*destinazione,*data,*orap,*orad;
    int ritardo;
}corsa;

enum {ord_data,ord_cod,ord_staz_p,ord_staz_arr,leggi_f};
int cnfr_data(corsa *t1,corsa *t2);
int cnfr_staz_p(corsa *t1,corsa *t2);
int cnfr_staz_arr(corsa *t1,corsa *t2);
int cnfr_cod(corsa *t1,corsa *t2);
void scambia_p(corsa **p1,corsa **p2);
void Bs_data(corsa **lista_tratte,int n_tratte);
void Bs_cod(corsa **lista_tratte,int n_tratte);
void Bs_staz_arr(corsa **lista_tratte,int n_tratte);
void Bs_staz_p(corsa **lista_tratte,int n_tratte);
void print_struct(corsa **arr_corse,int len);
void test_ord(corsa arr_tratte[],int n_tratte);
int read_comando(char *comando);
void print_comandi();
void dealloc(corsa *arr,int n_linee);
corsa* leggi_file(int *n_linee,corsa *arr_corse);


int main(){
    FILE *f;
    corsa *arr_corse;
    int i=0,n_linee=0;
    arr_corse=leggi_file(&n_linee,arr_corse);
    test_ord(arr_corse,n_linee);

    
      
}
corsa * leggi_file(int *n_linee,corsa *arr_corse){
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
    arr_corse=malloc((*n_linee)*sizeof(corsa));
    printf("n linee %d\n",*n_linee);
    char tmp_cod[LENGTH_COD];
    char tmp_par[MAX_CHAR];
    char tmp_des[MAX_CHAR];
    char tmp_data[MAX_CHAR];
    char tmp_orap[MAX_CHAR];
    char tmp_oraa[MAX_CHAR];
    //lettura dei dati
    while (fscanf(f,"%s %s %s %s %s %s %d",tmp_cod,tmp_par,tmp_des,tmp_data,tmp_orap,tmp_oraa,&(arr_corse[i].ritardo))==7&& i<*n_linee)
    {
        arr_corse[i].cod=malloc(strlen(tmp_cod)*sizeof(char));
        strncpy(arr_corse[i].cod,tmp_cod,strlen(tmp_cod));

        arr_corse[i].partenza=malloc(strlen(tmp_par)*sizeof(char));
        strncpy(arr_corse[i].partenza,tmp_par,strlen(tmp_par));

        arr_corse[i].destinazione=malloc(strlen(tmp_des)*sizeof(char));
        strncpy(arr_corse[i].destinazione,tmp_des,strlen(tmp_des));

        arr_corse[i].data=malloc(strlen(tmp_data)*sizeof(char));
        strncpy(arr_corse[i].data,tmp_data,strlen(tmp_data));

        arr_corse[i].orap=malloc(strlen(tmp_orap)*sizeof(char));
        strncpy(arr_corse[i].orap,tmp_orap,strlen(tmp_orap));

        arr_corse[i].orad=malloc(strlen(tmp_oraa)*sizeof(char));
        strncpy(arr_corse[i].orad,tmp_oraa,strlen(tmp_oraa));

        printf(" corsa [%d]  %s %s %s %s %s %s %d\n",i+1,arr_corse[i].cod,arr_corse[i].partenza,arr_corse[i].destinazione,arr_corse[i].data,arr_corse[i].orap,arr_corse[i].orad,arr_corse[i].ritardo);
        i++;
    }
    fclose(f);
    return arr_corse;

}
corsa **test_vett_din(corsa *arr_tratte,int n_tratte){
    corsa **vett= (corsa **)malloc(n_tratte*sizeof(corsa*));
    for(int i=0;i<n_tratte;i++){
        vett[i]=arr_tratte+i;
    }
    return vett;
}
void test_ord(corsa *arr_tratte,int n_tratte){
    FILE *fpout;
    char comando[MAX_CHAR_COMANDO]="";
    int indice_comando=0;
    corsa **arr_tratte_p_data;
    corsa **arr_tratte_p_cod;
    
    corsa **arr_tratte_p_staz_p;
    corsa **arr_tratte_p_staz_a;



    arr_tratte_p_data=test_vett_din(arr_tratte,n_tratte); //se fai assegnazioni multiple del tipo ..=..=test_vett_din
    //in pratica è come se copiassi la stessa porzione di memoria, quindi non sarebbero indipendenti tra loro.
    arr_tratte_p_cod=test_vett_din(arr_tratte,n_tratte);
    arr_tratte_p_staz_p=test_vett_din(arr_tratte,n_tratte);
    arr_tratte_p_staz_a=test_vett_din(arr_tratte,n_tratte);

    printf("\nPrima\n"); //stampa ordine in cui si trovano effettivamente gli elementi nel vettore di struct originale
    for(int i=0;i<n_tratte;i++){
   //     printf(" corsa [%d]  %s %s %s %s %s %s\n",i+1,arr_tratte[i].cod,arr_tratte[i].partenza,arr_tratte[i].destinazione,arr_tratte[i].data,arr_tratte[i].orap,arr_tratte[i].orad);
    }    
    Bs_data(arr_tratte_p_data,n_tratte);
    Bs_cod(arr_tratte_p_cod,n_tratte);
    Bs_staz_arr(arr_tratte_p_staz_a,n_tratte);
    Bs_staz_p(arr_tratte_p_staz_p,n_tratte);
    while (1){
        print_comandi();
        indice_comando=read_comando(comando);

        switch (indice_comando)
        {
        case ord_data:
            print_struct(arr_tratte_p_data,n_tratte);
            break;
        case ord_cod:
            print_struct(arr_tratte_p_cod,n_tratte);
            break;
        case ord_staz_arr:
            print_struct(arr_tratte_p_staz_a,n_tratte);
            break;
        case ord_staz_p:
            print_struct(arr_tratte_p_staz_p,n_tratte);
            break;
        case leggi_f:
            dealloc(arr_tratte,n_tratte);
            leggi_file(&n_tratte,arr_tratte);
            //deallocazione struttura usata precedentemente
            free(arr_tratte_p_data);
            free(arr_tratte_p_cod);
            free(arr_tratte_p_staz_a);
            free(arr_tratte_p_staz_p);
            arr_tratte_p_data=test_vett_din(arr_tratte,n_tratte);
            arr_tratte_p_cod=test_vett_din(arr_tratte,n_tratte);
            arr_tratte_p_staz_p=test_vett_din(arr_tratte,n_tratte);
            arr_tratte_p_staz_a=test_vett_din(arr_tratte,n_tratte);
            break;
        }
    }

}
void print_struct(corsa **arr_corse,int len){
    for(int i=0;i<len;i++)
        printf(" corsa [%d]  %s %s %s %s %s %s\n",i+1,arr_corse[i]->cod,arr_corse[i]->partenza,arr_corse[i]->destinazione,arr_corse[i]->data,arr_corse[i]->orap,arr_corse[i]->orad);
}
void scambia_p(corsa **p1,corsa **p2){
    corsa *temp= *p1; //mi copio dentro una variabile puntatore di tipo struct 'corsa' il valore del puntatore al dato passato(ossia un puntatore.)
    *p1=*p2;
    *p2=temp;

}
void Bs_data(corsa **lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_data(lista_tratte[j],lista_tratte[j+1])>0){
                scambia_p(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
void Bs_cod(corsa **lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_cod(lista_tratte[j],lista_tratte[j+1])>0){
                scambia_p(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
void Bs_staz_p(corsa **lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_staz_p(lista_tratte[j],lista_tratte[j+1])>0){
                scambia_p(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
void Bs_staz_arr(corsa **lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_staz_arr(lista_tratte[j],lista_tratte[j+1])>0){
                scambia_p(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
int cnfr_data(corsa *t1,corsa *t2){
    if(strcmp(t1->data,t2->data)==0) return strcmp(t1->orap,t2->orap);
    return strcmp(t1->data,t2->data);
}
int cnfr_staz_p(corsa *t1,corsa *t2){
    return strcmp(t1->partenza,t2->partenza);
}
int cnfr_staz_arr(corsa *t1,corsa *t2){
    return strcmp(t1->destinazione,t2->destinazione);
}
int cnfr_cod(corsa *t1,corsa *t2){
    return strcmp(t1->cod,t2->cod);
}

int read_comando(char *comando){
    int index;
    printf("Inserisci comando: ");
    scanf("%s",comando);
    for (int i=0;i<N_COMANDI;i++){
        //printf("%s\n",lista_c[i]);
        if(strcmp(comando,lista_comandi[i])==0){
            index=i;
            printf("comando trovato: %d\n",index);
            return index;
        }
    }
}
void print_comandi(){
    printf("comandi disponibili:\n");
    printf("ord_data -> ordina tratte per data\n");
    printf("ord_cod -> ordina tratte per codice\n");
    printf("ord_staz_p -> ordina tratte per stazione di partenza\n");
    printf("ord_staz_arr -> ordina tratte per stazione di arrivo\n");
    printf("ricerca -> ricerca di una tratta per stazione di partenza\n");
    printf("leggi_f -> leggi dati da nuovo file\n");
}

void dealloc(corsa *arr,int n_linee){
    for(int i=0;i<n_linee;i++){
        free(arr[i].cod);
        free(arr[i].partenza);
        free(arr[i].destinazione);
        free(arr[i].data);
        free(arr[i].orap);
        free(arr[i].orad);

    }
    free(arr);
}