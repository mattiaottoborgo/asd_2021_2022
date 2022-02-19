#include "stdio.h"
#include "stdlib.h"
#define f_tile "tiles.txt"
#define f_board "board.txt"

 typedef struct{
     int ruotato;
     char coloreT1;
     int valoreT1;
     char coloreT2;
     int valoreT2;
 }tessera;
tessera leggiTessera(tessera *vett_t,FILE *fp,int *i,int *r);
tessera* riempiVettTess(tessera* lista,int *length);
tessera **riempi_scacchiera(tessera *vett_t, int *R,int *C,int*mark,int **mark_cas,int *cas_occ,int **ruotati);
tessera nullItem();
tessera ** copia_scacchiera(tessera **s,int R,int C);
int checkValid(tessera item);
int calcolo_punteggio(tessera **s,int R,int C,int *ruotati);
void print_tessera(tessera **s,int R, int C,int *ruotati);
void disp(tessera *vett_t,tessera **s,int k,int n,int pos,int *ruotati,int R,int C,int *mark,int *mark_c,int *p_max,tessera ***smax);
int main(){
    tessera *vett_tessere;
    int n_tessere;
    vett_tessere=riempiVettTess(vett_tessere,&n_tessere);
    int R,C;
    int *mark_tess=calloc(n_tessere,sizeof(int)); //vettore caselle già utilizzate
    int *mark_caselle;
    int cas_occ=0;
     int *ruotati;   //vettore di supporto per controllare se casella è ruotata o meno.
    tessera **scacchiera=riempi_scacchiera(vett_tessere,&R,&C,mark_tess,&mark_caselle,&cas_occ,&ruotati);
    print_tessera(scacchiera,R,C,ruotati);
    int p_max=0;
    tessera **max;
    disp(vett_tessere,scacchiera,R*C-cas_occ,n_tessere,0,ruotati,R,C,mark_tess,mark_caselle,&p_max,&max);
    printf("soluzione con punteggio massimo:\n");
    print_tessera(max,R,C,ruotati);
    printf("punteggio: %d",p_max);

}

tessera* riempiVettTess(tessera* lista,int *length){
    FILE *fp;
    fp=fopen(f_tile,"r");
    fscanf(fp,"%d\n",length);
    tessera tmp;
    tessera *tmp_lista=malloc((*length)*sizeof(tessera));
    for(int i=0;i<*length;i++){
        fscanf(fp,"%c %d %c %d\n",&tmp.coloreT1,&tmp.valoreT1,&tmp.coloreT2,&tmp.valoreT2);
        tmp_lista[i]=tmp;      
    }
    lista=tmp_lista;
    return lista;
}
tessera **riempi_scacchiera(tessera *vett_t, int *R,int *C,int*mark,int **mark_cas,int *cas_occ,int **ruotati){
    FILE *fp;
    fp=fopen(f_board,"r");

    fscanf(fp,"%d %d",R,C);

    int *mark_c=calloc((*R)*(*C),sizeof(int)); //vettore che indica caselle scacchiera gia occ
    int *ruotati_t=calloc((*R)*(*C),sizeof(int));
    for(int i=0;i<*R;i++){
    }
    tessera **righe=(tessera **)malloc((*R)*sizeof(tessera*));
    for(int i=0;i<*R;i++){
        tessera *riga=(tessera *)malloc((*C)*sizeof(tessera));
        for(int j=0;j<*C;j++){
            int index,r;
            riga[j]=leggiTessera(vett_t,fp,&index,&r);
            if(checkValid(riga[j])) {
                mark[index]=-1;//elemento già utilizzato
                mark_c[i*(*R)+j]=-1;
                *cas_occ+=1;
                ruotati_t[i*(*R)+j]=r;
            }           
        }
        righe[i]=riga;

    }
    *mark_cas=mark_c;
    *ruotati=ruotati_t;
    return righe;
}

tessera leggiTessera(tessera *vett_t,FILE *fp,int *i,int*r){
    tessera tmp;
    fscanf(fp,"%d/%d",i,r);
    if(*i==-1 && *r==-1) return nullItem();
    tmp=vett_t[*i];
    tmp.ruotato=*r;
    return tmp;

}

