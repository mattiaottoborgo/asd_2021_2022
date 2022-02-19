#include "matrice.h"
#include "limits.h"
static void generaSolR(matrice M,sol Sol, int pos,sol *Best);
static int findmaxdimQ(matrice M,int x0,int y0);
static void riempizona(matrice *M,int x0,int y0,int d, int n);
static int findmaxdimQv2(matrice M,int x0,int y0);

matrice loadM(FILE *fp){
    int NR,NC;
    fscanf(fp,"%d %d",&NR,&NC);
    matrice M;
    M.matr=malloc(NR*sizeof(int));
    for(int i=0;i<NR;i++)
        M.matr[i]=calloc(NC,sizeof(int)); 
    for(int i=0;i<NR;i++)
        for(int j=0;j<NC;j++) 
            fscanf(fp,"%d",&(M.matr[i][j]));
    M.NR=NR;
    M.NC=NC;
    return M;
        
}
sol leggiProposta(FILE *fp){
    sol Sol;int N;
    fscanf(fp,"%d",&N);
    Sol.vett=malloc(N*sizeof(Q));
    for(int i=0;i<N;i++){
        fscanf(fp,"%d %d %d %d",&(Sol.vett[i].x0),&(Sol.vett[i].y0),&(Sol.vett[i].x1),&(Sol.vett[i].y1));
    }
    Sol.N=N;
    Sol.maxN=N;
    return Sol;
}



int verificaM (matrice M, sol proposta){
    int flag=0;
    for(int i=0;i<proposta.N;i++){
        Q tmp= proposta.vett[i];
        if(tmp.x1>=M.NC || tmp.x0>=M.NC || tmp.y0>=M.NR || tmp.y1>=M.NR) {flag=-1;break;}
        if((tmp.x1-tmp.x0) == (tmp.y1-tmp.y0)){
            int d=tmp.x1 - tmp.x0+1;
            for( int x=0;x<d;x++)
                for(int y=0; y<d;y++)
                    M.matr[tmp.y0+y][tmp.x0+x]+=2;
                
        }
        else {flag=-1;break;} // i due lati non sono uguali, quindi non soddisfo condizione di regioni quadrate
    }

    if (flag==0){
        for(int i=0;i<M.NR && flag==0;i++){
            for(int j=0;j<M.NC && flag==0;j++){
                if(M.matr[i][j]==0 || M.matr[i][j]>2){
                    flag=-1;
                    } 
            }
        }
    }
    for(int k=0;k<proposta.N;k++){
        Q tmp= proposta.vett[k];
        int d=tmp.x1 - tmp.x0+1;
            for( int x=0;x<d;x++)
                for(int y=0; y<d;y++)
                    M.matr[tmp.y0+y][tmp.x0+x]-=2;
    }
    
    if(flag==-1) return -1;
    
    return proposta.N;
}
void printSol(sol Sol){
    printf("numero sottoregioni: %d\n",Sol.N);
    for(int i=0;i<Sol.N;i++){
        Q q=Sol.vett[i];
        printf("sottoregione %d: (x0,y0)=(%d,%d), (x1,y1)=(%d,%d)\n",i,q.x0,q.y0,q.x1,q.y1);
    }
}

sol generaSolottima(matrice M){
    sol Best,Sol; 
    Best.vett=malloc(M.NR*M.NC*sizeof(Q));
    Best.N=M.NR*M.NC;
    Best.maxN=M.NR*M.NC;
    Sol.vett=malloc(sizeof(Q));
    Sol.N=0;
    Sol.maxN=1;
    generaSolR(M,Sol,0,&Best);
    printSol(Best); return Best;
}
static void generaSolR(matrice M, sol Sol,int pos, sol *Best){
    int i,j;
    if (Sol.N>Best->N) {
        return ;}

    if(pos>(M.NR)*(M.NC)-1){
        if(Sol.N<Best->N)
        if(verificaM(M,Sol)!=-1){
            solcopy(&Sol,Best);
        }
        return;
    }
    i=pos/(M.NR);j=pos%(M.NC);
    if(M.matr[i][j]==0){
        int dimMaxQ=findmaxdimQ(M,j,i);
        for(int d=dimMaxQ;d>=0;d--){
            riempizona(&M,j,i,d,-1);
            aggiungiQ(&Sol,j,i,d);
            generaSolR(M,Sol,pos+d+1,Best);
            rimuoviQ(&Sol);
            riempizona(&M,j,i,d,0);
        }
    }
    else generaSolR(M,Sol,pos+1,Best);
    
    return;
    
}
void solcopy(sol *source,sol *destination){
    //free(destination.vett);
    destination->vett=realloc(destination->vett,source->N*sizeof(Q));
    for(int i=0;i<source->N;i++){
        destination->vett[i]=source->vett[i];
    }
    destination->N=source->N;
    destination->maxN=source->maxN;
}

//funzione utilizzata nel compito

static int findmaxdimQ(matrice M, int x0, int y0){
    int d,dmax=0,flag;

    for(d=0;y0+d<M.NR && x0+d<M.NC;d++){
        flag=0;
        for(int i=y0;i<=y0+d && flag==0;i++){
            for(int j=x0;j<=x0+d && flag==0;j++){
                if(M.matr[i][j]!=0){
                    flag=1;
                }
            }
        }
        if(flag==0 && d>dmax)dmax=d;
    }
    return dmax;
}



//versione ottimizzata
static int findmaxdimQv2(matrice M,int x0,int y0){
    int d,dmax=0,flag=0;
    for(d=0;y0+d<M.NR && x0+d<M.NC && flag==0;d++){
        flag=0;

        for(int i=y0;i<=y0+d && flag==0;i++){
            if(M.matr[i][x0+d]!=0){
                    flag=1;
                }
        }
        for(int j=x0;j<=x0+d && flag==0;j++){
            if(M.matr[y0+d][j]!=0){
                    flag=1;
                }
        }
        if(flag==0 && d>dmax)dmax=d;
    }
    return dmax;
}
//funzione che riempe una sottoregione quadrata con l'intero desiderato
void riempizona(matrice *M,int x0, int y0, int d, int n){
    for(int i=y0;i<=y0+d;i++){
        for(int j=x0;j<=x0+d;j++){
            M->matr[i][j]=n;
        }
    }
}
void aggiungiQ(sol *Sol, int x0,int y0, int d){
    if(Sol->N>= Sol->maxN){
        Sol->vett=realloc(Sol->vett,2*(Sol->N)*sizeof(Q));
        Sol->maxN=2*Sol->N;
    }
    Q tmp; tmp.x0=x0;tmp.y0=y0; tmp.x1=x0+d;tmp.y1=y0+d;
    Sol->vett[(Sol->N)++]=tmp;
}
//chiaramente non era necessario una funzione per questo comando, è stata aggiunta solamente per mettere in risalto
//la parte di backtrack, la quale è "speculare" rispetto alla parte di "riempimento" della soluzione (aggiungi Q)
void rimuoviQ(sol *Sol){
    (Sol->N)--;
}