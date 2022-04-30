All: Gioco clean

Gioco: main.o Entita.o
	g++ -Wall -o Gioco main.o Entita.o -lncursesw

main.o: main.cpp Entita.hpp
	g++ -Wall -c main.cpp -lncurses

Entita.o: Entita.cpp Entita.hpp
	g++ -Wall -c Entita.cpp -lncurses

clean:
	rm *.o
