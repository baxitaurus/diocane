#define	LZW_H
#ifndef _STDIO_H
#include <stdio.h>
#endif
#ifndef _STDLIB_H
#include <stdlib.h>
#endif
#ifndef	_STRING_H
#include <string.h>
#endif

#define TABLE_SIZE 15

#define ByteSwap16(n) \
    ( ((((unsigned int) n) << 8) & 0xFF00) | \
      ((((unsigned int) n) >> 8) & 0x00FF) )

//ridefinizione tipi per conoscere misura in bit
typedef unsigned int uint32;
typedef unsigned short int uint16;
typedef unsigned char uint8;

typedef struct item_diz {
    uint16 char_code[TABLE_SIZE];
    uint16 new_code;
    struct item_diz* next;
} nodo_diz;

typedef nodo_diz* diz_lzw;

diz_lzw initUTF8();
diz_lzw initAscii();
diz_lzw cons_tail(diz_lzw l, uint16 *e);
void lzw_compression( uint8 *nome_file );
int trova ( diz_lzw l, uint16 *str);
int confronta(uint16 *a, uint16 *b);
void reset_array( uint16 *array);
void copia_array(uint16 *a, uint16 *b);
void lzw_decompression( uint8 *file_lzw);
int find_code( diz_lzw l, uint16 code, uint16 strCorr[] );
void stampa( uint16 *str );
void concatena(uint16 *a, uint16 *b, uint16 *risultato);
void write_file( uint16 *str, FILE *fo );