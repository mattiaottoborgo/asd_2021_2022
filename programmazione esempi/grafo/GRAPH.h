#ifndef GRAPH_HEADER
#define GRAPH_HEADER

#define WEIGTHED 0
#define NOT_WEIGHTED 1
#define ORIENTED 1
#define NOT_ORIENTED 1
#include "stdlib.h"
#include "stdio.h"
typedef struct graph *Graph;
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);
void GRAPHload(FILE *fin);
void GRAPHstore(GRAPH G, FILE *fout);
int GRAPHgetIndex(Graph G, char *label); //ritorna indice dato nome
void GRAPHinsertE(Graph G, int id1, int id2);
void GRAPHremoveE(Graph G, int id1, int id2);
void GRAPHedges( Graph G, Edge *a);
int GRAPHpath(Graph G, int id1, int id2);
void GRAPHbfs(Graph G, int id);
void GRAPHdfs(Graph G, int id);
#if NOT_WEIGHTED
typedef struct edge{int v;int w;} Edge;
#endif

#if WEIGTHED
typedef struct edge{int v;int w;int wt;} Edge;
#endif

#if NOT_ORIENTED
void GRAPHpathH(Graph G, int id1, int id2);
int GRAPHcc(Graph G);
#endif
#if ORIENTED
int GRAPHscc(Graph G);
#endif
#endif 