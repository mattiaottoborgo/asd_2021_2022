  #include "stdio.h"
 #include "stdlib.h"
 #define diff_pietre 4
 #define file "hard_test_set.txt"
enum{zaffiro=0,rubino=1,topazio=2,smeraldo=3};
//typedef int sol;
typedef struct {
    int succ1;
    int succ2;
}pietra;

//versione che printa soluzione 


typedef struct{
    int*vett;
    int l;
}sol;
char pietre[diff_pietre]={'z','r','t','s'};
sol*  inizializza_catena(int n);
void printSolution(sol Sol);
sol nullSolution(int n);
sol initSolution(int n);
 int disp_rip(int *sol, int k, int n,int pos,int z,int s,int r,int t,int *mark);
 int sumPietre();
int generaCollane(int*pietre,pietra *listaSucc);
sol calcColl(sol ****M,int *pietre,int pietra_id,pietra*listaSucc,int n_pietre,sol prec,sol *best);
sol***** allocaMatr(int *pietre,int n_pietre);
sol solCopy(sol s);
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
     int n_pietre=sumPietre(pietre);
    sol max=initSolution(n_pietre);
    sol***** M;
    int i;
    sol best1=initSolution(n_pietre);
    for(i=0;i<diff_pietre;i++){
        pietre[i]--;
        M=allocaMatr(pietre,n_pietre);
        sol prec=nullSolution(n_pietre);
        sol best=calcColl(M[i],pietre,i,listaSucc,n_pietre,prec,&best1);
        best.vett[0]=i;
        pietre[i]++;
        if(best1.l>max.l)max=best;
    }
    printSolution(max);
    return max.l;
 }

sol***** allocaMatr(int *pietre,int n_pietre){
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
                        M[i][j][k][z][l]=initSolution(n_pietre);
                    }
                }
            }
        }

    }
    return M;
}
sol calcColl(sol ****M,int *pietre,int pietra_id,pietra*listaSucc,int n_pietre,sol prec,sol *best){
    int succ1=listaSucc[pietra_id].succ1;
    int succ2=listaSucc[pietra_id].succ2;




    //controllo se effettivamente posso prendere pietra
    if(pietre[pietra_id]<0){
       // M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]]=0;//non posso proseguire!
        return nullSolution(n_pietre);
    }
    //controllo se soluzione è già stata calcolata prima
    /*
    int flag=0;
    if(prec.l>=36) 
        flag=1;
        */
    if(M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]].l!=-1)
        return M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]];
        //guardo se M[z][r][t][s] è !=-1;
        //ritorno valore trovato


        //step 1--> copio il valore di prec dentro 
    int k=n_pietre-1-pietre[zaffiro]-pietre[rubino]-pietre[topazio]-pietre[smeraldo];
    for(int i=0;i<n_pietre-1-pietre[zaffiro]-pietre[rubino]-pietre[topazio]-pietre[smeraldo];i++){
        M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]].vett[i]=prec.vett[i];
    }
    M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]].vett[n_pietre-1-pietre[zaffiro]-pietre[rubino]-pietre[topazio]-pietre[smeraldo]]=pietra_id;
    M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]].l=prec.l+1;
    sol tmp=M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]];
    if(M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]].l>best->l){
        *best=M[pietre[zaffiro]][pietre[rubino]][pietre[topazio]][pietre[smeraldo]];
    }

    //calcolo valore mettendo prima pietra possibile
    pietre[succ1]--;
    sol r1 =calcColl(M,pietre,succ1,listaSucc,n_pietre,tmp,best);
    //r1.l+=1;
    pietre[succ1]++;

    //calcolo valore mettendo seconda pietra possibile
    pietre[succ2]--;
    sol r2= calcColl(M,pietre,succ2,listaSucc,n_pietre,tmp,best);
    //r2.l+=1;
    pietre[succ2]++;


    //se sono giunto fino a qui, significa che qunado ho chiamato la funzione, non avevo il valore già salvato!
    //ritorno quello che mi conviene di più tra i due.

    //mi salvo la soluzione parziale
    //m[][][][]=max(r1,r2)
    //if(r1.l && r2.l ==0) return initSolution(n_pietre);


    if(r1.l>=r2.l ) {      
        return r1;
        }

    else if(r2.l>r1.l) {
        return r2;
    }

}


sol*  inizializza_catena(int n){
    sol* c=malloc(sizeof(*c));
    (*c).vett=malloc(n*sizeof(int));
    (*c).l=n;
    return c;
}

sol initSolution(int n){
    sol c;
    (c).l=-1;
    c.vett=malloc(n*sizeof(int));
    return c;
}

sol nullSolution(int n){
    sol c;
    c.l=0;
    c.vett=malloc(n*sizeof(int));
    return c;
}
int sumPietre(int *pietre){
    int sum=0;
    for(int i=0;i<diff_pietre;i++){
        sum+=pietre[i];
    }
    return sum;
}
void printSolution(sol Sol){
    for(int i=0;i<Sol.l;i++){
        printf("%c ",pietre[Sol.vett[i]]);
    }
    printf("\n");
}

sol solCopy(sol s){
    sol *c=malloc(sizeof*c);
    *c=s;
    return *c;
}
//come salvo pietre;

///struct in cui metto un vettore
//per scorrere nel vettore, faccio scorrere indice di n pietre - pietre disponibili