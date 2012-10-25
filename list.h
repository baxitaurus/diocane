#include <stdio.h>
#include <stdlib.h>
#include "el.h"

/*Definizione del tipo lista*/
typedef struct list_element{
	el_type value;
	struct list_element *next;
}NODO;

typedef NODO *list;

/* funzioni primitive */
boolean empty(list l);
list empty_list();
list cons_tail(list l,el_type e);

/* funzioni secondarie */
void stampa_lista(list l);
int length_list(list l);
list ordins_list_freq(list l,el_type el);
list unisci_el(list l);