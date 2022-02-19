#include "graph.h"
#include "stdlib.h"
#include "stdio.h"
#define file "grafo3.txt"
int main(){
    FILE *fin;
    fin=fopen(file,"r");
    FILE*fout=fopen("out.txt","w");
    Graph G=GRAPHload(fin);
    Graph Dag;
    int EdgeNum=GRAPHgetNEdges(G);
    Edge *E=malloc(EdgeNum*sizeof(Edge));
    GRAPHedges(G,E);
    Dag=GRAPHedgesToDAG(G,E);
    DAGlongestpath(Dag);
    GRAPHstore(Dag,fout);
    fclose(fout);
    return 0;
}