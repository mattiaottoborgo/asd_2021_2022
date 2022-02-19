#include "equipArray.h"
#define N_COMANDI 2
enum{elimina,aggiungi};
static char *lista_comandi[]={"elimina","aggiungi"};
static int getIndexComando(char *comando){
    for(int i=0;i<N_COMANDI;i++){
        if(strcmp(comando,lista_comandi[i])==0) return i;
    }
    return -1;
}
struct equipArray_s{
 int inUse;
 int *equipList;
};


equipArray_t equipArray_init(){
    equipArray_t equipArray=malloc(sizeof*equipArray);
    equipArray->equipList=malloc(EQUIP_SLOT*sizeof(int));
    for(int i=0;i<EQUIP_SLOT;i++){
        equipArray->equipList[i]=-1;
    }
    equipArray->inUse=0;
    return equipArray;
}
int equipArray_inUse(equipArray_t equipArray){
    return equipArray->inUse;
}
void equipArray_update(equipArray_t equipArray, invArray_t invArray){
    int index_comando;
    char comando[LEN];
    char nome_oggetto[LEN];
    printf("digita <elimina> oppure <aggiungi>: ");
    scanf("%s",comando);
    index_comando=getIndexComando(comando);

    switch(index_comando){
            case elimina:
                if(equipArray->inUse>0){
                    printf("inserisci nome oggetto dell'inventario da inserire: ");
                    scanf("%s",nome_oggetto);
                    int posArray=invArray_searchByName(invArray,nome_oggetto);
                    for(int i=0;i<EQUIP_SLOT;i++){
                        if(equipArray->equipList[i]==posArray){
                            equipArray->equipList[i]=-1;
                            equipArray->inUse--;
                            }
                        }
                }
                else printf("equipaggiamento vuoto!\n");
                //per eliminare faccio searchbyname dell'oggetto nell'inventario, poi cerco l'indice nell'equiplist, dopodichè metto -1
                break;
            case aggiungi:
                if((equipArray->inUse)<EQUIP_SLOT){
                    printf("inserisci nome oggetto dell'inventario da inserire: ");
                    scanf("%s",nome_oggetto);
                    int posArray=invArray_searchByName(invArray,nome_oggetto);
                    for(int i=0;i<EQUIP_SLOT;i++){
                        if(equipArray->equipList[i]==-1){
                            equipArray->equipList[i]=posArray;
                            equipArray->inUse++;
                            break;
                            }
                        }
                }
                else printf("equipaggiamento pieno!\n");
                break;
            default:
                printf("comando non trovato!\n");
                break;
        }

}
int equipArray_getEquipByIndex(equipArray_t equipArray, int index){
    //nel vettore, alla posizione dell'iesimo elemento salvo la posizione nell'inventario
    return equipArray->equipList[index];
}