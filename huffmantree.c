#include "huffmantree.h"
#include <stdio.h>
#include <stdlib.h>

new_list crea_lista_foglie(list l,int totcar){
	new_list newl=NULL;
	el_type buf;
	int i;
	tree foglia[50];
	// inizializzo le foglie
	for(i=0;i<totcar;i++){
		buf=converti(l->value);
		foglia[i]=(tree)malloc(sizeof(NODO_TREE));
		foglia[i]->value=buf;
		foglia[i]->right=NULL;
		foglia[i]->left=NULL;
		newl=new_constail(foglia[i],newl);
		l=l->next;
	}
	return newl;
}

tree crea_huffmantree(new_list l,tree t,int dim_l){
	new_list current;
	new_list succ;
	new_item node;
	int sumfreq;
	while(dim_l!=1 && dim_l!=0){
		current=l;
		succ=current->next;
		sumfreq=somma_frequenze(current->value,succ->value);
		t=new_constree(sumfreq,l->value,succ->value);
		node.value=t;
		node.next=NULL;
		l=delete_2(l);
		l=new_ordins(l,node.value);
		dim_l--;
	}
	t->value.bit=0;
	return t;
}