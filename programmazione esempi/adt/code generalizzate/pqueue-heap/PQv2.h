//in questa versione,anzichè salvare gli item, salvo posizione in vettore di Item
#ifndef PQV2_HEADER
#define PQV2_HEADER

typedef struct pqueue *PQ;
PQ PQinit(int maxN);
void PQfree(PQ pq);
int PQempty(PQ pq);
void PQinsert(PQ pq,int index,int prio);
int PQextractMax(PQ pq);
int PQshowMax(PQ pq);
void PQdisplay(PQ pq);
int PQsize(PQ pq);
void PQchange(PQ pq,int index,int prio);
#endif