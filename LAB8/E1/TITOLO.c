#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "TITOLO.h"
#include "QUOTA.h"
typedef struct BSTnode *link_b;
struct BSTnode{Quota quota;link_b l;link_b r;int N;link_b p;};
struct bst{ link_b root;link_b z;};
struct titolo{
    BST bst;
    char nome[MAXC];
};

static link_b insertR(link_b h, Quota x, link_b z);
static link_b NEW(Quota quota, link_b l, link_b r,int N,link_b p);
static int FindAndUpdateR(link_b h, Data k, link_b z,int valore,int n_scambi);
//funzione che cerca quotazione di un titolo ad una determinata data
static Quota searchR(link_b h, Data k, link_b z);
TITOLO TITOLOinit(char nome[MAXC],int n_transazioni){
    TITOLO titolo=malloc(sizeof(*titolo));
    titolo->bst=BSTinit();
    strcpy(titolo->nome,nome);
    return titolo;

}
int TITOLOcheckNull(TITOLO titolo){
    return !(strcmp(titolo->nome,"\0"));
}
TITOLO TITOLOnull(){
    TITOLO tmp=malloc(sizeof(*tmp));
    strcpy(tmp->nome,"\0");
    tmp->bst=BSTinit();
    return tmp;
}
BST BSTinit() {
    BST bst = malloc(sizeof *bst) ;
    bst->root= ( bst->z = NEW(QUOTANull(), NULL, NULL,0,NULL));
    return bst;
}
void BST_insert(BST bst,Quota x){
    bst->root=insertR(bst->root,x,bst->z);
}
static link_b NEW(Quota quota, link_b l, link_b r,int N,link_b p) {
    link_b x = malloc(sizeof *x);
    x->quota = quota; x->l = l; x->r = r;x->N=N;x->p=p;
    return x;
}
static link_b insertR(link_b h, Quota x, link_b z) {
    if (h == z) return NEW(x, z, z,1,z);
    if(DATAcompare(x.data,h->quota.data)==-1){
        h->l = insertR(h->l, x, z);h->l->p=h;
        }
    else{
        h->r = insertR(h->r, x, z);h->r->p=h;
        }
    (h->N++);
    return h;
}

static int FindAndUpdateR(link_b h, Data k, link_b z,int valore,int n_scambi) {
    int cmp;
    if (h == z){
        return 0;
    }
    cmp = DATAcompare(k, h->quota.data);
    if (cmp == 0) {
       QUOTAupdate(&(h->quota),valore,n_scambi);
        return 1;
    }
    if (cmp == -1) return FindAndUpdateR(h->l, k, z,valore,n_scambi);
    return FindAndUpdateR(h->r, k, z,valore,n_scambi);
}
void TITOLOupdateQuote(TITOLO titolo, Data k,int valore,int n_scambi) {
    
    int flag=FindAndUpdateR(titolo->bst->root, k, titolo->bst->z,valore,n_scambi);
    if(flag==0){
        titolo->bst->root=insertR(titolo->bst->root,QUOTAcreate(k,valore,n_scambi),titolo->bst->z);
    }
}
char* TITOLOgetname(TITOLO titolo){
    return titolo->nome;
}
Quota TITOLOgetQuota(TITOLO titolo,Data data){
    return searchR(titolo->bst->root,data,titolo->bst->z);
}

static Quota searchMinIntervall(link_b h, Data i, Data f, link_b z){
    Quota Min;
    if(h==z) return QUOTAcreate(DATAnull(),INT_MAX,1);
    Quota q1= searchMinIntervall(h->l,i,f,z);
    Quota q2= QUOTAcreate(DATAnull(),INT_MAX,1);
    //controllo se nodo corrente
    if(DATAcompare(h->quota.data,i)>=0 && DATAcompare(h->quota.data,f)<=0 )q2= h->quota;
    if(QUOTAcmp(q1,q2)==-1) Min=q1;
    else Min=q2;
    Quota q3= searchMinIntervall(h->r,i,f,z);
    if(QUOTAcmp(q3,Min)==-1) Min=q3;
    return Min;
}
static Quota searchMaxIntervall(link_b h, Data i, Data f, link_b z){
    Quota Max;
    if(h==z) return QUOTAcreate(DATAnull(),INT_MIN,1);
    Quota q1= searchMaxIntervall(h->l,i,f,z);
    Quota q2= QUOTAcreate(DATAnull(),INT_MIN,1);
    //controllo se nodo corrente
    if(DATAcompare(h->quota.data,i)>=0 && DATAcompare(h->quota.data,f)<=0 )q2= h->quota;
    if(QUOTAcmp(q1,q2)==1) Max=q1;
    else Max=q2;
    Quota q3= searchMaxIntervall(h->r,i,f,z);
    if(QUOTAcmp(q3,Max)==1) Max=q3;
    return Max;
}


