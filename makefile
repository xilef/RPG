OBJS = main.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
SRCFOLDER = src
OUTFOLDER = bin

rpg : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(OUTFOLDER)/rpg

main.o : character.h
	$(CC) $(CFLAGS) $(SRCFOLDER)/main.cpp

clean :
	rm -rf *o
