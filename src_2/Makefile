All: Gioco clean

Gioco: main2.o Entita.o Player.o Proiettile.o Stanza.o Livello.o GameData.o Gioco.o Colors.o MenuMain.o MenuOptions.o MenuCrediti.o
	g++ -g -Wall -o Gioco main2.o Entita.o Player.o Proiettile.o Stanza.o Livello.o GameData.o Gioco.o Colors.o MenuMain.o MenuOptions.o MenuCrediti.o -lncursesw

main2.o:
	g++ -g -Wall -c main2.cpp -lncursesw

Entita.o:
	g++ -g -Wall -c ./entita/Entita.cpp -lncursesw

Player.o:
	g++ -g -Wall -c ./entita/Player.cpp -lncursesw

Proiettile.o:
	g++ -g -Wall -c ./entita/Proiettile.cpp -lncursesw

Stanza.o:
	g++ -g -Wall -c ./mappa/Stanza.cpp -lncursesw

Livello.o:
	g++ -g -Wall -c ./mappa/Livello.cpp -lncursesw

GameData.o:
	g++ -g -Wall -c ./generale/GameData.cpp -lncursesw

Colors.o:
	g++ -g -Wall -c ./generale/Colors.cpp -lncursesw

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
