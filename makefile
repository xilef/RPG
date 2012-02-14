OBJS = main.o character.o skill.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c $(DEBUG)
LFLAGS = -Wall $(DEBUG)
SRCFOLDER = src
OUTFOLDER = bin

rpg : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o $(OUTFOLDER)/rpg

main.o : $(SRCFOLDER)/skill.h $(SRCFOLDER)/character.h $(SRCFOLDER)/main.cpp
	$(CC) $(CFLAGS) $(SRCFOLDER)/main.cpp

character.o : $(SRCFOLDER)/skill.h $(SRCFOLDER)/character.h $(SRCFOLDER)/character.cpp
	$(CC) $(CFLAGS) $(SRCFOLDER)/character.cpp

skill.o : $(SRCFOLDER)/skill.h $(SRCFOLDER)/skill.cpp
	$(CC) $(CFLAGS) $(SRCFOLDER)/skill.cpp

clean :
	rm -rf *.o
