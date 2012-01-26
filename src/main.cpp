// A very simple Text based RPG
// written by Felix Isaac Palomares

#include <iostream>
#include <string>
#include "character.h"

using namespace::std;

int running;
character player, enemy;

void init();
void cleanup();
void view_stats();

int main()
{
	init();
	while (running) {
	
	}
	return (0);
}

void init()
{
	int choice;

	running = 1;
	cout << "The story starts here" << endl << endl;
	cout << "You are a ..." << endl;
	cout << "1. Warrior" << endl;
	cout << "2. Mage" << endl;
	cout << "3. Ranger" << endl;
	do {
		cin >> choice;
	} while (choice < 1 || choice > 3);
	
	switch (choice) {
	case 1:
		cout << "Warrior class" << endl;
		break;
	case 2:
		cout << "Mage class" << endl;
		break;
	case 3:
		cout << "Ranger class" << endl;
		break;
	}
	
	view_stats();
}

void cleanup()
{

}

void view_stats()
{
	cout << "Name: " << player.getname() << endl;
/*	cout << player.hp << "/" << player.maxhp << endl;
	cout << player.sp << "/" << player.maxsp << endl;
	cout << "Attack: " << player.atk << endl;
	cout << "Defense: " << player.def << endl;*/
}
