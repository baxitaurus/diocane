#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

typedef struct list_new{
	tree value;
	struct list_new *next;
}new_item;

typedef new_item *new_list;

/* funzioni di gestione */
new_list new_constail(tree node,new_list l);
void new_show(new_list l);
void new_showel(tree el);
int somma_frequenze(tree t1,tree t2);
new_list delete_2(new_list l);
boolean new_isless(tree e1,tree e2);
new_list new_ordins(new_list l,tree el);