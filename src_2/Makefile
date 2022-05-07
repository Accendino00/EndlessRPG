All: Gioco clean

Gioco: Gioco.o Entita.o Player.o Stanza.o Livello.o General.o Colors.o MenuMain.o MenuOptions.o 
	g++ -g -Wall -o Gioco Gioco.o Entita.o Player.o Stanza.o Livello.o General.o Colors.o MenuMain.o MenuOptions.o -lncursesw

Gioco.o:
	g++ -g -Wall -c Gioco.cpp -lncursesw

Entita.o:
	g++ -g -Wall -c ./entita/Entita.cpp -lncursesw

Player.o:
	g++ -g -Wall -c ./entita/Player.cpp -lncursesw

Stanza.o:
	g++ -g -Wall -c ./mappa/Stanza.cpp -lncursesw

Livello.o:
	g++ -g -Wall -c ./mappa/Livello.cpp -lncursesw

General.o:
	g++ -g -Wall -c ./generale/General.cpp -lncursesw

Colors.o:
	g++ -g -Wall -c ./generale/Colors.cpp -lncursesw

MenuMain.o:
	g++ -g -Wall -c ./menu/MenuMain.cpp -lncursesw

MenuOptions.o:
	g++ -g -Wall -c ./menu/MenuOptions.cpp -lncursesw

clean:
	rm *.o
