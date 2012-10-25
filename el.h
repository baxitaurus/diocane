#include <stdio.h>

typedef int boolean; // per sottolineare quei casi in cui l'intero si comporterà come un booleano

typedef int binary; // per sottolineare quei casi in cui l'intero verrà usato con soltanto i valori 0 e 1 (bit)

/* definizione del tipo di dato che costituirà l'albero binario: rispetto a el_file_type prevede il campo bit */
typedef struct{
	char c[50];
	binary bit;
	int freq;
}el_type;


void show_el(el_type e); // stampa a video di un elemento di tipo el_type
boolean isless(el_type e1,el_type e2); // controlla se l'elemento e1 ha una frequenza inferiore a quella di e2
boolean isequal(el_type e1,el_type e2); // controlla se la frequenza dei due elementi è la stessa