#include "character.h"
#include <stdlib.h>
#include <iostream>
#include <climits>

using std::cout;
using std::endl;

character::character()
	:  currentHp(1), currentSp(1), maxHp(1), maxSp(1), maxAtk(1), minAtk(1),
		dodge(1), maxExp(100), exp(0), skillPt(1), turn(1), level(1), gold(1),
		name("New Player")
{

}

string character::getStringClass() const
{
	if (type == WARRIOR)
		return ("Warrior");
	else if (type == MAGE)
		return ("Mage");
	else if (type == RANGER)
		return ("Ranger");
	else if (type == ENEMY)
		return ("Enemy");
	else
		return ("Unknown");
}

bool character::isDead() const
{
	return (currentHp == 0);
}

void character::attack(character &e)
{
	int dmg = rand() % (maxAtk - minAtk) + minAtk;
	e.receiveDamage(dmg);
}

void character::receiveDamage(const unsigned short damage)
{
	int d = rand() % 100;
	cout << name;
	if (d > dodge) {
		if (damage > currentHp)
			currentHp = 0;
		else
			currentHp -= damage;

		cout << " took " << damage << " damage!" << endl;
	}
	else {
		cout << " avoided the attack!" << endl;
	}
}

bool character::levelUp(const short ex)
{
	if (exp + ex < 0) {
		exp = 0;
	} else if (exp + ex >= maxExp) {
		level++;
		exp += ex - maxExp;
		return (true);
	} else {
		exp += ex;
	}
	return (false);
}

void character::heal(const unsigned short h)
{
	if (h >= maxHp)
		currentHp = maxHp;
	else
		currentHp += h;
}

bool character::useGold(unsigned int g)
{
	if (g > gold) {
		cout << "Not enough gold!" << endl;
		return (false);
	} else {
		gold -= g;
	}

	return (true);
}

bool character::useSp(unsigned short s)
{
	if (s > currentSp) {
		cout << "Not enough SP!" << endl;
		return (false);
	} else {
		currentSp -= s;
	}
	
	return (true);
}