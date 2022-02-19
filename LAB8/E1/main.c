#include"TITOLI.h"
#include"string.h"
#define MAXCHAR 100
enum{load_file,search,get_quote,get_min_intervall,get_max_intervall,get_min,get_max,balance,end,print_com,NUM_COM};
char *lista_com[]={"load_file","search","get_quote","get_min_intervall","get_max_intervall","get_min","get_max","balance","exit","print_com"};
void PRINTCOMANDI();
int com_getIndex(char* com);
int main(){
    char com[MAXCHAR];
    char filename[MAXCHAR];
    char name[MAXCHAR];
    int index_com;
    LIST list;
    FILE *fp=NULL;
    TITOLO titolo;
    Quota quote,min,max,min_int,max_int;
    Data d1,d2;
    printf("lista comandi:\n");
    PRINTCOMANDI();
    while(1){
        printf("\ninserisci comando da eseguire: ");
        scanf("%s",com);
        index_com=com_getIndex(com);
        switch(index_com){
            case load_file:
            while(fp==NULL){
            printf("inserisci nome file: ");
            scanf("%s",filename);
            fp=fopen(filename,"r");
            }
            list=loadCollection(fp);
            break;
            case search:
                printf("inserisci nome titolo da cercare: ");
                scanf("%s",name);
                titolo=TITOLOsearch(list,name);
                if(TITOLOcheckNull(titolo))printf("Titolo non trovato!\n");
                else printf("titolo trovato!\n");
            break;
            case get_quote:
                d1=DATAinput();
                quote=TITOLOgetQuota(titolo,d1);
                if(QUOTAchecknull(quote))printf("Nessuna quota per la data selezionata!\n");
                else QUOTAprint(quote);
            break;
            case get_min_intervall:
                d1=DATAinput();
                d2=DATAinput();
                min_int=TITOLOgetIntervallminQUOTA(titolo,d1,d2);
                if(QUOTAchecknull(min_int))printf("Nessuna quota per l'intervallo selezionato!\n");
                else QUOTAprint(min_int);
            break;
            case get_max_intervall:
                d1=DATAinput();
                d2=DATAinput();
                max_int=TITOLOgetIntervallmaxQUOTA(titolo,d1,d2);
                if(QUOTAchecknull(max_int))printf("Nessuna quota per l'intervallo selezionato!\n");
                else QUOTAprint(max_int);
            break;
            case get_min:
                min=TITOLOgetminQUOTA(titolo);
                QUOTAprint(min);
                break;
            case get_max:
                max=TITOLOgetmaxQUOTA(titolo);
                QUOTAprint(max);
                break;
            case balance:
            TITOLObalance(titolo,0);
            break;
            case end:
             return 0;
            break;
            case print_com:
                printf("lista comandi:\n");
                PRINTCOMANDI();
            break;
            default:
                printf("Errore: comando non valido!\n");
            break;
        }
    }
}
void PRINTCOMANDI(){
    for(int i=0;i<NUM_COM;i++)
        printf("%s\n",lista_com[i]);
}
int com_getIndex(char* com){
    for(int i=0;i<NUM_COM;i++){
        if(!strcmp(com,lista_com[i])) return i;
    }
    return -1;
}