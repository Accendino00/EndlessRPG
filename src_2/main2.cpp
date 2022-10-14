#include <iostream>

int main() {

    int dim_x = 0, dim_y = 0;

    // Creazione della stringa che contiene il percorso al file della mappa scelta
    FILE * fin;
    fin = fopen( "./mappa/matrici_mappe/mappa0.map" , "r");
    
    //controllo fino a fine riga per trovare le x
    while(fgetc(fin)!='\n'){
        dim_x+=1;
    }
    rewind(fin);

    //controllo fino a fine file per trovare le y
    while(!feof(fin)){
        if(fgetc(fin)=='\n'){
            dim_y+=1;
        }
    }
    rewind(fin);

    fclose(fin);

    printf("dimensione (x: %d, y: %d)\n", dim_x, dim_y);


}