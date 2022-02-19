#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "limits.h"
#include "graph.h" 
#include "math.h"
#define MAXC 10
typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;
static int powerset_r(int*dim,Edge **a,Graph G,Edge*val,int k,int *sol, int j, int pos, int start,int cnt);
//funzione che calcola powerset con sottoinsiemi di cardinalità crescente tramite iterazione di combinazioni semplici.
static int powerset_comb_s(int *dim,Edge **a,Graph G,Edge *val, int k, int *sol);
//funzione che calcola il peso di un insieme di archi.
static int calcolaPeso(Edge *a,int length);
static void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post);
static Edge  EDGEcreate(int v, int w, int wt);
static link  NEW(int v, int wt, link next);
static Graph reverse(Graph G, Graph R);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
//funzione dfs modificata che alla scoperta di archi B si interrompe, in quanto implicherebbe la presenza di un ciclo.
static int dfsR(Graph G,Edge e, int *pre, int *post,int*time,int *st,int*scc);
//funzione dfs modificata per applicare ordinamento topologico.
static void TsdfsR(Graph G, int v, int*ts,int *pre, int *time);
//funzione che data una sorgente, calcola i percorsi massimi da esso agli altri nodi.
static void longpath(Graph G,int s,int *dist);
//funzione che verifica se grafo è un DAG.
static int GRAPHcheckDAG(Graph G,int*scc,int id);
//funzione che enumera gli archi di ogni scc e li salva.
static void EDGEsccList(Graph G,Edge ** cycleEdge,int n_scc,int* n_edge_scc,int*scc,int *dim_vett_edge_scc);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static link NEW(int v, int wt, link next) {
  link x = malloc(sizeof *x);
  if (x == NULL)
    return NULL;
  x->v = v;
  x->wt = wt;
  x->next = next;
  return x;
}

Graph GRAPHinit(int V) {
  int v;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->z = NEW(-1, 0, NULL);
  if (G->z == NULL)
    return NULL;
  G->ladj = malloc(G->V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
  for (v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}
void GRAPHfree(Graph G) {
  int v;
  link t, next;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  STfree(G->tab);
  free(G->ladj);
  free(G->z);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);
  if (G == NULL)
    return NULL;

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt);
  }
  return G;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, E = 0;
  link t;
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next)
      a[E++] = EDGEcreate(v, t->v, t->wt);
}


int GRAPHgetNEdges(Graph G){
    return G->E;
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;
  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);

}
int GRAPHgetNVertex(Graph G){
    return G->V;
}
void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2, 0));
}


static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  G->ladj[v] = NEW(w, wt, G->ladj[v]);
  G->E++;
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  link x;
  if (G->ladj[v]->v == w) {
    G->ladj[v] = G->ladj[v]->next;
    G->E--;
  }
  else
    for (x = G->ladj[v]; x != G->z; x = x->next)
      if (x->next->v == w) {
        x->next = x->next->next;
        G->E--;
  }
}
static int powerset_comb_s(int *dim,Edge **a,Graph G,Edge *val, int k, int *sol){
    int cnt=0,j;
    for(j=1;j<=k;j++){
        cnt= powerset_r(dim,a,G,val,k,sol,j,0,0,cnt);
    }
    return cnt;
}

static int powerset_r(int *dim,Edge **a,Graph G,Edge*val,int k,int *sol, int j, int pos, int start,int cnt){
    int i;
    if(pos==j){
        dim[cnt]=j;
        a[cnt]=malloc(j*sizeof(Edge));
        for(i=0; i<j;i++){
            a[cnt][i]=val[sol[i]];
          }
        return cnt+1;
    }
    for(i=start;i<k;i++){
        sol[pos]=i;
        cnt= powerset_r(dim,a,G,val,k,sol,j,pos+1,i+1,cnt);
        }
    return cnt;
}
static int calcolaPeso(Edge *a,int length){
    int wt=0;
    for(int i=0;i<length;i++){
        wt+=a[i].wt;
    }
    return wt;
}
void GRAPHcopy(Graph G1,Graph G2){
    Edge *tmp=malloc(G1->E*sizeof(Edge));
    GRAPHedges(G1,tmp);
    G2->tab=STcopy(G1->tab);
    for(int i=0;i<G1->E;i++){
        insertE(G2,tmp[i]);
    }
}

