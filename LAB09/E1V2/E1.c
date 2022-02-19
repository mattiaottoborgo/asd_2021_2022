#include "graph.h"
#include "stdlib.h"
#include "stdio.h"
#define file "grafo4.txt"
int main(){
    FILE *fin;
    fin=fopen(file,"r");
    Graph G=GRAPHload(fin);
    Graph Dag;
    int EdgeNum=GRAPHgetNEdges(G);
    Edge *E=malloc(EdgeNum*sizeof(Edge));
    GRAPHedges(G,E);
    Dag=GRAPHedgesToDAG(G,E);
    DAGlongestpath(Dag);
    return 0;
}