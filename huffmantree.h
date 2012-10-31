#include "list_new.h"
#include <stdio.h>

new_list crea_lista_foglie(list l,int totcar);
tree crea_huffmantree(new_list l,tree t,int dim_l);
void stampa_codifica(unsigned int el,tree t,FILE *fc);
void stampa_decodifica(tree t,FILE* fp);