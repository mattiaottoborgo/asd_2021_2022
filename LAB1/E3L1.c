#include "stdio.h"
#include "string.h"
#define nome_file "corse.txt"
#define MAX_CHAR 30
#define MAX_CHAR_COMANDO 20 //20+carattere terminatore
#define MAX_RIGHE 1000
#define N_COMANDI 7

typedef struct {
    char cod[7],partenza[MAX_CHAR],destinazione[MAX_CHAR],data[MAX_CHAR],orap[MAX_CHAR],orad[MAX_CHAR];
    int ritardo;
}corsa;

char lista_comandi[N_COMANDI][MAX_CHAR_COMANDO]={"stampa_video","stampa_file","ord_data",
                                    "ord_cod","ord_staz_p","ord_staz_arr","ricerca"};
int estremo_sx(char (*arr)[MAX_CHAR_COMANDO], int l,int r, char *key);
int estremo_dx(char (*arr)[MAX_CHAR_COMANDO], int l,int r, char *key);
int cnfr_data(corsa t1,corsa t2);
int cnfr_staz_p(corsa t1,corsa t2);
int cnfr_staz_arr(corsa t1,corsa t2);
int cnfr_cod(corsa t1,corsa t2);
void cerca(corsa *arr_tratte,int n_tratte);
void Bs_data(corsa *lista_tratte,int n_tratte);
void Bs_cod(corsa *lista_tratte,int n_tratte);
void Bs_staz_arr(corsa *lista_tratte,int n_tratte);
void Bs_staz_p(corsa *lista_tratte,int n_tratte);
void leggi_file(FILE *f, int *n_linee, corsa *arr_corse);
void ordina(corsa *lista_tratte,int n_tratte,int tipo_ord);
void menu(char (*lista_c)[MAX_CHAR_COMANDO],corsa arr_tratte[],int n_tratte);
void print_comandi();
void stampa(corsa *arr_tratte, int n_tratte);
void scambia(corsa *p1,corsa *p2);
void ric_lin(corsa *lista_tratte, int n_tratte, char *str_to_find);
void ric_dico(corsa *lista_tratte, int n_tratte, char *str_to_find);
int read_comando(char *comando,char (*lista_comandi)[MAX_CHAR_COMANDO]);
char lista_mod_ricerca[N_COMANDI][MAX_CHAR_COMANDO]={"dicotomica","lineare"};


typedef enum {stampa_video,stampa_file,ord_data,ord_cod,ord_staz_p,ord_staz_arr,ricerca};
typedef enum  {dicotomica,lineare};

int main(){
    FILE *f;
    corsa arr_corse[MAX_RIGHE];
    int n_linee=0;
    //fine lettura
    leggi_file(f,&n_linee,arr_corse);
    print_comandi();
    while (1)
    {
       menu(lista_comandi,arr_corse,n_linee);
    }
      
}
void menu(char (*lista_c)[MAX_CHAR_COMANDO],corsa arr_tratte[],int n_tratte){
    FILE *fpout;
    char comando[MAX_CHAR_COMANDO]="";
    int indice_comando=0,indice_mod_ric;
    printf("Inserisci comando: ");
    indice_comando=read_comando(comando,lista_comandi);
    switch (indice_comando)
    {
    case ord_data:
        Bs_data(arr_tratte,n_tratte);
        stampa(arr_tratte,n_tratte);
        break;
    case ord_cod:
        Bs_cod(arr_tratte,n_tratte);
        stampa(arr_tratte,n_tratte);
        break;
    case ord_staz_arr:
        Bs_staz_arr(arr_tratte,n_tratte);
        stampa(arr_tratte,n_tratte);
        break;
    case ord_staz_p:
        Bs_staz_p(arr_tratte,n_tratte);
        stampa(arr_tratte,n_tratte);
        break;
    case ricerca:
        Bs_staz_p(arr_tratte,n_tratte);
        cerca(arr_tratte,n_tratte);
        break;

        
    default:
        break;
    }
}
void print_comandi(){
    printf("comandi disponibili:\n");
    printf("ord_data -> ordina tratte per data\n");
    printf("ord_cod -> ordina tratte per codice\n");
    printf("ord_staz_p -> ordina tratte per stazione di partenza\n");
    printf("ord_staz_arr -> ordina tratte per stazione di arrivo\n");
    printf("ricerca -> ricerca di una tratta per stazione di partenza\n");
}
int cnfr_data(corsa t1,corsa t2){
    return strcmp(t1.data,t2.data);
}
int cnfr_staz_p(corsa t1,corsa t2){
    return strcmp(t1.partenza,t2.partenza);
}
int cnfr_staz_arr(corsa t1,corsa t2){
    return strcmp(t1.destinazione,t2.destinazione);
}
int cnfr_cod(corsa t1,corsa t2){
    return strcmp(t1.cod,t2.cod);
}

