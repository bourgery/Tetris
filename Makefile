CC = gcc
CFLAGS = -std=c99 -g -Wall
LFLAGS = sdl-config --libs
DP = -lSDL_image -lSDL_ttf
LFLAG = -I/opt/local/include
SRC = main.c jeu_classique.c jeu_sprint.c piece.c highscore.c menu.c
OBJ = $(SRC:.c=.o)

all: tetris

tetris: $(OBJ)
	@$(CC) $(CFLAGS) -o $@ $^ `$(LFLAGS)` $(DP)

%.o: %.c 
	@$(CC) $(CFLAGS) -o $@ -c $< $(LFLAG)

execute:
	@./tetris

clean:
	@rm -f *~ *.o tetris

