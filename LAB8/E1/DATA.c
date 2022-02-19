#include "DATA.h"
#include "stdlib.h"
#include "stdio.h"
#define MAXCHAR 100
Data DATAnull(){
    Data tmp;
    tmp.anno=-1;
    tmp.mese=-1;
    tmp.giorno=-1;
    return tmp;
}
int DATAcheckNull(Data d){
    return d.anno==-1;
}
Data leggiData(FILE*fp){
    Data tmp;
    fscanf(fp,"%d %d %d",&tmp.anno,&tmp.mese,&tmp.giorno);
    return tmp;
}
Orario leggiOrario(FILE*fp){
    Orario tmp;
    fscanf(fp,"%d %d",&tmp.ora,&tmp.minuto);
    return tmp;
}
Data DATAprint(Data d){
    printf("data: %d/%d/%d\n",d.anno,d.mese,d.giorno);
}
Data DATAinput(){
    int anno,mese,giorno;
    char str[MAXCHAR];
    printf("inserisci data nel seguente formato: aaaa/mm/dd\n");
    scanf("%s",str);
    sscanf(str,"%d/%d/%d",&anno,&mese,&giorno);
    return DATAcreate(anno,mese,giorno);
}
//ritorna 0 se uguali , 1 se viene dopo, -1 se viene prima
//ordine cronologico
int DATAcompare(Data d1,Data d2){
    if(d1.anno<d2.anno) return -1;
    else if(d1.anno>d2.anno) return 1;
    else if(d1.anno==d2.anno){
        if(d1.mese<d2.mese)return -1;
        else if(d1.mese>d2.mese)return 1;
        else if(d1.mese==d2.mese){
            if (d1.giorno<d2.giorno)return -1;
            else if(d1.giorno>d2.giorno)return 1;
            else return 0;
        }
    }
}

Data DATAcreate(int anno, int mese, int giorno){
    Data tmp;
    tmp.anno=anno;
    tmp.mese=mese;
    tmp.giorno=giorno;
    return tmp;
}