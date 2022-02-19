#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "TITOLO.h"



//parte quote
typedef struct {Data data;Orario orario;int n_scambi;int valore}transazione;
typedef struct BSTnode *link;
struct BSTnode{Quota quota;link l;link r;};
struct binarysearchtree{link root;link z;Data data};
struct titolo{
    char nome[MAXC];
    BST lista_quote_giornaliere;
    transazione *lista_transazioni;
    int numero_transazioni;
};
TITOLO initTitolo();

BST initListaQuoteGG();
static link NEWbstnode(Quota quota, link l, link r);

transazione *initListaTransazioni(int numero_transazioni){
    transazione* l_t=malloc(numero_transazioni*sizeof(transazione));
    return l_t;
}


static link NEWbstnode(Quota quota, link l, link r){
    link x=malloc(sizeof(*x));
    x->quota=quota;
    x->l=l; x->r=r;
    return x;
}



//bst contenente "lista" quote giornaliere
BST initListaQuoteGG(){
    BST coll_quote=malloc(sizeof(*coll_quote));
    coll_quote->root=(coll_quote->z=NEWbstNode(QUOTAnull(),NULL,NULL));
    coll_quote->data=DATAnull();
    return coll_quote;
}


TITOLO initTitolo(char* nome,int numero_transazioni){
    TITOLO titolo=malloc(sizeof(*titolo));
    strcpy(titolo->nome,nome);
    titolo->lista_quote_giornaliere=initListaQuoteGG();
    titolo->lista_transazioni=initListaTransazioni(numero_transazioni);
    titolo->numero_transazioni=numero_transazioni;
    return titolo;

}

void leggiTransazioni(FILE *fp,TITOLO titolo,int numero_transazioni){
    for(int i=0;i<numero_transazioni;i++){
        transazione tmp;
        int tmp_valore;
        int tmp_n_scambi;
        Data tmp_data=leggiData(fp);
        Orario tmp_orario=leggiOrario(fp);
        fscanf("%d %d",&tmp_valore,&tmp_n_scambi);
        
    }
}
//funzione che entra in bst e aggiunge nuova data oppure modifica quota di quella data
void aggiornaQuota(TITOLO titolo,int valore,int n_scambi,link h,Data key, link z){
    int cmp;
    if(h==z){
        //non l'ho trovato aggiungi come foglia
    }
    cmp=DATAcompare(key,h->quota.data);
    if(cmp==0){
        //ho trovato l'item, posso modificarlo
    }
    if(cmp==-1){
        aggiornaQuota(titolo,valore,n_scambi,h->l,key,z);
    }
    aggiornaQuota(titolo,valore,n_scambi,h->r,key,z);

}

