All: Gioco clean

Gioco: main.o Entita.o Nemico.o Proiettile.o Artefatto.o Porta.o ListaEntita.o ListaNemici.o ListaProiettili.o ListaArtefatti.o ListaPorte.o Stanza.o Livello.o Player.o GameData.o Gioco.o Colors.o Menu.o MenuMain.o MenuScore.o MenuOptions.o MenuCrediti.o
	g++ -g -Wall -o Gioco main.o Entita.o Nemico.o Proiettile.o Artefatto.o Porta.o ListaEntita.o ListaNemici.o ListaProiettili.o ListaArtefatti.o ListaPorte.o Stanza.o Livello.o Player.o GameData.o Gioco.o Colors.o Menu.o MenuMain.o MenuScore.o MenuOptions.o MenuCrediti.o -lncursesw

main.o:
	g++ -g -Wall -c main.cpp -lncursesw

Entita.o:
	g++ -g -Wall -c ./entita/Entita.cpp -lncursesw

Nemico.o:
	g++ -g -Wall -c ./entita/Nemico.cpp -lncursesw

Proiettile.o:
	g++ -g -Wall -c ./entita/Proiettile.cpp -lncursesw

Artefatto.o:
	g++ -g -Wall -c ./entita/Artefatto.cpp -lncursesw

Porta.o:
	g++ -g -Wall -c ./entita/Porta.cpp -lncursesw

ListaEntita.o:
	g++ -g -Wall -c ./liste/ListaEntita.cpp -lncursesw

ListaNemici.o:
	g++ -g -Wall -c ./liste/ListaNemici.cpp -lncursesw

ListaProiettili.o:
	g++ -g -Wall -c ./liste/ListaProiettili.cpp -lncursesw

ListaArtefatti.o:
	g++ -g -Wall -c ./liste/ListaArtefatti.cpp -lncursesw

ListaPorte.o:
	g++ -g -Wall -c ./liste/ListaPorte.cpp -lncursesw

Stanza.o:
	g++ -g -Wall -c ./mappa/Stanza.cpp -lncursesw

Livello.o:
	g++ -g -Wall -c ./mappa/Livello.cpp -lncursesw

Player.o:
	g++ -g -Wall -c ./entita/Player.cpp -lncursesw

GameData.o:
	g++ -g -Wall -c ./generale/GameData.cpp -lncursesw

Colors.o:
	g++ -g -Wall -c ./generale/Colors.cpp -lncursesw

Menu.o:
	g++ -g -Wall -c ./menu/Menu.cpp -lncursesw

MenuMain.o:
	g++ -g -Wall -c ./menu/MenuMain.cpp -lncursesw

MenuScore.o:
	g++ -g -Wall -c ./menu/MenuScore.cpp -lncursesw

MenuOptions.o:
	g++ -g -Wall -c ./menu/MenuOptions.cpp -lncursesw

MenuCrediti.o:
	g++ -g -Wall -c ./menu/MenuCrediti.cpp -lncursesw

Gioco.o:
	g++ -g -Wall -c ./generale/Gioco.cpp -lncursesw

clean:
	rm *.o
