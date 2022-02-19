#ifndef DATA_HEADER
#define DATA_HEADER

#include "stdio.h"
typedef struct {int anno;int mese;int giorno;}Data;
typedef struct {int ora;int minuto;}Orario;
Data DATAnull();
Data DATAcreate(int anno, int mese, int giorno);
Data leggiData(FILE*fp);
Data DATAinput();
int DATAcheckNull(Data d);
Data DATAprint(Data d);
Orario leggiOrario(FILE*fp);
int DATAcompare(Data d1,Data d2);
#endif