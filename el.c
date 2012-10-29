#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "el.h"

void show_el(el_type e){
	printf("\nCarattere: %c \t Frequenza: %d\n",e.carattere,e.freq); // stampa a video di un el_type
}

boolean isless(el_type e1,el_type e2){ // controlla se e1 ha una frequenza minore o uguale a quella di e2
	return (e1.freq<=e2.freq);
}

boolean isequal(el_type e1,el_type e2){
	return (e1.freq==e2.freq);
}

el_type converti(info_carattere el){
	el_type converted;
	converted.carattere=el.carattere;
	converted.freq=el.presenze;
	return converted;
}

void show_bit(el_type e){
	printf("%d",e.bit);
}
