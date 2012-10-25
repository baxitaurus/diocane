#include "list.h"
#include <stdio.h>
#include <stdlib.h>

/* definizione del tipo albero (tree) */
typedef struct tree_element{
	el_type value;
	struct tree_element *left, *right;
}NODO_TREE;

typedef NODO_TREE *tree;

/* funzioni primitive */
tree empty_tree();
boolean emptyt(tree t);
el_type root(tree t);
tree left(tree t);
tree right(tree t);
tree cons_tree(el_type el,tree l,tree r); // !E' IN PROVA OCCHIO!
