# Makefile
CC = gcc
CFLAGS = -Wall -Wextra
SDL_FLAGS = $(shell pkg-config --cflags sdl2 SDL2_image)
SDL_LIBS = $(shell pkg-config --libs sdl2 SDL2_image)

all: jeu

jeu: main.o paddle.o ball.o game.o block.o
	$(CC) -o jeu main.o paddle.o ball.o game.o block.o $(SDL_LIBS)

main.o: main.c paddle.h ball.h game.h block.h
	$(CC) $(CFLAGS) $(SDL_FLAGS) -c main.c

paddle.o: paddle.c paddle.h
	$(CC) $(CFLAGS) $(SDL_FLAGS) -c paddle.c

ball.o: ball.c ball.h
	$(CC) $(CFLAGS) $(SDL_FLAGS) -c ball.c

game.o: game.c game.h
	$(CC) $(CFLAGS) $(SDL_FLAGS) -c game.c

block.o: block.c block.h ball.h
	$(CC) $(CFLAGS) $(SDL_FLAGS) -c block.c

clean:
	rm -f *.o ping

run: ping
	./ping