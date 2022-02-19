#include "mod_pers.h"




link newNode(pg Pg,link next){
    link x=malloc(sizeof *x);
    if(x==NULL)return NULL;
    x->value =Pg;
    x->next=next;
    return x;
}
link initPgList(char *filename){//inserimento in testa
    FILE *fp;
    fp=fopen(filename,"r");
    link head=NULL;
    head=newNode(loadPg(fp),NULL);//
    int flag=0;
    if(checkValidPg(head->value)==0) return NULL;
    else flag=1;
    while(flag!=0){
        pg t=loadPg(fp);
        flag=checkValidPg(t);
        if(flag!=0)
        head=newNode(t,head);
    }
    return head;
}

pg loadPg(FILE *fp){
    pg t;
    //if(fscanf(fp,"%s %s %s %d %d %d %d %d %d",(t.codice),(t.nome),(t.classe),&t.stat.hp,&t.stat.mp,&t.stat.atk,&t.stat.def,&t.stat.mag,&t.stat.spr)==9);
    if(fscanf(fp,"%s %s %s",(t.codice),(t.nome),(t.classe))==3)
        t.stat=riempi_stat(fp);
    else t=nullPg();
    return t;
}
int lenListPg(link head){
    link x;
    int cnt=0;
    for(x=head;x!=NULL;x=x->next,cnt++);
    return cnt;

}
pg createPg(int *N_pg){
    pg t;
    char codice[LEN_CODICE]="PG";
    char num[MAX_PG];
    //assegna in automatico il numero al pg (migliorabile calcolando potenza di 10)
    if ((*N_pg)<=9 && (*N_pg)>=0) strcat(codice,"000");
    else if ((*N_pg)>=10 && (*N_pg)<=99) strcat(codice,"00");
    else if ((*N_pg)>=100 && (*N_pg)<=999) strcat(codice,"0");
    (*N_pg)++;
    itoa((*N_pg),num,10);
    
    strcat(codice,num);
    strcpy(t.codice,codice);
    printf("inserisci nome: ");
    scanf("%s",t.nome);
    printf("inserisci classe: ");
    scanf("%s",t.classe);
    t.stat=creaStat();
    return t;
}
pg nullPg(){
    pg t;
    strcpy(t.nome,"\0");
    strcpy(t.codice,"\0");
    strcpy(t.classe,"\0");
    t.stat=nullStat();
    return t;
}
 int checkValidPg(pg Pg){
     return strcmp(Pg.codice,"\0");
 }
 link addPg(link head,pg Pg){
     if (checkValidPg(Pg)!=0) {
         head=newNode(Pg,head);
     }
     return head;
 }
 Stat creaStat(){
     Stat t;
     printf("inserisci hp: ");
     scanf("%d",&t.hp);
     printf("inserisci mp: ");
     scanf("%d",&t.mp);
     printf("inserisci atk: ");
     scanf("%d",&t.atk);
     printf("inserisci def: ");
     scanf("%d",&t.def);
     printf("inserisci mag: ");
     scanf("%d",&t.mag);
     printf("inserisci spr: ");
     scanf("%d",&t.spr);
     return t;
 }