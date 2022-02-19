#include "queue.h"

int main(){
    QUEUE q= QUEUEinit(4);
    int s=QUEUEempty(q);
    //QUEUEput(q,1);
    QUEUEget(q);
    //QUEUEput(q,2);
    QUEUEget(q);
    //QUEUEput(q,3);
    QUEUEget(q);
    //QUEUEput(q,4);
    QUEUEget(q);
    //QUEUEput(q,5);
    QUEUEget(q);
    //QUEUEput(q,5);
    QUEUEget(q);
   /*
    QUEUEput(q,3);
    QUEUEput(q,4);
    QUEUEput(q,5);
    
    QUEUEput(q,6);
    QUEUEput(q,7); //nota: aggiungendo troppi elementi, ricomincia da capo a scrivere(solo per vettore)
  //  QUEUEput(q,6);

  */    
    s=QUEUEempty(q);
     Item f=QUEUEget(q);
     f=QUEUEget(q);
    s=QUEUEempty(q);
    return 0;
}