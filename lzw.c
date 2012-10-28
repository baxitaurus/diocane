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
    
    for( i=0x01; i<=0x7f; i++){ 
        karray[0] = i;
        dizionario = cons_tail(dizionario, karray);
    }
    k = 0xC2;
    k <<= 8;
    for ( i = 0x80; i <= 0xBF; i++ ){
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

diz_lzw initAscii(){
    diz_lzw dizionario = NULL;
    unsigned int karray[TABLE_SIZE];
    int i;
    diz_long =0;
    output_long=0;
    reset_array( karray );
    for( i=0x01; i<=0xFF; i++){ 
        karray[0] = i;
        dizionario = cons_tail(dizionario, karray);
    }
    return dizionario;
}



void lzw_compression(){
    unsigned int strCorr[TABLE_SIZE];
    unsigned int strPrs[TABLE_SIZE];
    unsigned int lstChr;
    FILE *fp, *fo;
    unsigned int carattere_letto=0;
    unsigned char y=0;
    diz_lzw dizionario = NULL;
    int buffer_pointer = 0;
    int i;
    unsigned int write;
    
    dizionario = initAscii();
    
    if((fp=fopen("testo_prova.txt", "rb"))==NULL){
        printf("ERRORE: apertura file: %s\n", "Bibbia");
        exit(1);
    }
    
    if((fo=fopen("testo_prova.lzw", "wb"))==NULL){
        printf("ERRORE: apertura file: %s\n", "Bibbia.lzw");
        exit(1);
    }
    
    reset_array( strCorr );
    
    while((fread(&carattere_letto, 1, 1, fp)) > 0){                
        if( carattere_letto <= 0x7F ){
            //carattere ascii
            strCorr[buffer_pointer] = carattere_letto;
        } else if( carattere_letto > 0x7E ){
            fread(&y, 1, 1, fp);                 
            carattere_letto<<=8;
            carattere_letto+=y;            
            y=0;
            strCorr[buffer_pointer] = carattere_letto;
         
        }
        if (trova( dizionario, strCorr )){
            //trovata stringa in dizionario
            buffer_pointer++;          
        } else {
            lstChr = strCorr[buffer_pointer];
            reset_array( strPrs );
            for( i = 0; i < buffer_pointer; i++ )
                strPrs[i] = strCorr[i];  
            write = trova ( dizionario, strPrs);
            //printf("%x\n", write);//output file
            fwrite( &write, sizeof(unsigned short int), 1, fo);
            output_long++;
            cons_tail(dizionario, strCorr);
            reset_array( strCorr );
            buffer_pointer = 0;
            strCorr[buffer_pointer] = lstChr;
            buffer_pointer++;
        }
    }  
    write = trova( dizionario, strCorr);
    //printf("%x\n", write);//output file    
    fwrite( &write, sizeof(unsigned short int), 1, fo);
    printf("NUMERO DI DATI IN DIZIONARIO: %d\n", diz_long);
    printf("NUMERO DI DATI IN OUTPUT: %d\n", output_long);
    fclose( fp );
    fclose( fo );
}


void lzw_decompression(){
    FILE *fi, *fo;
    unsigned int dec, olDec;
    unsigned int strLst[TABLE_SIZE];
    unsigned int strTmp[TABLE_SIZE];
    unsigned int strConc[TABLE_SIZE];
    diz_lzw dizionario = NULL;
    
    dizionario = initAscii();
    if((fi=fopen("testo_prova.lzw", "rb"))==NULL){
        printf("ERRORE: apertura file: %s\n", "x");
        exit(1);
    }
    
    if((fo=fopen("testo_prova.dec.txt", "wb"))==NULL){
        printf("ERRORE: apertura file: %s\n", "xxx");
        exit(1);
    }
    reset_array( strLst );
    reset_array( strTmp );
    reset_array( strConc );
    
    fread(&dec, sizeof( unsigned int), 1, fi);
    find_code( dizionario, dec, strLst );
    stampa( strLst );
    write_file( strLst, fo );
    olDec = dec;
    
    
    while((fread(&dec, sizeof( unsigned int), 1, fi)) > 0){  
        if( find_code( dizionario, dec, strTmp ) ){
            stampa( strTmp );
            write_file( strTmp, fo );
            concatena( strLst, strTmp, strConc );
            cons_tail(dizionario, strConc);
            copia_array(strLst, strTmp);
            olDec = dec; 
            reset_array( strTmp );        
            reset_array( strConc );
        } else {
            concatena( strLst, strLst, strConc );
            stampa( strConc );
            write_file( strConc, fo );
            cons_tail(dizionario, strConc);
        }
    }    
    fclose( fi );
    fclose( fo );    
}

void write_file( unsigned int *str, FILE *fo ){
    int i=0;
    while( str[i] != 0 && i < TABLE_SIZE ){
        if(str[i] > 0x7e ){
            printf(" - Scrive ui: %x, %d, %d\n", str[i], sizeof(str[i]),sizeof(unsigned int) );
            //fwrite( &str[i], sizeof(unsigned int),2, fo);
        }else{
            printf(" - Scrive ch: %x, %d, %d\n", str[i], sizeof(str[i]),sizeof(char) );
            fwrite( &str[i], sizeof( char), 1, fo);
        }
        i++;
    }
}


void stampa( unsigned int *str ){
    int i=0;
    while( str[i] != 0 && i < TABLE_SIZE ){
        printf("%c", str[i]);
        i++;
    }
}

int find_code( diz_lzw l, unsigned int code, unsigned int strCorr[] ){
    int trovato = 0;
    while((l!=NULL) && !trovato){
        if( l->new_code == code ){        
            trovato = 1;
            copia_array( strCorr, l->char_code );
        }else
            l = l->next;
    }
    return trovato;    
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

void concatena(unsigned int *a, unsigned int *b, unsigned int *risultato){
    int i=0;
    for( i = 0; i < TABLE_SIZE; i++ ){
        risultato[i]=a[i];
        if(a[i]==0){
            risultato[i] = b[0];
            break;
        }
    }
}