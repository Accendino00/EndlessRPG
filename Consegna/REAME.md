# Dungneon

## Descrizione del gioco

**Dungneon** è un top-down shooter dove si ***esplorno livelli, collezionano artefatti e battono nemici.***

Man mano che vai avanti, guadagnerai punti sconfiggendo i nemici che diventeranno sempre più forti e diventerai più potente collezionando gli artefatti.

Tuttavia, una volta che la tua salute arriverà a 0, dovrai iniziare tutto da capo! I tuoi punti, però, verrano salvati, e potrai confrontarti con le altre persone hanno giocato.

La parte grafica è stata interamente realizzata con **ncurses**. Il codice, invece, è scritto interamente in **CPP**.

&nbsp;

# Come installare il gioco

## Dipendeze esterne

Questo gioco può essere giocato esclusivamente da **Linux**.
Avrai bisogno della libreria **ncurses**, che puoi installare tramite il comando:

```bash
sudo apt-get install libncurses5-dev libncursesw5-dev 
```

Dopo aver installato **ncurses**, ti basterà eseguire il **Makefile** eseguendo il comando:

```bash
make 
```

Il tempo di compilazione può essere abbastanza lungo.

Adesso che hai compilato il gioco, puoi giocarlo eseguendo da terminale ***Gioco***:

```bash
./Gioco
```

&nbsp;

# Come giocare

## Menu

Dopo aver avviato il gioco, sarai davanti al menu principale. Per spostarti i *qualsiasi* menu puoi usare le **frecce**, oppure **WASD**. Per scegliere l'opzione evidenziata premi **Invio**.

Dal menu principale puoi scegliere:
- ***Gioca***
  - Avvia la partita.
  - Se devi, durante la partita, puoi premere 'p' per andare al **menu di pausa**.
- ***Punteggi***
  - Elenco degli **highscore**
- ***Opzioni***
  - Si possono modificare le opzioni, tra cui:
    - FPS cap, ovvero il numero massimo di FPS
    - Se mostrare gli FPS
    - La difficoltà
- ***Istruzioni***
  - Da qui, puoi vedere le istruzioni del gioco. Se hai dubbi su come si gioca, **controlla questa opzione del menu!**

I vari sub-menu sono intuitivi, una volta che si capisce come funziona uno di essi, quindi lasciamo l'esplorazione all'utente. *Da notare* che alcuni menu hanno una sola opzione, che è anche l'unica evidenziata. Quindi in quei casi, basta premere **invio** per tornare indietro.

&nbsp;

## Gioco

Per vedere i comandi per giocare, vedere le **Istruzioni**, che puoi trovare sia nel menu principale che nel **menu di pausa**, al quale puoi accedere durante la partita premendo ***p***.

> L'obbiettivo è semplice - fai più punti possibili!

Per farli, devi sconfiggere nemici, e per sconfiggere nemici più facilmente devi raccogliere gli artefatti, che ti rendono più forte.

Più alta è la difficoltà, più punti guadagnerai. Quindi, se te la senti, **modifica la difficoltà dal menù delle opzioni**. Il nemico che dà più punti di tutti è il **boss**. Ma non passare al livello successivo subito dopo averlo battuto! Ti potresti perdere degli artefatti e, visto che i nemici diventeranno **più difficili quando passi al livello successivo**. 