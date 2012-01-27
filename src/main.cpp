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
	string name;

	running = 1;
	cout << "You wake up with a headache trying to remember your name..." << endl;
	cout << "What is your name? ";
	cin >> name;
	player.setname(name);

	cout << "You are a ..." << endl;
	cout << "1. Warrior" << endl;
	cout << "2. Mage" << endl;
	cout << "3. Ranger" << endl;
	do {
		cin >> choice;
	} while (choice < 1 || choice > 3);
	
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
	
	view_stats();
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
}
