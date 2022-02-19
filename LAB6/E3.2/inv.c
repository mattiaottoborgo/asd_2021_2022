#include"inv.h"
#include "limits.h"
void inv_read(FILE *fp, inv_t *invp){
    fscanf(fp,"%s %s",invp->nome,invp->tipo);
    stat_read(fp,&invp->stat);
}
void inv_print(FILE *fp, inv_t *invp){
    fprintf(fp,"%s %s",invp->nome,invp->tipo);
    stat_print(fp,&invp->stat,MIN_STAT);
}

void stat_read(FILE *fp, stat_t *statp){

    fscanf(fp,"%d %d %d %d %d %d",&statp->hp, &statp->mp, &statp->atk, &statp->def, &statp->mag, &statp->spr);
}
void stat_print(FILE *fp, stat_t *statp, int soglia){
     fprintf(fp,"%d %d %d %d %d %d\n",statp->hp,statp->mp,statp->atk,statp->def,statp->mag,statp->spr);
}

stat_t inv_getStat(inv_t *invp){
    return invp->stat;
}
inv_t* void_inv(){
    inv_t* tmp=malloc(sizeof(*tmp));
    strcpy(tmp->nome,"\0");
    strcpy(tmp->tipo,"\0");
    tmp->stat=void_stat();
    return tmp;
}
stat_t void_stat(){
    stat_t tmp;
    tmp.hp=INT_MAX;
    tmp.mp=INT_MAX;
    tmp.atk=INT_MAX;
    tmp.def=INT_MAX;
    tmp.mag=INT_MAX;
    tmp.spr=INT_MAX;
    return tmp;

}

stat_t calc_stat(stat_t s1,stat_t s2){
    stat_t tmp;
    tmp.hp=s1.hp+s2.hp;
    tmp.mp=s1.mp+s2.mp;
    tmp.atk=s1.atk+s2.atk;
    tmp.def=s1.def+s2.def;
    tmp.mag=s1.mag+s2.mag;
    tmp.spr=s1.spr+s2.spr;
    if(tmp.hp<1)tmp.hp=1;
    if(tmp.mp<1)tmp.mp=1;
    if(tmp.atk<1)tmp.atk=1;
    if(tmp.def<1)tmp.def=1;
    if(tmp.mag<1)tmp.mag=1;
    if(tmp.spr<1)tmp.spr=1;
    return tmp;
}