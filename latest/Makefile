CFLAGS = -Wall -Wextra -std=c99

all: code

color.o: src/color.c
		gcc $(CFLAGS) src/color.c -c 

tile.o: src/tile.c
		gcc $(CFLAGS) src/tile.c -c

queue.o: src/queue.c
		gcc $(CFLAGS) src/queue.c -c

players.o: src/players.c
		gcc $(CFLAGS) src/players.c -c

motif.o: src/motif.c
		gcc $(CFLAGS) src/motif.c -c

test: tst/test.c color.o tile.o queue.o players.o motif.o
		gcc $(CFLAGS) tst/test.c color.o tile.o queue.o players.o motif.o -o tst/test
		./tst/test

code: src/main.c color.o tile.o queue.o players.o motif.o
		gcc $(CFLAGS) src/main.c color.o tile.o queue.o players.o motif.o -o project
		./project 

clean:
		rm -f ./project src/project tst/test color.o tile.o queue.o players.o motif.o