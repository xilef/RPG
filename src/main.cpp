// A very simple Text based RPG
// written by Felix Isaac Palomares

#include <iostream>
#include <string>
#include <stdlib.h>
#include <limits>
#include "character.h"

// Pub menu choices
#define EXPLORE_CHOICE 1
#define REST_CHOICE 2
#define BUY_CHOICE 3
#define STAT_CHOICE 4
#define EXIT_CHOICE 5

// Outside menu choices
#define MOVE_CHOICE 1
#define PUB_CHOICE 2

//Attack menu choices
#define ATTACK_CHOICE 1
#define ITEM_CHOICE 2
#define RUN_CHOICE 3

#define ENEMY_CHANCE 60

using namespace::std;

bool running;
character player;

void init();
void cleanup();
void view_full_stats(character &ch);
void view_stats(character &ch);
void show_pub_menu();
void show_outside_menu();
void random_encounter();
void fight(character &enemy);

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

	running = true;
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
		player.setturn(2);
		break;
	}

	// Seeding the random number generator for encounters
	srand(time(NULL));

	cout << endl;
}

void cleanup()
{

}

void view_full_stats(character &ch)
{
	cout << endl;
	cout << "Name: " << ch.getname() << endl;
	cout << "Class: " << ch.getstringclass() << endl;
	cout << "Level: " << (int)ch.getlevel() << endl;
	cout << "Exp: " << (int)ch.getexp() << "/100" << endl;
	cout << "HP: " << ch.gethp() << "/" << ch.getmaxhp() << endl;
	cout << "SP: " << ch.getsp() << "/" << ch.getmaxsp() << endl;
	cout << "Attack: " << ch.getminatk() << "-" << ch.getmaxatk() << endl;
	cout << endl;
}

void view_stats(character &ch)
{
	cout << "Name: " << ch.getname() << endl;
	cout << "HP: " << ch.gethp() << "/" << ch.getmaxhp() << endl;
	cout << "SP: " << ch.getsp() << "/" << ch.getmaxsp() << endl;
	cout << endl;
}

void show_pub_menu()
{
	int choice;
	cout << EXPLORE_CHOICE << ". Explore outside" << endl;
	cout << REST_CHOICE << ". Rest" << endl;
	cout << BUY_CHOICE << ". Buy items" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do? ";

	do {
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case EXPLORE_CHOICE:
		cout << endl << "Going outside" << endl;
		player.setlocation(OUTSIDE);
		break;
	case REST_CHOICE:
		cout << endl << "You slept and is now refreshed" << endl;
		player.rest();
		break;
	case BUY_CHOICE:
		break;
	case STAT_CHOICE:
		cout << endl << "Your stats" << endl;
		view_full_stats(player);
		break;
	case EXIT_CHOICE:
		running = false;
		break;
	}

	cout << endl;
}

void show_outside_menu()
{
	int choice;

	cout << MOVE_CHOICE << ". Move" << endl;
	cout << PUB_CHOICE << ". Go back to the pub" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do? ";

	do {
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case MOVE_CHOICE:
		random_encounter();
		break;
	case PUB_CHOICE:
		cout << endl << "Going to the pub" << endl;
		player.setlocation(PUB);
		break;
	case STAT_CHOICE:
		cout << endl << "Your stats" << endl;
		view_full_stats(player);
		break;
	case EXIT_CHOICE:
		running = false;
		break;
	}

	cout << endl;
}

void random_encounter()
{
	int i = rand() % 100;
	unsigned char level = player.getlevel();

	if (i <= ENEMY_CHANCE) {
		character enemy;
		enemy.setname("Ogre");
		enemy.setclass(ENEMY);
		enemy.setmaxhp(28 + (7 + level * 5));
		enemy.setmaxsp(10 + (2 * level));
		enemy.setminatk(24 + (1.5 * level));
		enemy.setmaxatk(29 + (1.5 * level));
		enemy.setlevel(level);
		fight(enemy);
	}
}

void fight(character &enemy)
{
	int choice;
	unsigned char pturn, eturn;
	unsigned short damage;
	bool escape = false;

	pturn = player.getturn();
	eturn = enemy.getturn();

	cout << "An enemy has appeared!" << endl;
	while (!player.isdead() && !enemy.isdead() && !escape) {
		view_stats(player);
		view_stats(enemy);

		if (pturn > 0) {
			cout << ATTACK_CHOICE << ". Attack" << endl;
			cout << ITEM_CHOICE << ". Use an item" << endl;
			cout << RUN_CHOICE << ". Run away" << endl;
			cout << "What do you want to do? ";

			do {
				cin >> choice;
			} while (choice < 1 || choice > RUN_CHOICE);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (choice) {
			case ATTACK_CHOICE:
				cout << "You attacked " << enemy.getname() << "!" << endl;
				damage = player.attack(enemy);
				cout << enemy.getname() << " received " << damage << " damage" << endl;
				break;
			case ITEM_CHOICE:
				break;
			case RUN_CHOICE:
				escape = true;
				break;
			}
			cin.get();

			pturn--;
			if (eturn == 0) 
				eturn++;
		} else if (eturn > 0) {
			cout << enemy.getname() << " attacks you!" << endl;
			damage = enemy.attack(player);
			cout << "You received " << damage << " damage" << endl;

			cin.get();

			eturn--;
			if (pturn == 0) 
				pturn++;
		}
	}

	if (enemy.isdead()) {
		cout << enemy.getname() << " defeated!" << endl;
		cout << "You received " << enemy.getmaxhp() << " exp" << endl;

		if (player.levelup(enemy.getmaxhp())) {
			cout << "You leveled-up!" << endl;
			view_full_stats(player);
		}
	} else if (player.isdead()) {
		cout << "You died!" << endl;
		player.setlocation(PUB);
		player.rest();
	} else if (escape)
		cout << "Escaped!" << endl;

	cout << endl;
}