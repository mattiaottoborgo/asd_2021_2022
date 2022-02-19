#include "stdlib.h"
#include "stdio.h"
#include "TITOLI.h"
typedef struct titoloNode *link_t;
struct titoloNode{
    TITOLO titolo;
    link_t next;
};
struct lista_titoli{
    link_t head;
};


void leggiFile(FILE *fp){
    int numero_transazioni;
    char nome[MAXC];
    while(fscanf(fp,"%s %d",nome,&numero_transazioni)==2){
        TITOLO titolo=initTitolo(nome,numero_transazioni);
        leggiTransazioni(fp,numero_transazioni);
    }
}