CC=gcc
SRC_DIRS=./src
OBJ=$(shell find $(SRC_DIRS) -name '*.cpp' -or -name '*.c' -or -name '*.s')
CFLAGS=-lSDL2 -lSDL2 -Wall
prog: 
	 $(CC)   $(OBJ) $(CFLAGS) -o tictactoe
clean:
	rm -rf *.o
mrproper: clean
	rm -rf tictactoe