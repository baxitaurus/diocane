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
    list l=NULL;
    lzw_compression();
    //lzw_decompression();
    
    //menu_start();
    //menu( &scelta );
    /*
    while( 0 ){ // scelta != 6 ){
        switch ( scelta ) {
            case 1:
                printf("Creazione dizonaro per file %s\n", argv[1]);
                l = scroll_txt_file(argv[1], l);                
                show_list( l );
                menu( &scelta);
                break;
            case 2:
                printf("Scelta 2\n");
                menu( &scelta);
                break;
            case 3:
                printf("Compressione lzw\n");
                lzw_compression();
                menu( &scelta);
                break;
            case 4:
                
                menu( &scelta);
                break;
            case 5:
                printf("DeCompressione lzw\n");
                lzw_decompression();
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
    */
    return 0;    
}
