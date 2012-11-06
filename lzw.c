#ifndef LZW_H
#include "lzw.h"
#endif

uint16 diz_long;
uint16 diz_original;
diz_lzw initUTF8(){
    //creo lista con i valori base dell'alfabeto a-z A-Z 0-1 simboli e accenti vari
    int i;
    uint16 karray[TABLE_SIZE];
    uint16 k;
    
    diz_lzw dizionario = NULL;
    diz_long =0;
    
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
    diz_original = diz_long;
    return dizionario;
}

diz_lzw initAscii(){
    diz_lzw dizionario = NULL;
    uint16 karray[TABLE_SIZE];
    int i;
    diz_long =0;
    reset_array( karray );
    for( i=0x61; i<=0x63; i++){ 
        karray[0] = i;
        dizionario = cons_tail(dizionario, karray);
    }
    diz_original = diz_long;
    return dizionario;
}

void lzw_compression( char *nome_file ){
    uint16 strCorr[TABLE_SIZE];
    uint16 strPrs[TABLE_SIZE];
    uint16 lstChr;
    uint16 carattere_speciale = 0;
    uint8 carattere_letto=0;
    uint16 write; 
    uint16 diz_position;
    uint32 dim_file_orig;    
    char file_lzw[100]="";
    
    FILE *fp, *fo;
    diz_lzw dizionario = NULL;
    int buffer_pointer = 0;
    int i;
        
    printf("Apertura File %s ...\n", nome_file);
    if((fp=fopen( nome_file, "rb"))==NULL){
        printf("ERRORE: apertura file: %s\n", nome_file);
        exit(1);
    }
    
    fseek(fp, 0, SEEK_END);
    dim_file_orig = ftell(fp);
    printf("Dimensione file originale %s: %d byte\n", nome_file, dim_file_orig);
    fseek(fp, 0, SEEK_SET);
      
    strcpy(file_lzw, nome_file);
    strcat(file_lzw, ".lzw");
    
    if((fo=fopen(file_lzw, "wb"))==NULL){
        printf("ERRORE: apertura file: %s\n", file_lzw);
        exit(1);
    }
    printf("Creazione dizionario base...\n");
    dizionario = initUTF8();
    reset_array( strCorr );
    printf("Inizio processo di compressione...\n");
    printf("Percentuale: \n");
    while((fread( &carattere_letto, sizeof( uint8 ), 1, fp)) > 0){         
        printf("\b\b\b %ld", (ftell(fp)*100)/dim_file_orig);        
        fflush( stdout );
        if( carattere_letto <= 0x7F ){
            strCorr[buffer_pointer] = carattere_letto;            
            carattere_letto = 0;   
        } else {
            carattere_speciale = carattere_letto;
            fread(&carattere_letto, sizeof( uint8 ), 1, fp);
            carattere_speciale <<= 8;
            carattere_speciale += carattere_letto;            
            strCorr[buffer_pointer] = carattere_speciale;
            carattere_speciale = 0;      
        }
        
        if ( (diz_position = trova( dizionario, strCorr ))){
            if ( buffer_pointer< TABLE_SIZE )
                buffer_pointer++;
            else {
                lstChr = strCorr[buffer_pointer];
                reset_array( strPrs );                
                fwrite( &diz_position, sizeof( uint16 ), 1, fo);
                printf("\n+\n");
                reset_array( strCorr );
                buffer_pointer = 0;
                strCorr[buffer_pointer] = lstChr;
                buffer_pointer++;
            }
        } else {
            lstChr = strCorr[buffer_pointer];
            reset_array( strPrs );
            for( i = 0; i < buffer_pointer; i++ )
                strPrs[i] = strCorr[i];  
            write = trova ( dizionario, strPrs);            
            fwrite( &write, sizeof( uint16 ), 1, fo);              
            cons_tail(dizionario, strCorr);
                                          
            reset_array( strCorr );
            buffer_pointer = 0;
            strCorr[buffer_pointer] = lstChr;
            buffer_pointer++;
        }
    }  
    write = trova( dizionario, strCorr);
    fwrite( &write, 2, 1, fo);
    printf("\nNUMERO DI DATI IN DIZIONARIO: %d ( %d + %d )\n", diz_long, diz_original, diz_long - diz_original );   
    fseek(fo, 0, SEEK_SET);
    fseek(fo, 0, SEEK_END);
    printf("\nDimensione file compresso %s: %ld byte\n", file_lzw, ftell(fo));
    printf("Rapporto compressione: %ld %% \n", (ftell(fo)*100)/ftell(fp));
    fclose( fp );
    fclose( fo );
    
}


