//implementazione con vettore


typedef struct stack *STACK;
typedef struct{
    int value;
    int code;
}Item;

STACK STACKinit(int maxN);
int STACKempty(STACK sp);
void STACKpush(STACK sp, Item val);
Item STACKpop(STACK sp);