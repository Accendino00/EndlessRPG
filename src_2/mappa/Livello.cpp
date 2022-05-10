#include "../generale/libs.hpp"
//Generazione 

/* Livello -> 5x5
Generazione di un livello standard:
  Quindi generi un livello con 4 stanze tutte collegate
   
Poi per la generazione:
  -  new Livello();
  Loop con:
    - trovaprimolibero() : trova la prima stanza a partire dal centro che ha almeno uno dei quattro lati liberi
                           la prima stanza che trova questo metodo è la stanza centrale ([2][2]), poi va a quelle affinco, poi a quelle affianco di quelle affianco, etc.
    - generaStanza() : sceglie, a partire dalla stanza ritornata da "trovaprimolibero", una stanza casuale tra le quattro affianco, la genera se può (se stanza * è nullo), se non può ne sceglie un'altra
                       se non può sceglierne nessuna, allora esci da questo metodo e non aumenti il contatore del "numero di stanze generate"

      C'è un contatore quando generi le stanze, in questo loop, per certi valori il "new Stanza()" avrà parametri particolari (ex: numero 8 -> miniboss, numero 16 -> boss);

  Puoi decidere se far si che, dopo ogni generaStanza, si salvi la posizione di questa nuova stanza per creare la prossima
                    oppure che, dopo ogni generaStanza, richiama il metodo "trovaprimolibero" e usi queste coordinate per la generazione delle stanze 

  NON interpretare le stanze in questa funzione, ma dopo, quando hai finito
  La funzione "interpretaStanza()" di Stanza, inizializza la matrice cchar_t e la matrice logica in base a 4 bool, che indicano la presenza di altre stanze affianco o meno
                       
Devi far si che sia possibile fare
  void livello.stampa();
    // stampa la stanza attuale, tenuta come parametro
  void livello.cambiaStanza(int direzione)
    // che chiede di poter cambiare la stanza in base alla direzione (0 -> nord, 1->est, etc.)
  bool livello.camminabile(int x, int y)
    // Ritorna vero se si può camminare in queste coordinate, falso se non
  

  Dopo che vengono implementate altre entità, devi poter andare anche a fare tipo "livello.controllaNemici(player, entita)" -> dentro, per ogni entita, si controlla se player.contatto(entita[i])
```
*/

Livello::scegli_lato(Stanza *** matrice_livello , int * x, int *y){ 
    switch(rand() % 4){
        case 0:
        y++;
        break;
        case 1:
        x++;
        break;
        case 2:
        y--;
        break;
        case 3:
        x--;
        break;
    }
}

Livello::Livello(){
    int current_x = 2;
    int current_y = 2;
    int stanza_counter = 0;
    while(stanza_counter < 16)
        if(matrice_livello [current_y] [current_x] != NULL){
            scegli_lato(matrice_livello , &current_y, &current_x);
        } else if (stanza_counter == 8 || stanza_counter == 16){
            matrice_livello [current_y] [current_y] = new Stanza(1);
            stanza_counter++;            
        } else{
            matrice_livello [current_y] [current_y] = new Stanza(0);
            stanza_counter++;
        }
    }
}