static Quota searchR(link_b h, Data k, link_b z) {
    int cmp;
    if (h == z){
        return QUOTANull();
    }
    cmp = DATAcompare(k, h->quota.data);
    if (cmp == 0) {
       
        return h->quota;
    }
    if (cmp == -1) return searchR(h->l, k, z);
    return searchR(h->r, k, z);
}

Quota TITOLOgetIntervallminQUOTA(TITOLO titolo,Data data_i,Data data_f){
    return searchMinIntervall(titolo->bst->root,data_i,data_f,titolo->bst->z);
}
Quota TITOLOgetIntervallmaxQUOTA(TITOLO titolo,Data data_i,Data data_f){
    return searchMaxIntervall(titolo->bst->root,data_i,data_f,titolo->bst->z);
}


static Quota searchMin(link_b h, link_b z){
    Quota Min;
    if(h==z) return QUOTAcreate(DATAnull(),INT_MAX,1);
    Quota q1= searchMin(h->l,z);
    Quota q2= h->quota;
    if(QUOTAcmp(q1,q2)==-1) Min=q1;
    else Min=q2;
    Quota q3= searchMin(h->r,z);
    if(QUOTAcmp(q3,Min)==-1) Min=q3;
    return Min;
}
static Quota searchMax(link_b h,link_b z){
    Quota Max;
    if(h==z) return QUOTAcreate(DATAnull(),INT_MIN,1);
    Quota q1= searchMax(h->l,z);
    Quota q2= h->quota;
    if(QUOTAcmp(q1,q2)==1) Max=q1;
    else Max=q2;
    Quota q3= searchMax(h->r,z);
    if(QUOTAcmp(q3,Max)==1) Max=q3;
    return Max;
}
static int TITOLOgetminPath(link_b root){
    int u,v;
    if(root==NULL) return -1;
    u=TITOLOgetminPath(root->l);v=TITOLOgetminPath(root->r);
    if(u<v) return u+1;
    return v+1;
}
static int TITOLOgetmaxPath(link_b root){
    int u,v;
    if(root==NULL) return -1;
    u=TITOLOgetmaxPath(root->l);v=TITOLOgetmaxPath(root->r);
    if(u>v) return u+1;
    return v+1;
}
Quota TITOLOgetminQUOTA(TITOLO titolo){
    return searchMin(titolo->bst->root,titolo->bst->z);
}
Quota TITOLOgetmaxQUOTA(TITOLO titolo){
    return searchMax(titolo->bst->root,titolo->bst->z);
}

link_b rotR(link_b h) {
    link_b x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}
link_b rotL(link_b h) {
    link_b x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}
link_b partR(link_b h, int r){
    int t = h->l->N;
    if (t > r){
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r){
        h->r = partR(h->r,r -t -1);
        h = rotL(h);
    }
    return h;
}
static link_b balanceR(link_b h, link_b z) {
int r;
if (h == z)
return z;
r = (h->N+1)/2-1;
h = partR(h, r);
h->l = balanceR(h->l, z);
h->r = balanceR(h->r, z);
return h;
}
void BSTbalance(BST bst) {
bst->root = balanceR(bst->root, bst->z);
}

void TITOLObalance(TITOLO titolo,float S){
    int Min=TITOLOgetminPath(titolo->bst->root);
    int Max=TITOLOgetmaxPath(titolo->bst->root);
    if(((float)Max/(float)Min)>S)
        BSTbalance(titolo->bst);
    return;
}

