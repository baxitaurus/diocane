#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* funzioni primitive: implementazione */
tree empty_tree(){
	return NULL;
}

boolean emptyt(tree t){
	return (t==NULL);
}

el_type root(tree t){
	if(emptyt(t))
		abort();
	return t->value;
}

tree left(tree t){
	if(emptyt(t))
		abort();
	return t->left;
}

tree right(tree t){
	if(emptyt(t))
		abort();
	return t->right;
}

tree cons_tree(el_type el,tree l,tree r){ // !!E' IN PROVA OCCHIO!!
	tree t=(tree)malloc(sizeof(NODO_TREE));
	t->value=el;
	t->left=l;
	t->right=r;
	return t;
}