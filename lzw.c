#ifndef LZW_H
#include "lzw.h"
#endif

unsigned int diz_long;
unsigned int output_long;
diz_lzw init(){
    //creo lista con i valori base dell'alfabeto a-z A-Z 0-1 simboli e accenti vari
    int i;
    unsigned int karray[TABLE_SIZE];
    unsigned int k;
    diz_lzw dizionario = NULL;
    diz_long =0;
    output_long=0;
    
    reset_array( karray );
    
    for( i=0x20; i<=0x7e; i++){ 
        karray[0] = i;
        dizionario = cons_tail(dizionario, karray);
    }
    k = 0xC2;
    k <<= 8;
    for ( i = 0xA0; i <= 0xBF; i++ ){
        karray[0] = k+i;
        dizionario = cons_tail(dizionario, karray);
    }
    k = 0xC3;
    k <<= 8;
    for ( i = 0x80; i <= 0xBF; i++ ){       
        karray[0] = k+i;
        dizionario = cons_tail(dizionario, karray);
    }
    return dizionario;
}

void lzw_compression(){
    unsigned int strCorr[TABLE_SIZE];
    unsigned int strPrs[TABLE_SIZE];
    unsigned int lstChr;
    FILE *fp;
    unsigned int carattere_letto=0;
    unsigned char y=0;
    diz_lzw dizionario = NULL;
    int buffer_pointer = 0;
    int i;
    
    dizionario = init();
    
    if((fp=fopen("testo_prova.txt", "rb"))==NULL){
        printf("ERRORE: apertura file: %s\n", "Bibbia");
        exit(1);
    }
    reset_array( strCorr );
    
    while((fread(&carattere_letto, 1, 1, fp)) > 0){                
        if( carattere_letto > 0x19 && carattere_letto <= 0x7E ){
            //carattere ascii
            strCorr[buffer_pointer] = carattere_letto;
        } else if( carattere_letto > 0x7E ){
            fread(&y, 1, 1, fp);                 
            carattere_letto<<=8;
            carattere_letto+=y;            
            y=0;
            if( carattere_letto >= 0xC2A0 && carattere_letto <= 0xC3bF){
                //carattere speciale
                strCorr[buffer_pointer] = carattere_letto;
            }
        }
        if (trova( dizionario, strCorr )){
            //trovata stringa in dizionario
            buffer_pointer++;          
        } else {
            lstChr = strCorr[buffer_pointer];
            reset_array( strPrs );
            for( i = 0; i < buffer_pointer; i++ )
                strPrs[i] = strCorr[i];                            
            printf("%d\n", trova ( dizionario, strPrs));//output file
            output_long++;
            cons_tail(dizionario, strCorr);
            reset_array( strCorr );
            buffer_pointer = 0;
            strCorr[buffer_pointer] = lstChr;
            buffer_pointer++;
        }
        //esiste carattere_ok in dizionario?
        //se si aggiungo un ulteriore carattere alla stringa
        //se no aggiungo la stringa al dizionario e metto 
        
        
    }  
    printf("%d\n", trova ( dizionario, strCorr));//output file
    printf("NUMERO DI DATI IN DIZIONARIO: %d\n", diz_long);
    printf("NUMERO DI DATI IN output: %d\n", output_long);
}


diz_lzw cons_tail(diz_lzw l, unsigned int *e){
    diz_lzw aux=l;
    if(l==NULL){
        aux=(diz_lzw)malloc(sizeof(nodo_diz));
        l=aux;
    }else{
        while( aux->next != NULL )
                aux=aux->next;
        aux->next=(diz_lzw)malloc(sizeof(nodo_diz));
        aux=aux->next;
    }
    copia_array( aux->char_code, e);
    diz_long++;
    aux->new_code = diz_long;
    aux->next=NULL;
    return l;
}

int trova ( diz_lzw l, unsigned int *str){
    int trovato = 0;
    while((l!=NULL) && !trovato){
        if( confronta( l->char_code, str)){        
            trovato = l->new_code;
            //printf("Trovato carattere %s con codice %d\n", l->char_code, l->new_code );
        }else
            l = l->next;
    }
    return trovato;   
}

int confronta(unsigned int *a, unsigned int *b){
    int i=0;
    while(a[i] == b[i] && i<TABLE_SIZE)
        i++;
    if( i == TABLE_SIZE)
        return 1;
    else
        return 0;
}

void reset_array( unsigned int *array){
    int i;
    for( i = 0; i < TABLE_SIZE; i++ )
        array[i] = 0x0000;
}

void copia_array(unsigned int *a, unsigned int *b){
    int i;
    for( i = 0; i < TABLE_SIZE; i++ )
        a[i] = b[i];
    
}