#ifndef TITOLI_HEADER
#define TITOLI_HEADER
#include "TITOLO.h"
#include "stdlib.h"
#include "string.h"
typedef struct list *LIST;
LIST loadCollection(FILE *fp);
TITOLO TITOLOsearch(LIST list,char*nome);
#endif 