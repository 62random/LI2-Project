CFLAGS=-Wall -Wextra -pedantic -O2
FICHEIROS=cgi.h estado.c estado.h pathfind.c animate.c battle.c react.c print.c data.c script.c bot.c main.c Makefile

install: jogo
	sudo cp jogo /usr/lib/cgi-bin
	touch install
	make clean

jogo: estado.o data.o print.o react.o battle.o animate.o pathfind.o script.o bot.o main.o
	cc -o jogo estado.o data.o print.o react.o battle.o animate.o pathfind.o script.o bot.o main.o -lm

jogo.zip: $(FICHEIROS)
	zip -9 jogo.zip $(FICHEIROS)

doc:
	doxygen Doxyfile

clean:
	rm -rf *.o jogo latex install


estado.o: estado.c cgi.h header.h
data.o: data.c
print.o: print.c
react.o: react.c
battle.o: battle.c
animate.o: animate.c
pathfind.o: pathfind.c
script.o: script.c
bot.o: bot.c
main.o: main.c
