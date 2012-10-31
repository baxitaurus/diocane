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

tree new_constree(int sum,tree l,tree r){
	tree t=(tree)malloc(sizeof(NODO_TREE));
	t->value.freq=sum;
	t->left=l;
	t->right=r;
	/* ASSEGNO A SINISTRA IL BIT 0 E A DESTRA IL BIT 1 */
	l->value.bit=0;
	r->value.bit=1;
	return t;
}

void inorder(tree t){
	if(!emptyt(t)){
		inorder(t->left);
			if(t->left==NULL && t->right==NULL)
				show_el(t->value);
		inorder(t->right);
	}
}

boolean member_tree(unsigned int el,tree t){
	if(emptyt(t))
		return 0;
	else{
		if(t->value.carattere==el)
			return 1;
		return (member_tree(el,t->left) || member_tree(el,t->right));
	}
}