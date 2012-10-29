#include "huffmantree.h"
#include <stdio.h>
#include <stdlib.h>

new_list crea_lista_foglie(list l,int totcar){
	new_list newl=NULL;
	el_type buf;
	int i;
	tree foglia[70];
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
	return t;
}

void stampa_codifica(unsigned int el,tree t,FILE *fc){
	tree sx,dx;
	sx=t->left;
	dx=t->right;
	if(emptyt(t)){
		fclose(fc);
		return ;
	}
	else{
		if(member_tree(el,sx)){
			fprintf(fc,"%d ",sx->value.bit);
			show_bit(sx->value);
			stampa_codifica(el,t->left,fc);
		}
		else if(member_tree(el,dx)){
			fprintf(fc,"%d ",dx->value.bit);
			show_bit(dx->value);
			stampa_codifica(el,t->right,fc);
		}
	}
}

void stampa_decodifica(tree t,FILE *fp){
	int bit;
	tree aux;
	printf("\n\n\nDecodifica del testo:\n");
	printf("\n\n\n");
	while(!feof(fp)){
		aux=t;
		while(!emptyt(aux->left) && !emptyt(aux->right)){
			fscanf(fp,"%d",&bit);
			if(bit==1)
				aux=aux->right;
			if(bit==0)
				aux=aux->left;
		}
	printf("%c",aux->value.carattere);
	}
	printf("\n\n\n\t\t\t\t***FINE***\n");
}