tessera nullItem(){
    tessera tmp;
    tmp.coloreT1='\0';
    tmp.valoreT1=-1;
    tmp.coloreT2='\0';
    tmp.valoreT2=-1;
    return tmp;
}
void print_tessera(tessera **s,int R, int C,int *ruotati){
    for(int i=0;i<R;i++){
        for(int j=0;j<C;j++){
            printf("{ ");
            printf("%d: %c %d %c %d",ruotati[i*R+j],s[i][j].coloreT1,s[i][j].valoreT1,s[i][j].coloreT2,s[i][j].valoreT2);
            printf(" } ");
        }
        printf("\n");
    }
}
void disp(tessera *vett_t,tessera **s,int k,int n,int pos,int *ruotati,int R,int C,int *mark,int *mark_c,int*p_max,tessera ***smax){
    int z;
    if(pos>=n){
      int punteggio=calcolo_punteggio(s,R,C,ruotati);
      if(punteggio!=0){
        //printf("soluzione :\n");
        //print_tessera(s,R,C);
       // printf(" \n");
        if(punteggio>*p_max){
            *p_max=punteggio;
            *smax=copia_scacchiera(s,R,C);
        }
      }
        return;
    }
    for(z=0;z<n;z++){//pos 3--4 casella
        int j=pos%C; //j-->0
        int i=pos/R; //i-->1
        //devo controllare che casella non sia una di quelle preimpostate e che la tessera non sia una di quelle iniziali
        if (mark_c[pos]==-1)  disp(vett_t,s,k,n,pos+1,ruotati,R,C,mark,mark_c,p_max,smax);
        else if(mark[z]==0 && mark_c[pos]==0){
            s[i][j]=vett_t[z];
            mark[z]=1;
            mark_c[pos]=1;
            (ruotati)[z]=0;
            disp(vett_t,s,k,n,pos+1,ruotati,R,C,mark,mark_c,p_max,smax);
            (ruotati[z])=1;
            disp(vett_t,s,k,n,pos+1,ruotati,R,C,mark,mark_c,p_max,smax);
            mark[z]=0;
            mark_c[pos]=0;
        }


    }
    return ;
}

int checkValid(tessera item){
    if(item.coloreT1=='\0' || item.valoreT1==-1 || item.coloreT2=='\0' || item.valoreT2==-1) return 0;
    return 1;
}
int calcolo_punteggio(tessera **s,int R,int C,int *ruotati){
    //se 0-->T1 verticale, t2 or
    //se 1-->t2 vert, t1 or
    int i,j;
    int punteggio=0;
    //controllo su righe
    for(int i=0;i<R;i++){
        char c;
        int somma_riga=0;
        if(ruotati[i*R+C]==0) { c=s[i][0].coloreT2;}
        else { c=s[i][0].coloreT1;}
        for(int j=0;j<C;j++){
            char c_curr;
            int val;
            if(ruotati[i*R+j]==0) { 
                c_curr=s[i][j].coloreT2;
                val=s[i][j].valoreT2;
                }
            else { 
                c_curr=s[i][j].coloreT1;
                val=s[i][j].valoreT1;
                }
            if(c_curr!=c){
                somma_riga=0;
                break;
            }
        somma_riga+=val;
        }
        punteggio+=somma_riga;
    }
    //controllo colonne
    //se 0-->T1 verticale, t2 or
    //se 1-->t2 vert, t1 or
    for(int j=0;j<C;j++){
        char c;
        int somma_colonna=0;
        if(ruotati[j]==0) { 
            c=s[0][j].coloreT1;
            }
        else { 
            c=s[0][j].coloreT2;
            }
        for(int i=0;i<R;i++){
            char c_curr;
            int val;
            if(ruotati[i*R+j]==0) { 
                c_curr=s[i][j].coloreT1;
                val=s[i][j].valoreT1;
                }
            else { 
                c_curr=s[i][j].coloreT2;
                val=s[i][j].valoreT2;
                }
            if(c_curr!=c){
                somma_colonna=0;
                break;
            }
            somma_colonna+=val;
        }
        punteggio+=somma_colonna;
    }
    return punteggio;

}
tessera ** copia_scacchiera(tessera **s,int R,int C){
    tessera *riga=malloc(C*sizeof(tessera));
    tessera **tmp_s=malloc(R*sizeof(riga));
    for(int i=0;i<R;i++){
        riga=malloc(C*sizeof(tessera));
        for(int j=0;j<C;j++){
            riga[j]=s[i][j];
        }
        tmp_s[i]=riga;
    }
    return tmp_s;
}