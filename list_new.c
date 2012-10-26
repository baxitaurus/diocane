#include "list_new.h"
#include <stdlib.h>
#include <stdio.h>

new_list new_constail(tree node,new_list l){
	new_list aux,prec;
	new_list root=l;
	aux=(new_list)malloc(sizeof(new_item));
	aux->value=node;
	aux->next=NULL;
	if(l==NULL)
		return aux;
	else{
		while(l!=NULL){
			prec=l;
			l=l->next;
		}
		prec->next=aux;
		return root;
	}
}

void new_show(new_list l){
	if(l==NULL){
		printf("\n\tErrore Lista Foglie Vuota!\n");
		abort();
	}
	while(l!=NULL){
		new_showel(l->value);
		l=l->next;
	}
}

void new_showel(tree el){
	show_el(el->value);
}

int somma_frequenze(tree t1,tree t2){
	int a=t1->value.freq;
	int b=t2->value.freq;
	return (a+b);
}

new_list delete_2(new_list l){
	int i;
	new_list aux;
	for(i=0;i<2;i++){
		aux=l;
		l=l->next;
		free(aux);
	}
	return l;
}

boolean new_isless(tree e1,tree e2){
	int f1,f2;
	f1=e1->value.freq;
	f2=e2->value.freq;
	return (f1<=f2);
}

new_list new_ordins(new_list l,tree el){
	new_list aux,prec,current;
	int trovato=0;
	aux=(new_list)malloc(sizeof(new_item));
	aux->value=el;
	aux->next=NULL;
	if(l==NULL) // primo inserimento
		l=aux;
	else{
		current=l;
		while(current!=NULL && !trovato){
			if(new_isless(current->value,el)){
				prec=current;
				current=current->next;
			}
			else
				trovato=1;
		}
		if(current==NULL)// inserimento in coda
			prec->next=aux;
		else{
			if(current==l){ // inserimento in testa
				aux->next=l;
				l=aux;
			}
			else{
				prec->next=aux;
				aux->next=current;
			}
		}
	}
	return l;
}



		

	