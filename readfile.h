#define	READFILE_H
#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _STDLIB_H
#include <stdlib.h>
#endif
#ifndef	_MATH_H
#include <math.h>
#endif

typedef struct {
    unsigned int carattere;
    int presenze;
} info_carattere;

typedef struct item {
    info_carattere value;
    struct item* next;
} nodo;

typedef nodo* list;



list scroll_txt_file(char *file, list l);
list cons( list l, unsigned int x, int *overflow);
int member( list l, unsigned int x);
int add_presenza( list l, unsigned int x, int **overflow);
void show_list(list l);
list ordina_lista( list l);
list tail( list l );
info_carattere head( list l );
list delete( info_carattere c, list l);
list cons_el( info_carattere m,  list lista_ordinata);
info_carattere cerca_maggiore(list l);
list insOrd( list l, info_carattere e);
int length_list(list l); // aggiunta da baxitaurus
float calcolo_entropia(list l);