void GRAPHcustomDfs(Graph G,int n_scc,Edge **cycleEdge){
    int time=0;
    int *st=malloc(G->V*sizeof(int));
    int *pre=malloc(G->V*sizeof(int));
    int *post=malloc(G->V*sizeof(int));
      for(int i=0;i<G->V;i++){
        pre[i]=-1;post[i]=-1;st[i]=-1;
    }

}
void EDGEprint(Graph G, Edge* vett,int dim){
  for(int j=0;j<dim;j++){
              printf("%s-->%s:%d\n",STsearchByIndex(G->tab,vett[j].v),STsearchByIndex(G->tab,vett[j].w),vett[j].wt);
          }
}
static void EDGEsccList(Graph G,Edge ** cycleEdge,int n_scc,int* n_edge_scc,int*scc,int *dim_vett_edge_scc){
  link t;
  for(int i=0;i<n_scc;i++){
      for(int j=0;j<G->V;j++){
        if (scc[j]==i){
          for(t=G->ladj[j];t!=G->z;t=t->next){
            if(t->v>=0 && scc[t->v]==i){
              
              if (dim_vett_edge_scc[i]<n_edge_scc[i]+1){
                realloc(cycleEdge[i],2*n_edge_scc[i]*sizeof(Edge));
                dim_vett_edge_scc[i]=2*n_edge_scc[i];
              }
              
              cycleEdge[i][n_edge_scc[i]++]=EDGEcreate(j,t->v,t->wt);
            }
          }
        }
      }
    }
}
Graph GRAPHedgesToDAG(Graph G,Edge *E){
    
    Graph Gcopy=GRAPHinit(G->V);
    GRAPHcopy(G,Gcopy);
    Graph DAG=GRAPHinit(G->V);
    GRAPHcopy(G,DAG);
    int *scc = malloc(G->V * sizeof(int));
    int n_scc=GRAPHscc(G,scc);
    Edge **cycleEdge=malloc(n_scc*sizeof(Edge*));
    //vettore che contiene la cardinalità di archi per ogni scc.
    int *n_edge_scc=calloc(n_scc,sizeof(int));
    int *dim_vett_edge_scc=malloc(n_scc*sizeof(int));
    for(int i=0;i<n_scc;i++){
      cycleEdge[i]=malloc(G->E*sizeof(Edge));
      dim_vett_edge_scc[i]=1;
    }
    EDGEsccList(G,cycleEdge,n_scc,n_edge_scc,scc,dim_vett_edge_scc);
//si ciclano le adiacenze dei vertici di ogni scc per "raccogliere" gli archi delle scc, 
//i quali sono gli unici che possono formare un ciclo in un grafo orientato.
    
    printf("Archi rimossi:\n");
    for(int k=0;k<n_scc;k++){
      int dim=pow(2,n_edge_scc[k]);
      int *sol=calloc((n_edge_scc[k]),sizeof(int));//vettore di indici archi che compongono/non compongono insieme soluzione.
      Edge **a=malloc(dim*sizeof(Edge*)); //vettore contenente tutte le soluzioni.
      int *dimVett=calloc(dim,sizeof(int));//dimensione di ogni insieme di archi
      int found=0;
      int indexMax=-1; //indice soluzione finale per quella scc
      int maxwt=0;

     // for(int i=0;i<dim;i++) a[i]=malloc(G->E*sizeof(Edge));
      int cnt=powerset_comb_s(dimVett,a,G,cycleEdge[k],n_edge_scc[k],sol);
      a=realloc(a,cnt*sizeof(*a));
      for(int i=0;i<cnt;i++){
          int wt=calcolaPeso(a[i],dimVett[i]);
          if(found==1 && dimVett[i]>dimVett[i-1])break;
          if(wt>maxwt){
          for(int j=0;j<dimVett[i];j++) removeE(Gcopy,a[i][j]);

          int flag=GRAPHcheckDAG(Gcopy,scc,k);
              if(flag==1){
                  found=1;
                  maxwt=wt;
                  indexMax=i;
                  GRAPHfree(DAG);
                  DAG=GRAPHinit(G->V);
                  GRAPHcopy(Gcopy,DAG);    
              }      
          for(int j=0;j<dimVett[i];j++) insertE(Gcopy,a[i][j]);        
          }
      }
      //ad ogni iterazione aggiorno intero grafo, in modo che alla fine del ciclo delle scc mi ritrovi un DAG.
     if(indexMax!=-1)
     EDGEprint(Gcopy,a[indexMax],dimVett[indexMax]);

     GRAPHfree(Gcopy);
    Gcopy=GRAPHinit(G->V);
    GRAPHcopy(DAG,Gcopy);
    free(sol);
    free(dimVett);
    for(int i=0;i<cnt;i++) free(a[i]);
    free(a);
  
    }
     return DAG;

}
static Graph reverse(Graph G, Graph R) {
  int v;
  link t;
  for (v=0; v < G->V; v++)
    for (t= G->ladj[v]; t != G->z; t = t->next)
      GRAPHinsertE(R, t->v, v,t->wt);
  return R;
}
static int dfsR(Graph G,Edge e, int *pre, int *post,int*time,int *st,int*scc){
    link t;
    int res=1;
    int v,w=e.w;
    Edge x;
    st[e.w]=e.v;
    pre[w]=(*time)++;
    for(t=G->ladj[w];t!=G->z && res!=0;t=t->next){
        if(scc[w]==scc[t->v]){
          if(pre[t->v]==-1 )
          res=dfsR(G,EDGEcreate(w,t->v,0),pre,post,time,st,scc);
          else{
              v=t->v;
              if(post[v]==-1) return 0;
          }
        }
    }
    post[e.w]=(*time)++;
return res;
}
static void TsdfsR(Graph G, int v, int*ts,int *pre, int *time){
    link t; pre[v]=0;
    for(t=G->ladj[v];t!=G->z;t=t->next){
        if (pre[t->v]==-1){
            TsdfsR(G,t->v,ts,pre,time);
        }
    }
    ts[(*time)++]=v;
}
static void longpath(Graph G,int s,int *dist){
    int time=0;
    int *pre=malloc(G->V*sizeof(int));
    int *ts=malloc(G->V*sizeof(int));
    Edge *e=malloc(G->E*sizeof(*e));
    Graph R=GRAPHinit(G->V);
    R=reverse(G,R);
    link t;
    for(int i=0;i<G->V;i++){pre[i]=-1;ts[i]=-1;dist[i]=-INT_MAX;}
    dist[s]=0;
    for(int i=0;i<G->V;i++)
    if(pre[i]==-1)TsdfsR(R,i,ts,pre,&time);
    //dopo l'ordinamento topologico, è sufficiente stilare una lista di archi,enumerando le adiacenze dei nodi cosi ordinati.
    int cnt=0;
    for(int i=0;i<G->V;i++){
      for(t=G->ladj[ts[i]];t!=NULL;t=t->next){
        if(t->v!=-1) e[cnt++]=EDGEcreate(ts[i],t->v,t->wt);
      }
    }
    for(int i=0;i<G->E;i++){
      int v=e[i].v,w=e[i].w,wt=e[i].wt;
      if(dist[w]<dist[v]+wt)
        dist[w]=dist[v]+wt;
    }
    GRAPHfree(R);
    //sulla lista di archi appena stilata, è sufficiente applicare la funzione di relaxation opportunamente modificata.
}
void DAGPrintdist(Graph G,int *dist,int v){
  printf("distanza massima di ogni vertice da %s:\n",STsearchByIndex(G->tab,v));
  for(int i=0;i<G->V;i++){
    if(i!=v) printf("\tdistanza massima di %s da %s: %d\n",STsearchByIndex(G->tab,i),STsearchByIndex(G->tab,v),dist[i]);
  }
}
void  DAGlongestpath(Graph G){
    link t;
    //riconosci nodi sorgente ciclando adiancenze ed incrementando contatore incidenze se trovi quel nodo. dopodiche metti in un vettore sono i vertici che rimangono a zero.
    //crea vettore di archi delle adiacenze dei vertici sorgente
    //applica relaxation sugli archi.
    int *in_degree=calloc(G->V,sizeof(int));
    int *source_vertex=malloc(G->V*sizeof(int));
    int time=0;
    //calcolo in_degree di tutti i vertici:
    for(int i=0;i<G->V;i++){
        for(t=G->ladj[i];t!=G->z;t=t->next){
            in_degree[t->v]++;
        }
    }
    int *dist=malloc(G->V*sizeof(int));
    //per ogni nodo sorgente, eseguo l'algoritmo di cammino massimo per i DAG
    for(int i=0;i<G->V;i++){
        if(in_degree[i]==0) {
            longpath(G,i,dist);
            DAGPrintdist(G,dist,i); 
            }
    }

}
int GRAPHcheckDAG(Graph G,int *scc,int id){
    int time=0;
    int *st=malloc(G->V*sizeof(int));
    int *pre=malloc(G->V*sizeof(int));
    int *post=malloc(G->V*sizeof(int));
    for(int i=0;i<G->V;i++){
        pre[i]=-1;post[i]=-1;st[i]=-1;
    }
    for(int i=0;i<G->V;i++){
      if(pre[i]==-1 && scc[i]==id){
      int flag=dfsR(G,EDGEcreate(i,i,1),pre,post,&time,st,scc);
      if(flag==0)return 0;
      }
    }
    
    for(int i=0;i<G->V;i++){
        //se almeno un elemento non è stato raggiunto dalla dfs, significa che è sconnesso.
        if(pre[i]==-1 && scc[i]==id) return 0;
    }
    return 1;
}
//algoritmo: faccio powerset sul vettore di archi che compongono il grafo.
//creo grafo temporaneo a partire da questa lista di archi. 
//applichi algoritmo mix tra componenti connesse e dfs ( per riconoscere archi B).
//se non trovo archi B e ho una sola componente connessa, ho trovato un DAG




