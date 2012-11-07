#ifndef _STDIO_H
#include <stdio.h>
#endif

#ifndef MENU_H
#include "menu.h"
#endif

#ifndef LZW_H
#include "lzw.h"
#endif

#include "huffmantree.h"

int main( int argc, char **argv){
	FILE *f1,*f2;
	float compressione;
	char c;
    int scelta=0;
<<<<<<< Updated upstream
    char nome_file[1024];
    list l=NULL;
    
    
    
=======
	int dim_list,tot_bit_huffman=0,tot_bit_ascii=0;
	new_list l2=NULL;
    list l=NULL;
	tree t=NULL;
	char nome_file[]="C:\\Users\\Rob-And\\Documents\\FILEPROVA.txt";
>>>>>>> Stashed changes
    menu_start();
    menu( &scelta );
    while( scelta != 6 ){
        switch ( scelta ) {
            case 1:
<<<<<<< Updated upstream
                printf("Creazione dizonaro \n");
                printf("Digita il nome del file da comprimere\n");
                fflush(stdin);
                scanf("%s", nome_file);
                l = scroll_txt_file(nome_file, l);                                
=======
                printf("Creazione dizionario per file FILEPROVA.txt\n");
				l = scroll_txt_file(nome_file, l);                
                show_list( l );
>>>>>>> Stashed changes
                menu( &scelta);
                break;
            case 2:
                printf("Scelta 2\n");
				printf("\nQuesta funzione effettuera' una codifica di Huffman sulla base della lista di\noccorrenze creata al passo 1\n");
				printf("In questo passaggio verra' realizzato un file COMPRESSED.txt che riporta la sequenza di bit corrispondente alla compressione simulata\n");
				printf("\nCalcolo lunghezza della lunghezza della lista\n");
				dim_list=length_list(l);
				printf("Numero di elementi calcolati: %d",dim_list);
				printf("\nCreazione di una lista di foglie (proprieta' di prefisso)***\n");
				l2=crea_lista_foglie(l,dim_list);
				printf("\nCreazione dell'albero di Huffman***\n");
				t=crea_huffmantree(l2,t,dim_list);
				printf("\nStampo a video l'albero***\n");
				inorder(t); printf("\n");
				f1=fopen("C:\\Users\\Rob-And\\Documents\\FILEPROVA.txt","rt");
				f2=fopen("C:\\Users\\Rob-And\\Documents\\COMPRESSED.txt","at");
				printf("\nStampa della codifica a video e su file COMPRESSED.txt:\n");
				while(!feof(f1)){
					c=fgetc(f1);
					stampa_codifica(c,t,f2,&tot_bit_huffman);
				}
				fclose(f1); fclose(f2);
				printf("\n\nOperazione terminata, codifica stampata su COMPRESSED.txt***\n");
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
<<<<<<< Updated upstream
=======
                menu( &scelta);
                break;
            case 5:
				printf("\nQuesta opzione permette di leggere la codifica di Huffman precedentemente\nscritta su COMPRESSED.txt al passo 2, e crearne una decodifica che verra' stampata a video\n");
				f1=fopen("C:\\Users\\Rob-And\\Documents\\COMPRESSED.txt","rt");
				stampa_decodifica(t,f1,&tot_bit_ascii);
				fclose(f1);
				printf("\nLa codifica in ASCII utilizza %d bit\n",tot_bit_ascii);
				printf("\nLa codifica in Huffman Statico utilizza %d bit\n",tot_bit_huffman);
				compressione=(float)tot_bit_ascii/tot_bit_huffman;
				printf("\nIl fattore di compressione e' di %f\n",compressione);
				printf("\n\n\n\t\t\t\t***FINE***\n");
                menu( &scelta);
                break;
>>>>>>> Stashed changes
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
