#include "stdlib.h"
#include "stdio.h"
#include "mod_pers.h"
#define inv_file "inventario.txt"
#define pg_file "pg.txt"
#define MAXC_COM 100
enum {carica_personaggi,carica_oggetti,aggiungi_personaggio,elimina_personaggio,aggiungi_oggetto,rimuovi_oggetto,calcola_statistiche,uscita,LEN_LIST_COM};
char *LISTA_COMANDI[]={"carica_personaggi","carica_oggetti","aggiungi_personaggio","elimina_personaggio","aggiungi_oggetto","rimuovi_oggetto","calcola_statistiche","uscita"};
void menu();
void printComandi();
int checkComando(char *comando);
void inizializza(LIST *list,tab_inv_p *t_inv);
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
    char codice_personaggio[MAXC_COM];
    char n_ogg[MAXC_COM];
    char n_pers[MAXC_COM];
    LIST list;
    tab_inv_p t_inv;
    PG t_pg;
    inizializza(&list,&t_inv);
    while(1){
        printComandi();
        scanf("%s",comando);
        index_comando=checkComando(comando);
        switch(index_comando){
            case carica_personaggi:
            printf("inserisci nome file contenente lista personaggi: ");
            scanf("%s",filename_pg);
            list=initPgList(filename_pg);
            printf("caricamento lista personaggi completato\n");
            break;
            case carica_oggetti:
            printf("inserisci nome file contenente lista oggetti: ");
            scanf("%s",filename_inv);
            t_inv=createTab(filename_inv);
            break;
            case aggiungi_personaggio:
            t_pg=createPg(list);
            list= addPg(list,t_pg);
            printf("\n");
            break;
            case elimina_personaggio:
            printf("inserisci codice personaggio da eliminare: ");
            scanf("%s",codice_personaggio);
            list=DelPg(codice_personaggio,list);
            break;
            case aggiungi_oggetto:
            printf("inserisci nome oggetto da aggiungere all 'equipaggiamento: ");
            scanf("%s",n_ogg);
            printf("inserisci nome personaggio a cui aggiungere l'oggetto: ");
            scanf("%s",n_pers);
            addObjToPg(n_ogg,n_pers,list,t_inv);
            break;
            case rimuovi_oggetto:
            printf("inserisci nome oggetto da eliminare dall 'equipaggiamento: ");
            scanf("%s",n_ogg);
            printf("inserisci nome personaggio da cui rimuovere l'oggetto: ");
            scanf("%s",n_pers);
            delObjFromPg(n_ogg,n_pers,list,t_inv);
            break;
            case calcola_statistiche:
            printf("inserisci nome personaggio di cui si vogliono calcolare le statistiche: ");
            scanf("%s",codice_personaggio);
            calcolaStat(codice_personaggio,list,t_inv);
            break;
            case uscita:
                freePgList(list);
                exit(0);
            break;



        }
        
    }
}
void printComandi(){

    printf("Inserisci uno dei seguenti comandi:\n");
    printf("carica_personaggi\ncarica_oggetti\naggiungi_personaggio\nelimina_personaggio\naggiungi_oggetto\nrimuovi_oggetto\ncalcola_statistiche\nuscita\n");
    

    printf("-->");

}
int checkComando(char *comando){
    int i;
    for( i=0;i<LEN_LIST_COM;i++){
        if(strcmp(comando,LISTA_COMANDI[i])==0) return i;
    }
    return -1;
}
void inizializza(LIST *list,tab_inv_p *t_inv){
    *list=initPgList(pg_file);
    *t_inv=createTab(inv_file);
    return;
}
