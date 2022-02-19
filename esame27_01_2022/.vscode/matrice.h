#include "stdlib.h"
#include "stdio.h"
typedef struct {
    int **matr,NR,NC;
}matrice;

typedef struct{
    int x0,y0,x1,y1;
}Q;

typedef struct {
    Q*vett;
    int maxN;
    int N;
}sol;

matrice loadM(FILE *fp);
sol leggiProposta(FILE *fp);
int verificaM(matrice M, sol proposta);
sol generaSolottima(matrice M);
void printSol(sol Sol);
void solcopy(sol *source,sol *destination);
void aggiungiQ(sol *Sol, int x0,int y0, int d);
void rimuoviQ(sol *Sol);

