#ifndef QUOTA_HEADER
#define QUOTA_HEADER
#include "DATA.h"
#include "limits.h"
typedef struct{int valore; Data data;int numero_scambi;}Quota;
Quota QUOTANull();
Quota QUOTAcreate(Data data,int valore,int numero_scambi);
int QUOTAcmp(Quota q1,Quota q2);
void QUOTAprint(Quota q);
int QUOTAchecknull(Quota q);
void QUOTAupdate(Quota * quota,int valore,int numero_scambi);
#endif