#include "stdlib.h"
#include "stdio.h"
#include "matrice.h"
#define file_matrice   "griglia_compito.txt"
#define file_proposta  "proposta_compito.txt"

int main(){
    matrice M;
    sol proposta;
    FILE *fm,*fp;
    fm=fopen(file_matrice,"r");
    fp=fopen(file_proposta,"r");
    M=loadM(fm);
    proposta=leggiProposta(fp);
    
    if( verificaM(M,proposta)!=-1){
        printf("la soluzione proposta è valida e contiene %d sottoregioni!\n", proposta.N);
        printSol(proposta);
    }
    else printf("soluzione proposta non valida!\n");
    printf("Soluzione ottimaa:\n");
    sol Best=generaSolottima(M);

    return 0;
}