static void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post) {
  link t;
  scc[w] = time1;
  for (t = G->ladj[w]; t != G->z; t = t->next)
    if (scc[t->v] == -1)
      SCCdfsR(G, t->v, scc, time0, time1, post);
  post[(*time0)++]= w;
}

int GRAPHscc(Graph G,int*sccG) {
  int v, time0 = 0, time1 = 0, *sccR, *postG, *postR;
  Graph R;

  R = GRAPHinit(G->V);
  reverse(G, R);

  sccR = malloc(G->V * sizeof(int));
  postG = malloc(G->V * sizeof(int));
  postR = malloc(G->V * sizeof(int));

  for (v=0; v < G->V; v++) {
    sccG[v] = -1;
    sccR[v] = -1;
    postG[v] = -1;
    postR[v] = -1;
  }

  for (v=0; v < G->V; v++)
    if (sccR[v] == -1)
      SCCdfsR(R, v, sccR, &time0, time1, postR);

  time0 = 0;
  time1 = 0;

  for (v = G->V-1; v >= 0; v--)
    if (sccG[postR[v]]==-1){
      SCCdfsR(G,postR[v], sccG, &time0, time1, postG);
      time1++;
    }
  printf("componenti fortemente connesse:\n");
  for (v = 0; v < G->V; v++)
    printf("node %s in scc %d \n", STsearchByIndex(G->tab, v), sccG[v]);
  GRAPHfree(R);
  return time1;
 }