#ifndef GRAPH_H
#define GRAPH_H

#include "ST.h"
#include "stdio.h"
typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
int   GRAPHgetIndex(Graph G, char *label);
int GRAPHgetNEdges(Graph G);
int GRAPHgetNVertex(Graph G);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
Graph GRAPHedgesToDAG(Graph G,Edge *E);
void GRAPHcopy(Graph G1,Graph G2);
void  GRAPHspD(Graph G, int id);
void  GRAPHspBF(Graph G, int id);
void  DAGlongestpath(Graph G);
int GRAPHscc(Graph G,int*sccG);
Graph GRAPHedgestoDAG(Graph G,Edge *E);
#endif