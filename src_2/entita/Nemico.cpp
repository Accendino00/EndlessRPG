/*

    Nemici:
        - Si muovono
            - In modo diverso da tipo a tipo
        - Sparano
            - Più o meno, in base al tipo
        - Possono cambiare forma
            - Per indicare che stanno per sparare
        - Hanno dimensione e immagini diverse




        - Per evitare di implementare nuove strutture dati, lo stampabile
        sarà contenuto nello stampabile, ma offsettato di una certa dimensione

        - La dimensione del nemico non cambierà dinamicamente, ma la sua forma sì,
        in quanto si potrà scegliere che parte stampare in base al tempo.

            - L'idea è un dato tipo:
                short FrameAttuale
            e nel for di stampabile, al x è j + (FrameAttuale*dim_x)

            Per implementare delle routine
            dovrei fare che ci sono delle cose che fa ogni n tick
            tipo 
            {spara, spara, spara, fermo, fermo, muovi, fermo, muovi, fermo} e poi quando 
            arriva alla fine ripete la routine
            quindi una serie di switch in base all'indice della cosa da fare adesso
            in base al nemico ogni cosa ha una cosa diversa

            ognuna di quelle cose è definita da dei define, tipo NEMICO_SPARA, NEMICO_FERMO, NEMICO_MUOVI, etc.

            Potrei far sì che ognuna di quelle cose sia una lista di cose che deve fare, tipo
            CAMBIA_ANIMAZIONE -> MUOVITI



            PER CAPIRE DOVE SPARARE:
                - Tra i due punti si forma un angolo, dove la distanza x è il
                raggio dell'angolo, l'altezza y è il valore della tangente dell'angolo
                
                - Per trovare l'angolo bisogna quindi fare arctan(y/x)

                In base all'angolo (se si trova in una di 3 sezioni per capire se in alto, diagonale, o di lato),
                e se la x di uno è maggiore dell'altro
                e se la y di uno è maggiore dell'altro
                si spara il proiettile
*/

#include "../generale/libs.hpp"


class Nemico : public Entita {

};