void Bs_data(corsa *lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_data(lista_tratte[j],lista_tratte[j+1])>0){
                scambia(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
void Bs_cod(corsa *lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_cod(lista_tratte[j],lista_tratte[j+1])>0){
                scambia(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
void Bs_staz_p(corsa *lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_staz_p(lista_tratte[j],lista_tratte[j+1])>0){
                scambia(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}
void Bs_staz_arr(corsa *lista_tratte,int N)
{
    int i, j, l = 0, r = N - 1;
    for (i = l; i < r; i++){
        for (j = l; j < r - i + l; j++)
            if (cnfr_staz_arr(lista_tratte[j],lista_tratte[j+1])>0){
                scambia(&lista_tratte[j],&lista_tratte[j+1]);
            }
    }
    return;
}

void ric_lin(corsa *lista_tratte,int n_tratte, char *str_to_find){
    char p[MAX_RIGHE][MAX_CHAR_COMANDO];
    for(int i=0;i<n_tratte;i++){
        strcpy(p[i],(lista_tratte+i)->partenza);
    }
    for(int j=0;j<n_tratte && strcmp((lista_tratte+j)->partenza ,str_to_find)<=0 ;j++){ //ciclo fino alla fine del vettore o la prima lettera
                                                                                         //della parola corrente supera la prima di quella data
        if(strcmp((lista_tratte+j)->partenza ,str_to_find)==0|| strstr((lista_tratte+j)->partenza ,str_to_find)==((lista_tratte+j)->partenza)){
            printf("corsa [%d]  %s %s %s %s %s %s\n",j,lista_tratte[j].cod,lista_tratte[j].partenza,lista_tratte[j].destinazione,lista_tratte[j].data,lista_tratte[j].orap,lista_tratte[j].orad);

        }
    }
}
void ric_dico(corsa *lista_tratte,int n_tratte, char *str_to_find){
    //strategia: poichè posso avere più ricorrenze, la ricerca binaria classica non basta:
    //la utilizzo tuttavia per cercare il limite sx e dx del sottovettore contenente tutte le ricorrenze
    
    char p[MAX_RIGHE][MAX_CHAR_COMANDO];
    for(int i=0;i<n_tratte;i++){
        strcpy(p[i],(lista_tratte+i)->partenza);
    }
    int l_i=estremo_sx(p,0,n_tratte-1,str_to_find),r_i=estremo_dx(p,0,n_tratte-1,str_to_find);
    if(r_i-l_i!=0)
    for(int j=l_i;j<r_i;j++){
        printf("corsa [%d]  %s %s %s %s %s %s\n",j,lista_tratte[j].cod,lista_tratte[j].partenza,lista_tratte[j].destinazione,lista_tratte[j].data,lista_tratte[j].orap,lista_tratte[j].orad);

    }
    else printf("nessun elemento trovato!");
    
}

int estremo_sx(char (*arr)[MAX_CHAR_COMANDO], int l,
                int r, char *key)
{
    if (l > r) //terminazione
        return l;
    
    int m = l + (r - l) / 2;
    //se elemento centrale è maggiore o uguale a quello cercato, continua a sinistra
    if (strcmp(arr[m] ,key)>=0|| strstr(arr[m],key)==arr[m]) {
        return estremo_sx(arr, l,
                           m - 1, key);
    }
    //altrimenti continua a destra
    return estremo_sx(arr, m + 1,
                       r, key);
}

int estremo_dx(char (*arr)[MAX_CHAR_COMANDO], int l,
                int r, char *key)
{
    if (l > r)
        return l;
    // Find the middle index
    int m = l + (r - l) / 2;
    // If arr[mid] is less than// or equal to X search in// right subarray
    if (strcmp(arr[m] ,key)<=0 || strstr(arr[m],key)==arr[m]) {
        return estremo_dx(arr, m + 1,
                           r, key);
    }
 
    // If arr[mid] is greater than X// then search in left subarray
    return estremo_dx(arr, l,
                       m - 1, key);
}

int read_comando(char *comando,char (*lista_comandi)[MAX_CHAR_COMANDO]){
    int index;
    scanf("%s",comando);
    for (int i=0;i<N_COMANDI;i++){
        if(strcmp(comando,lista_comandi[i])==0){
            index=i;
            return index;
        }
    }
}

void scambia(corsa *p1,corsa *p2){
    corsa temp= *p1; //mi copio dentro una variabile puntatore di tipo struct 'corsa' il valore del puntatore al dato passato(ossia un puntatore.)
    *p1=*p2;
    *p2=temp;

}

void stampa(corsa *arr_tratte,int n_tratte){
    char comando[MAX_CHAR_COMANDO];
    FILE *fpout;
    printf("ordinamento completato! digita 'stampa_file' per stampare su file oppure 'stampa_video' per stampare su terminale!\n");
    int indice_comando=read_comando(comando,lista_comandi);
    switch (indice_comando){
        case stampa_video:
            printf("\nstampa video:\n");
            for(int i=0;i<n_tratte;i++){
                printf(" corsa [%d]  %s %s %s %s %s %s\n",i+1,arr_tratte[i].cod,arr_tratte[i].partenza,arr_tratte[i].destinazione,arr_tratte[i].data,arr_tratte[i].orap,arr_tratte[i].orad,arr_tratte[i].ritardo);
            }
            break;
        case stampa_file:
            fpout=fopen("log.txt","w");
            printf("salvato su log.txt !\n");
            for(int i=0;i<n_tratte;i++){
                fprintf(fpout," corsa [%d]  %s %s %s %s %s %s\n",i+1,arr_tratte[i].cod,arr_tratte[i].partenza,arr_tratte[i].destinazione,arr_tratte[i].data,arr_tratte[i].orap,arr_tratte[i].orad,arr_tratte[i].ritardo);
            }
            fclose(fpout);
            break;

        default:
        printf("\nstampa video di default:\n");
            for(int i=0;i<n_tratte;i++){
                printf(" corsa [%d]  %s %s %s %s %s %s\n",i+1,arr_tratte[i].cod,arr_tratte[i].partenza,arr_tratte[i].destinazione,arr_tratte[i].data,arr_tratte[i].orap,arr_tratte[i].orad,arr_tratte[i].ritardo);
            }
            break;
    }
}
void leggi_file(FILE *f,int *n_linee,corsa *arr_corse){
    int i=0;
    f=fopen(nome_file,"r");
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
void cerca(corsa *arr_tratte,int n_tratte){
    int indice_mod_ric;
    char mod_ricerca[MAX_CHAR_COMANDO];
    char mod[MAX_CHAR_COMANDO]="";
    char input_nome_staz[MAX_CHAR_COMANDO];
    printf("digita 'dicotomica <stazione di partenza da cercare>' oppure 'lineare  <stazione di partenza da cercare>' per scegliere il tipo di ricerca: ");
    scanf("%s %s",mod_ricerca,input_nome_staz);
    for (int i=0;i<N_COMANDI;i++){
        if(strcmp(mod_ricerca,lista_mod_ricerca[i])==0){
            indice_mod_ric=i;
            break;
        }
    }
    switch (indice_mod_ric){
        case dicotomica:
            ric_dico(arr_tratte,n_tratte,input_nome_staz);
            break;
        case lineare:
            ric_lin(arr_tratte,n_tratte,input_nome_staz);
        
        default:
            break;
    }
}