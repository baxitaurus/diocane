#ifndef MENU_H
#include "menu.h"
#endif
void menu_start(){
    printf("Programma di compressione e decompressione testo\n");
    printf("UniFe Andrea bassi & Luigi Scagnet\n\n");
}

void menu(int *scelta){
    printf("Scegli una opzione per:\n");
    printf("1 - Crea file statistiche presenze caratteri\n");
    printf("2 - Comprimi usando algoritmo Huffman statico\n");
    printf("3 - Comprimi usando algoritmo LZW\n");
    printf("4 - Decomprimi usando algoritmo Huffman statico\n");
    printf("5 - Decomprimi usando algoritmo LZW\n");   
    printf("6 - Uscita dal programma\n");
    scanf("%d", scelta);
} 
