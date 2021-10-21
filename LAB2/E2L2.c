#include "stdio.h"
#include "stdlib.h"
#define filename "mat.txt"
int **malloc2dR();
void malloc2dP(int ***m);
void separa(int **mat ,int nr,int nc,int *bianchi, int *neri);
int main(){
    FILE *fp;
    int nr,nc;
    int **m; //puntatore a matrice
    fp=fopen(filename,"r");
    fscanf(fp,"%d %d",&nr,&nc);
    int size=nr*nc/2;
    int *bianchi= (int*) malloc((size+1)*sizeof(int));
    int *neri= (int *) malloc(size*sizeof(int));
    int **matrix;
    int **matrix2;
    matrix=malloc2dR(fp,nr,nc);
    malloc2dP(&matrix2);
    separa(matrix,nr,nc,bianchi,neri);
    printf("\n");

}

int **malloc2dR(FILE *fp,int nr,int nc){

  int **m; //puntatore a matrice

  m= (int **) malloc(nr*sizeof(int *));
  for(int i=0;i<nr;i++){
      m[i]= (int *) malloc(nc*sizeof(int));
  }
  for(int i=0;i<nr;i++){
      for(int j=0;j<nc;j++){
          fscanf(fp,"%d",&m[i][j]);
      }
  }
  return m;
}

void malloc2dP(int ***m){
  FILE *fp;
  int nr,nc;
  fp=fopen(filename,"r");
  fscanf(fp,"%d %d",&nr,&nc);
  int **m_temp;
  m_temp= (int **) malloc(nr*sizeof(int *));
  for(int i=0;i<nr;i++){
      m_temp[i]= (int *) malloc(nc*sizeof(int));
  }
  for(int i=0;i<nr;i++){
      for(int j=0;j<nc;j++){
          fscanf(fp,"%d",&m_temp[i][j]);
      }
  }
  *m=m_temp;

}
void separa(int **mat ,int nr,int nc,int *bianchi, int *neri){
    int size=nr*nc/2;
    int z=0;
    for(int i=0;i<nr;i++){
        for(int j=0;j<nc;j++){
            if((i+j)%2==0){//bianchi
                bianchi[z]=mat[i][j];
            }
            else{
                neri[z++]=mat[i][j];


            }
        }
    }

}