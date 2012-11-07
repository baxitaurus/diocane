#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef MENU_H
#include "menu.h"
#endif

#ifndef READFILE_H
#include "readfile.h"
#endif

#ifndef LZW_H
#include "lzw.h"
#endif

int main( int argc, char **argv){
    int scelta=0;
    char nome_file[1024];
    list l=NULL;
    
    
    
    menu_start();
    menu( &scelta );
    
    while( scelta != 6 ){
        switch ( scelta ) {
            case 1:
                printf("Creazione dizonaro \n");
                printf("Digita il nome del file da comprimere\n");
                fflush(stdin);
                scanf("%s", nome_file);
                l = scroll_txt_file(nome_file, l);                                
                menu( &scelta);
                break;
            case 2:
                printf("Scelta 2\n");
                menu( &scelta);
                break;
            case 3:
                printf("Compressione lzw\n");
                printf("Digita il nome del file da comprimere\n");
                fflush(stdin);
                scanf("%s", nome_file);
                lzw_compression( nome_file );
                printf("*********************** FINE *************************\n");
                printf("******************************************************\n");
                printf("\n\n\n\n");
                menu( &scelta);
                break;
            case 4:
                
                menu( &scelta);
                break;
            case 5:
                printf("Decompressione lzw\n");
                printf("Digita il nome del file da decomprimere\n");
                fflush(stdin);
                scanf("%s", nome_file);
                lzw_decompression( nome_file );
                printf("*********************** FINE *************************\n");
                printf("******************************************************\n");
                printf("\n\n\n\n");
                menu( &scelta);
                break;
            case 6:
                printf("USCITA\n");
                break;
            default:
                menu( &scelta);
                break;
        }
    }
    
    return 0;    
}
