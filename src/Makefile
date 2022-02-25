All: Gioco clean

Gioco: main.o Entita.o
	g++ -o Gioco main.o Entita.o -lncurses

main.o: main.cpp Entita.hpp
	g++ -c main.cpp -lncurses

Entita.o: Entita.cpp Entita.hpp
	g++ -c Entita.cpp -lncurses

clean:
	rm *.o
