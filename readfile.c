#include "readfile.h"

<<<<<<< Updated upstream
static unsigned int totale_caratteri_letti = 0;


list scroll_txt_file(char *file, list l){
=======
list scroll_txt_file(char file[], list l){
>>>>>>> Stashed changes
    FILE *fp;
    unsigned int x=0;
    unsigned char y=0;
    list lista_ordinata=NULL;
    int overflow=0;
<<<<<<< Updated upstream
    unsigned int dim_file;
    int old_perc = 0, perc;
    
    if((fp=fopen(file, "rb"))==NULL){
=======
    if((fp=fopen(file, "rt"))==NULL){
>>>>>>> Stashed changes
        printf("ERRORE: apertura file: %s\n", file);
        exit(1);
    }
    
    printf("Inizio processo di calcolo percentuali caratteri sul file %s\n", file );
    fseek(fp, 0, SEEK_END);
    dim_file = ftell(fp);    
    printf("Dimensione file %s: %d byte\n", file, dim_file);
    fseek(fp, 0, SEEK_SET);    
    
    printf("Percentuale: \n");
    while((fread(&x, 1, 1, fp)) > 0){ 
        totale_caratteri_letti++;
        
        perc = (ftell(fp)*100)/dim_file;
        if(perc != old_perc){
                printf("\b\b\b\b\b\b %d %% ", perc );        
                fflush( stdout );
                old_perc = perc;
        }
                
        if( x > 0x19 && x <= 0x7E )
            l = cons(l, x, &overflow);
        else if( x > 0x7E ){
            fread(&y, 1, 1, fp);                 
            x<<=8;
            x+=y;            
            y=0;
            if( x >= 0xC2A0 && x <= 0xC3bF)
                l = cons(l, x, &overflow);
        }
        x = 0x0000;
    }
    printf("\n");
    fclose(fp);
    lista_ordinata = ordina_lista(l);    
    return lista_ordinata;
}

list ordina_lista( list l){
    list lista_ordinata=NULL;  
    while ( l!= NULL ){              
        lista_ordinata = insOrd( lista_ordinata, l->value );                
        l = l->next;
    }
    return lista_ordinata;
}

list insOrd( list l, info_carattere e){
    if(l==NULL)
        return cons_el( e, l );
    else if(e.presenze < l->value.presenze )
        return cons_el ( e, l );
    else 
        return cons_el( l->value, insOrd( l->next, e ) );
}

list cons_el( info_carattere m,  list lista_ordinata){
    list aux;
    aux=(list)malloc(sizeof(nodo));
    aux->value=m;    
    aux->next=lista_ordinata;
    return aux;
}

list cons (list l,unsigned int x, int *overflow) {
    if(member(l,x)){
        add_presenza(l,x, &overflow);
        return l;
    } else {
        list aux;
        aux=(list)malloc(sizeof(nodo));
        aux->value.carattere=x;
        aux->value.presenze=1;
        aux->next=l;
        return aux;
    }
}

int add_presenza( list l, unsigned int x, int **overflow){
    int trovato = 0;
    unsigned int tester = 0x0000-2;
    while((l!=NULL) && !trovato){
        if(l->value.carattere == x){
            l->value.presenze++;
            trovato = 1;
            if(l->value.presenze == tester)
                **overflow = 1;
        } else
            l = l->next;
    }
    return trovato;   
}

int member( list l, unsigned int x){
    int trovato = 0;
    while((l!=NULL) && !trovato){
        if(l->value.carattere == x)
            trovato = 1;
        else
            l = l->next;
    }
    return trovato;   
}

void show_list(list l){
    while(l!=NULL){
        printf("%x - %d \n", l->value.carattere, l->value.presenze);
        l=l->next;
    }        
}

int length_list(list l){
    int dim=0;
    while(l!=NULL){
        l=l->next;
        dim++;
    }
    return dim;
}

float calcolo_entropia(list l){
    float totale = 0.0;
    float p = 0.0;
    while(l!=NULL){
        // p = probabilita simbolo
        p = 1.0 * l->value.presenze / totale_caratteri_letti;
        totale = totale + ( p * log2(p) );
        l = l->next;
    }
    return totale;
}