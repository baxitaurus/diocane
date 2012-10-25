#include "list.h"
#include <stdio.h>
#include <stdlib.h>

boolean empty(list l){ // funzione che controlla se la lista che riceve è vuota
	return (l==NULL);
}

list empty_list(){ // restituisce una lista vuota
	return NULL;
}

list cons_tail(list l,el_type e){ // funzione di inserimento in coda della lista ricevuta
	list aux=l;
	if(empty(l)){
		aux=(list)malloc(sizeof(NODO));
		l=aux;
	}
	else{
		while(!empty(aux->next))
			aux=aux->next;
		aux->next=(list)malloc(sizeof(NODO));
		aux=aux->next;
	}
	aux->value=e;
	aux->next=NULL;
	return l;
}

void stampa_lista(list l){ // stampa a video della lista passata
	list aux=l;
	while(!empty(aux)){
		show_el(aux->value);
		aux=aux->next;
	}
}

int length_list(list l){ // calcola e restituisce la lunghezza della lista ricevuta
	list aux=l;
	int dim=0;
	while(!empty(aux)){
		dim++;
		aux=aux->next;
	}
	return dim;
}

list ordins_list_freq(list l,el_type el){ // inserimento in lista ordinato in modo crescente sul campo frequenza
	list aux,prec,current;
	int trovato=0;
	aux=(list)malloc(sizeof(NODO));
	aux->value=el;
	aux->next=NULL;
	if(empty(l))
		l=aux;
	else{
		current=l;
		while(!empty(current) && !trovato){
			if(isless(current->value,el)){
				prec=current;
				current=current->next;
			}
			else
				trovato=1;
		}
		if(empty(current))
			prec->next=aux; // inserimento in fondo alla lista (non ho trovato elementi con frequenza maggiore di quella di el)
		else{
			if(current==l){
				aux->next=l; // ho trovato che il primo elemento ha una frequenza più grande di quella di el (ins. in testa)
				l=aux;
			}
			else{ // ho trovato un elemento che ha una frequenza più grande di quella di el in una qualche posizione interna alla lista
				prec->next=aux;
				aux->next=current;
			}
		}
	}
	return l;
}