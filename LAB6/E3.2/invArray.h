#ifndef INVARRAY_H_DEFINED
#define INVARRAY_H_DEFINED

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inv.h"

/* ADT di prima classe collezione di oggetti di inventario */
typedef struct invArray_s *invArray_t;

/* creatore e disruttore */
invArray_t invArray_init();  ////ok
void invArray_free(invArray_t invArray);

/* lettura e scrittura su file */
void invArray_read(FILE *fp, invArray_t invArray); ///ok
void invArray_print(FILE *fp, invArray_t invArray); ///ok
/* stampa un unico oggetto selezionato da indice (nel vettore) */
void invArray_printByIndex(FILE *fp, invArray_t invArray, int index);///ok
/* ritorna puntatore a oggetto selezionato da indice (nel vettore) */
inv_t *invArray_getByIndex(invArray_t invArray, int index);///ok
/* ritorna indice (nel vettore) a oggetto selezionato da nome */
int invArray_searchByName(invArray_t invArray, char *name);///ok

/* Si possono aggiungere altre funzioni se ritenute necessarie */

#endif
