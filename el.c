#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "el.h"

void show_el(el_type e){
	printf("\nCarattere: %s \t Frequenza: %d\n",e.c,e.freq); // stampa a video di un el_type
}

boolean isless(el_type e1,el_type e2){ // controlla se e1 ha una frequenza minore o uguale a quella di e2
	return (e1.freq<=e2.freq);
}

boolean isequal(el_type e1,el_type e2){
	return (e1.freq==e2.freq);
}