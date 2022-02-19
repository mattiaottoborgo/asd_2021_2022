#ifndef DATA_HEADER
#define DATA_HEADER

#include "stdio.h"
typedef struct {int anno;int mese;int giorno;}Data;
typedef struct {int ora;int minuto;}Orario;
Data DATAnull();
Data leggiData(FILE*fp);
Orario leggiOrario(FILE*fp);
int DATAcompare(Data d1,Data d2);
#endif DATA_HEADER