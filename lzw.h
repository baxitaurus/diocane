#define	LZW_H
#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _STDLIB_H
#include <stdlib.h>
#endif
#define TABLE_SIZE 15

typedef struct item_diz {
    unsigned int char_code[TABLE_SIZE];
    unsigned short int new_code;
    struct item_diz* next;
} nodo_diz;

typedef nodo_diz* diz_lzw;

diz_lzw init();
diz_lzw initAscii();
diz_lzw cons_tail(diz_lzw l, unsigned int *e);
void lzw_compression();
int trova ( diz_lzw l, unsigned int *str);
int confronta(unsigned int *a, unsigned int *b);
void reset_array( unsigned int *array);
void copia_array(unsigned int *a, unsigned int *b);
void lzw_decompression();
int find_code( diz_lzw l, unsigned int code, unsigned int strCorr[] );
void stampa( unsigned int *str );
void concatena(unsigned int *a, unsigned int *b, unsigned int *risultato);
void write_file( unsigned int *str, FILE *fo );