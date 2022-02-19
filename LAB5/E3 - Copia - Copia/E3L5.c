#include "stdlib.h"
#include "stdio.h"
#include "mod_pers.h"
#define inv_file "inventario.txt"
#define pg_file "pg.txt"
#define MAXC_COM 100
enum {carica_personaggi,carica_oggetti,aggiungi_personaggio,elimina_personaggio,aggiungi_oggetto,rimuovi_oggetto,calcola_statistiche,LEN_LIST_COM};
char *LISTA_COMANDI[7]={"carica_personaggi","carica_oggetti","aggiungi_personaggio","elimina_personaggio","aggiungi_oggetto","rimuovi_oggetto","calcola_statistiche"};
int main(){

    menu();
    //carica inventario
    /*
    
    tab_inv_p t_inv=createTab(file);
    item found=searchObj_byName(t_inv,"Excalibur");
    printObjInfo(found);
    printf("ok1");
    link head=NULL;
    head=initPgList(pg_file);

    */

}
void menu(){
    char comando[MAXC_COM];
    int index_comando;
    int N_pg;
    char filename_pg[MAXC_COM];
    char filename_inv[MAXC_COM];
    link head=NULL;
    tab_inv_p t_inv;
    inizializza(&head,&t_inv);
    while(1){
        printComandi();
        scanf("%s",comando);
        index_comando=checkComando(comando);
        switch(index_comando){
            case carica_personaggi:
            printf("inserisci nome file contenente lista personaggi: ");
            scanf("%s",filename_pg);
            head=initPgList(filename_pg);
            printf("caricamento lista personaggi completato");
            break;
            case carica_oggetti:
            printf("inserisci nome file contenente lista oggetti: ");
            scanf("%s",filename_inv);
            t_inv=createTab(filename_inv);
            break;
            case aggiungi_personaggio:
            N_pg=lenListPg(head);
            pg t_pg=createPg(&N_pg);
            head= addPg(head,t_pg);
            printf("\n");
            break;

        }
        
    }
}
void printComandi(){

    printf("Inserisci uno dei seguenti comandi:\n");
    

    printf("-->");

}
int checkComando(char *comando){
    int i;
    for( i=0;i<LEN_LIST_COM;i++){
        if(strcmp(comando,LISTA_COMANDI[i])==0) return i;
    }
    return -1;
}
void inizializza(link *head,tab_inv_p *t_inv){
    *head=initPgList(pg_file);
    *t_inv=createTab(inv_file);
    return;
}