void lzw_decompression( char *file_lzw ){
    FILE *fi, *fo;
    uint16 dec, olDec;
    uint16 strLst[TABLE_SIZE];
    uint16 strTmp[TABLE_SIZE];
    uint16 strConc[TABLE_SIZE];
    diz_lzw dizionario = NULL;
    char file_decompresso[100]=""; 
    uint32 dim_file_compresso;
    
    printf("Apertura File %s ...\n", file_lzw);
    if((fi=fopen(file_lzw, "rb"))==NULL){
        printf("ERRORE: apertura file: %s\n", file_lzw);
        exit(1);
    }    
    fseek(fi, 0, SEEK_END);
    dim_file_compresso = ftell(fi);
    printf("Dimensione file compresso %s: %d byte\n", file_lzw, dim_file_compresso);
    fseek(fi, 0, SEEK_SET);
    
    strcpy( file_decompresso, file_lzw);
    strcat( file_decompresso, ".txt");  
    if((fo=fopen( file_decompresso, "wb"))==NULL){
        printf("ERRORE: apertura file: %s\n", file_decompresso);
        exit(1);
    }
    
    dizionario = initUTF8();
    reset_array( strLst );
    reset_array( strTmp );
    reset_array( strConc );
    
    printf("Inizio processo di compressione...\n");
    printf("Percentuale: \n");
    
    fread(&dec, sizeof( uint16 ), 1, fi);
    find_code( dizionario, dec, strLst );
    //stampa( strLst );
    write_file( strLst, fo );
    olDec = dec;    
    while((fread(&dec, sizeof( uint16 ), 1, fi)) > 0){
        printf("\b\b\b %ld", (ftell(fi)*100)/dim_file_compresso);        
        fflush( stdout );  
        if( find_code( dizionario, dec, strTmp ) ){
            //stampa( strTmp );
            write_file( strTmp, fo );
            concatena( strLst, strTmp, strConc );
            cons_tail(dizionario, strConc);
            copia_array(strLst, strTmp);
            olDec = dec; 
            reset_array( strTmp );        
            reset_array( strConc );
        } else {
            concatena( strLst, strLst, strConc );
            //stampa( strConc );
            write_file( strConc, fo );
            cons_tail(dizionario, strConc);
        }
    }    
    
    fseek(fo, 0, SEEK_SET);
    fseek(fo, 0, SEEK_END);
    printf("\nDimensione file decompresso %s: %ld byte\n", file_decompresso, ftell(fo));
    fclose( fi );
    fclose( fo );    
}

void write_file(uint16 *str, FILE *fo ){
    int i=0;
    uint16 carattere=0;
    while( str[i] != 0 && i < TABLE_SIZE ){
        if(str[i] < 0x7f ){
            //printf(" - Scrive ui: %x, %d, %d\n", str[i], sizeof(str[i]),sizeof(unsigned int) );
            fwrite( &str[i], sizeof( uint8 ),1, fo);
        }else{
            //printf(" - Scrive ch: %x, %d, %d\n", str[i], sizeof(str[i]),sizeof(char) );
            carattere = ByteSwap16( str[i] );
            fwrite( &carattere, sizeof( uint16 ), 1, fo);
        }
        i++;
    }
}


void stampa(uint16 *str ){
    int i=0;
    while( str[i] != 0 && i < TABLE_SIZE ){
        printf("%d", str[i]);
        i++;
    }
    printf( "\n" );
}

int find_code( diz_lzw l,uint16 code,uint16 strCorr[] ){
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


diz_lzw cons_tail(diz_lzw l,uint16 *e){
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

uint16 trova ( diz_lzw l,uint16 *str){
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

int confronta(uint16 *a,uint16 *b){
    int i=0;
    while(a[i] == b[i] && i<TABLE_SIZE)
        i++;
    if( i == TABLE_SIZE)
        return 1;
    else
        return 0;
}

void reset_array( uint16 *array){
    int i;
    for( i = 0; i < TABLE_SIZE; i++ )
        array[i] = 0x0000;
}

void copia_array(uint16 *a,uint16 *b){
    int i;
    for( i = 0; i < TABLE_SIZE; i++ )
        a[i] = b[i];
    
}

void concatena(uint16 *a,uint16 *b,uint16 *risultato){
    int i=0;
    for( i = 0; i < TABLE_SIZE; i++ ){
        risultato[i]=a[i];
        if(a[i]==0){
            risultato[i] = b[0];
            break;
        }
    }
}

