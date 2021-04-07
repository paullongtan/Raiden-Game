# run: objects

run: Raiden/main.o Raiden/menu.o Raiden/info.o Raiden/game.o Raiden/Firebullet.o Raiden/enemy.o Raiden/fighter.o Raiden/professor.o
	@g++ game.o professor.o fighter.o info.o menu.o main.o Firebullet.o enemy.o -o RGame -lsfml-window -lsfml-graphics -lsfml-system -lsfml-audio

dir:
	@if [ ! -d "obj" ]; then mkdir obj; fi

Raiden/professor.o:
	@g++ -w Raiden/professor.cpp -o professor.o -c

Raiden/fighter.o:
	@g++ -w Raiden/fighter.cpp -o fighter.o -c

Raiden/enemy.o:
	@g++ -w Raiden/enemy.cpp -o enemy.o -c

Raiden/Firebullet.o:
	@g++ -w Raiden/Firebullet.cpp -o Firebullet.o -c

Raiden/main.o: Raiden/main.cpp
	@g++ -w Raiden/main.cpp -o main.o -c

Raiden/menu.o: Raiden/menu.cpp
	@g++ -w Raiden/menu.cpp -o menu.o -c

Raiden/info.o: Raiden/info.cpp
	@g++ -w Raiden/info.cpp -o info.o -c

Raiden/game.o: Raiden/game.cpp
	@g++ -w Raiden/game.cpp -o game.o -c

clean:
	@rm -rf *.o 
	@rm -rf RGame
