  #include "stdio.h"
 #include "stdlib.h"
 #define diff_pietre 4
 #define file "hard_test_set.txt"
enum{zaffiro=0,rubino=1,topazio=2,smeraldo=3};
typedef int sol;
typedef struct {
    int succ1;
    int succ2;
}pietra;


typedef struct{
    int*vett;
    int l;
}catena;
char pietre[diff_pietre]={'z','r','t','s'};
catena*  inizializza_catena(int n);
 int disp_rip(int *sol, int k, int n,int pos,int z,int s,int r,int t,int *mark);
int generaCollane(int*pietre,pietra *listaSucc);
int calcColl(sol ****M,int *pietre,int pietra_id,pietra*listaSucc);
sol***** allocaMatr(int *pietre);
 int main(){
     int l;
     pietra *listaSucc=malloc(diff_pietre*sizeof(pietra));
     listaSucc[zaffiro].succ1=zaffiro;
     listaSucc[zaffiro].succ2=rubino;
     listaSucc[rubino].succ1=smeraldo;
     listaSucc[rubino].succ2=topazio;
     listaSucc[topazio].succ1=zaffiro;
     listaSucc[topazio].succ2=rubino;
     listaSucc[smeraldo].succ1=smeraldo;
     listaSucc[smeraldo].succ2=topazio;
    int length_file;
    FILE *fp;
    fp=fopen(file,"r");
    int *pietre=malloc(diff_pietre*sizeof(int));
    fscanf(fp,"%d",&length_file);
    for(int i=0;i<length_file;i++){
        printf("TEST #%d\n",i+1);
        fscanf(fp,"%d %d %d %d",&pietre[zaffiro],&pietre[rubino],&pietre[topazio],&pietre[smeraldo]);
        l=generaCollane(pietre,listaSucc);
        printf("la collana di valore massimo è %d\n",l);
    }

 }
 int generaCollane(int*pietre,pietra *listaSucc){
    int max=0;
    sol***** M;
    M=allocaMatr(pietre);
    for(int i=0;i<diff_pietre;i++){
        pietre[i]--;
        int l=calcColl(M[i],pietre,i,listaSucc);
        pietre[i]++;
        if(l>max)max=l;
    }
    return max;
 }

sol***** allocaMatr(int *pietre){
    sol*****M=malloc(diff_pietre*sizeof(*M));
    for(int i=0;i<diff_pietre;i++){
        M[i]=(sol****)malloc((pietre[zaffiro]+1)*sizeof(**M));
        for(int j=0;j<pietre[zaffiro]+1;j++){
            M[i][j]=(sol***)malloc((pietre[rubino]+1)*sizeof(***M));
            for(int k=0;k<pietre[rubino]+1;k++){
                M[i][j][k]=(sol**)malloc((pietre[topazio]+1)*sizeof(****M));
                for(int z=0;z<pietre[topazio]+1;z++){
                    M[i][j][k][z]=(sol*)malloc((pietre[smeraldo]+1)*sizeof(*****M));
                    for(int l=0;l<pietre[smeraldo]+1;l++){
                        M[i][j][k][z][l]=-1;
                    }
                }
            }
        }

    }
    return M;
}
int calcColl(sol ****M,int *pietre,int pietra_id,pietra*listaSucc){
    int succ1=listaSucc[pietra_id].succ1;
    int succ2=listaSucc[pietra_id].succ2;




    //controllo se effettivamente posso prendere pietra
    if(pietre[pietra_id]<0){
        //rimetto pietra-->non so se giusto---penso di no
       // M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]]=0;//non posso proseguire!
        return 0;
    }
    //controllo se soluzione è già stata calcolata prima
    if(M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]]!=-1)
        return M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]];
        //guardo se M[z][r][t][s] è !=-1;
        //ritorno valore trovato

    

    //calcolo valore mettendo prima pietra possibile
    pietre[succ1]--;
    int r1 =calcColl(M,pietre,succ1,listaSucc)+1;
    pietre[succ1]++;

    //calcolo valore mettendo seconda pietra possibile
    pietre[succ2]--;
    int r2= calcColl(M,pietre,succ2,listaSucc)+1;
    pietre[succ2]++;

    //se sono giunto fino a qui, significa che qunado ho chiamato la funzione, non avevo il valore già salvato!
    //ritorno quello che mi conviene di più tra i due.

    //mi salvo la soluzione parziale
    //m[][][][]=max(r1,r2)
    if(r1>r2 ) {

        M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]]=r1;
        
        return r1;
        }

    else {
        M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]]=r2;
        return r2;
    }

}


catena*  inizializza_catena(int n){
    catena* c=malloc(sizeof(*c));
    (*c).vett=malloc(n*sizeof(int));
    (*c).l=n;
    return c;
}

//come salvo pietre;

///struct in cui metto un vettore
//per scorrere nel vettore, faccio scorrere indice di n pietre - pietre disponibili