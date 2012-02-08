// A very simple Text based RPG
// written by Felix Isaac Palomares

#include <iostream>
#include <string>
#include <stdlib.h>
#include "character.h"

#define EXPLORE_CHOICE 1
#define BUY_CHOICE 2
#define STAT_CHOICE 3
#define EXIT_CHOICE 4

#define PUB_CHOICE 1

using namespace::std;

int running;
character player, enemy;

void init();
void cleanup();
void view_stats();
void show_pub_menu();
void show_outside_menu();
void random_encounter();

int main()
{
	init();

	while (running) {
		switch (player.getlocation()) {
		case PUB:
			cout << "You are in the pub" << endl;
			show_pub_menu();
			break;
		case OUTSIDE:
			cout << "You are outside exploring" << endl;
			show_outside_menu();
			break;
		}
	}
	
	cleanup();
	return (0);
}

void init()
{
	int choice;
	string name;

	running = 1;
	player.setlocation(PUB);
	cout << "You wake up with a headache trying to remember eveything..." << endl;
	cout << "What is your name? ";
	cin >> name;
	player.setname(name);

	cout << "And you are a ..." << endl;
	cout << "1. Warrior" << endl;
	cout << "2. Mage" << endl;
	cout << "3. Ranger" << endl;
	do {
		cin >> choice;
	} while (choice < 1 || choice > 3);

	// Inital stats
	switch (choice) {
	case 1:
		player.setclass(WARRIOR);
		player.setmaxhp(50);
		player.setmaxsp(10);
		player.setminatk(20);
		player.setmaxatk(25);
		break;
	case 2:
		player.setclass(MAGE);
		player.setmaxhp(20);
		player.setmaxsp(30);
		player.setminatk(5);
		player.setmaxatk(10);
		break;
	case 3:
		player.setclass(RANGER);
		player.setmaxhp(25);
		player.setmaxsp(5);
		player.setminatk(30);
		player.setmaxatk(40);
		break;
	}

	// Seeding the random number generator for encounters
	srand(time(NULL));

	cout << endl;
}

void cleanup()
{

}

void view_stats()
{
	cout << "Your stats:" << endl;
	cout << "Name: " << player.getname() << endl;
	cout << "Class: " << player.getclass() << endl;
	cout << "Level: " << player.getlevel() << endl;
	cout << "Exp: " << player.getexp() << "/100" << endl;
	cout << "HP: " << player.gethp() << "/" << player.getmaxhp() << endl;
	cout << "SP: " << player.getsp() << "/" << player.getmaxsp() << endl;
	cout << "Attack: " << player.getminatk() << "-" << player.getmaxatk() << endl;
//	cout << "Defense: " << player.def << endl;

	cout << endl;
}

void show_pub_menu()
{
	int choice;
	cout << EXPLORE_CHOICE << ". Explore outside" << endl;
	cout << BUY_CHOICE << ". Buy items" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do? ";

	do {
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case EXPLORE_CHOICE:
		player.setlocation(OUTSIDE);
		break;
	case BUY_CHOICE:
		break;
	case STAT_CHOICE:
		view_stats();
		break;
	case EXIT_CHOICE:
		running = 0;
		break;
	}

	cout << endl;
}

void show_outside_menu()
{
	int choice;
	
	cout << PUB_CHOICE << ". Go back to the pub" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do? ";

	do {
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case PUB_CHOICE:
		player.setlocation(PUB);
		break;
	case STAT_CHOICE:
		view_stats();
		break;
	case EXIT_CHOICE:
		running = 0;
		break;
	}

	cout << endl;
}

void random_encounter()
{

}