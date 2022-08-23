All: Gioco clean

Gioco: main.o Entita.o Player.o Nemico.o Proiettile.o ListaEntita.o Stanza.o Livello.o GameData.o Gioco.o Colors.o Menu.o MenuMain.o MenuOptions.o MenuCrediti.o
	g++ -g -Wall -o Gioco main.o Entita.o Player.o Nemico.o Proiettile.o ListaEntita.o Stanza.o Livello.o GameData.o Gioco.o Colors.o Menu.o MenuMain.o MenuOptions.o MenuCrediti.o -lncursesw

main.o:
	g++ -g -Wall -c main.cpp -lncursesw

Entita.o:
	g++ -g -Wall -c ./entita/Entita.cpp -lncursesw

Player.o:
	g++ -g -Wall -c ./entita/Player.cpp -lncursesw

Nemico.o:
	g++ -g -Wall -c ./entita/Nemico.cpp -lncursesw

Proiettile.o:
	g++ -g -Wall -c ./entita/Proiettile.cpp -lncursesw

ListaEntita.o:
	g++ -g -Wall -c ./entita/ListaEntita.cpp -lncursesw

Stanza.o:
	g++ -g -Wall -c ./mappa/Stanza.cpp -lncursesw

Livello.o:
	g++ -g -Wall -c ./mappa/Livello.cpp -lncursesw

GameData.o:
	g++ -g -Wall -c ./generale/GameData.cpp -lncursesw

Colors.o:
	g++ -g -Wall -c ./generale/Colors.cpp -lncursesw

Menu.o:
	g++ -g -Wall -c ./menu/Menu.cpp -lncursesw

MenuMain.o:
	g++ -g -Wall -c ./menu/MenuMain.cpp -lncursesw

MenuOptions.o:
	g++ -g -Wall -c ./menu/MenuOptions.cpp -lncursesw

MenuCrediti.o:
	g++ -g -Wall -c ./menu/MenuCrediti.cpp -lncursesw

Gioco.o:
	g++ -g -Wall -c ./generale/Gioco.cpp -lncursesw

clean:
	rm *.o
