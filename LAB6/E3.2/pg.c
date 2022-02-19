#include "pg.h"
int pg_empty(pg_t *pg){
    return !strcmp(pg->cod,NULL);
}
int pg_read(FILE *fp, pg_t *pgp){ //1 se letto corr, 0 se fallito
    int check=fscanf(fp,"%s %s %s",pgp->cod,pgp->nome,pgp->classe);
    pgp->equip=equipArray_init();
    if(check==3){// è stato letto un personaggio
        stat_read(fp,&(pgp->b_stat));
        return 1;
    }
    else return 0;


}
void pg_updateEquip(pg_t *pgp, invArray_t invArray){
    equipArray_update(pgp->equip,invArray);
}

void pg_print_stat(FILE*fp,pg_t *pgp, invArray_t invArray){
    stat_t pg_stat=pgp->b_stat;
    for(int i=0;i<EQUIP_SLOT&&i<equipArray_inUse(pgp->equip);i++){
        int pos=equipArray_getEquipByIndex(pgp->equip,i);
        inv_t *tmp_inv_obj=invArray_getByIndex(invArray,pos);
        pg_stat=calc_stat(pg_stat,tmp_inv_obj->stat);
    }
    stat_print(fp,&pg_stat,MIN_STAT);
}

void pg_print(FILE *fp, pg_t *pgp, invArray_t invArray){
    fprintf(fp,"%s %s %s ",pgp->cod,pgp->nome,pgp->classe);
    pg_print_stat(fp,pgp,invArray);
    return;
}
