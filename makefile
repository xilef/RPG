OBJS = main.o character.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
SRCFOLDER = src
OUTFOLDER = bin

rpg : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(OUTFOLDER)/rpg

main.o : $(SRCFOLDER)/character.h $(SRCFOLDER)/main.cpp
	$(CC) $(CFLAGS) $(SRCFOLDER)/main.cpp

character.o : $(SRCFOLDER)/character.h $(SRCFOLDER)/character.cpp
	$(CC) $(CFLAGS) $(SRCFOLDER)/character.cpp

clean :
	rm -rf *o
