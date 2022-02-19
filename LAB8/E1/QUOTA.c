#include "QUOTA.h"

Quota QUOTANull(){
    Quota quota;
    quota.valore=0;
    quota.numero_scambi=1;
    quota.data=DATAnull();
    return quota;
}
Quota QUOTAcreate(Data data,int valore,int numero_scambi){
    Quota tmp;
    tmp.data=data;
    tmp.valore=valore*numero_scambi;
    tmp.numero_scambi=numero_scambi;
    return tmp;
}
void QUOTAupdate(Quota * quota,int valore,int numero_scambi){
    quota->valore+=valore *numero_scambi;
    quota->numero_scambi+=numero_scambi;
}
int QUOTAcmp(Quota q1,Quota q2){
    if((q1.valore/q1.numero_scambi)>(q2.valore/q2.numero_scambi)) return 1;
    else if((q1.valore/q1.numero_scambi)<(q2.valore/q2.numero_scambi)) return -1;
    else if((q1.valore/q1.numero_scambi)==(q2.valore/q2.numero_scambi)) return 0;
}
void QUOTAprint(Quota q){
    printf("valore: %d\n",q.valore);
    printf("numero scambi: %d\n",q.numero_scambi);
    DATAprint(q.data);
}
int QUOTAchecknull(Quota q){
    return DATAcheckNull(q.data);
}