#include "character.h"
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

character::character()
	: name("New Player"),
		maxhp(1),
		hp(1),
		maxsp(1),
		sp(1),
		maxatk(1),
		minatk(1),
		def(1),
		maxexp(100),
		exp(0),
		turn(1),
		level(1),
		dodge(1),
		gold(1)
{

}

string character::getstringclass() const
{
	if (type == WARRIOR)
		return("Warrior");
	else if (type == MAGE)
		return("Mage");
	else if (type == RANGER)
		return("Ranger");
	else if (type == ENEMY)
		return("Enemy");
	else
		return("Unknown");
}

bool character::isdead() const
{
	if (hp == 0)
		return(true);

	return(false);
}

void character::attack(character &e)
{
	int d = rand() % (maxatk - minatk) + minatk;
	e.receivedamage(d);
}

void character::receivedamage(const unsigned short damage)
{
	int d = rand() % 100;
	cout << name;
	if (d > dodge) {
		if (damage > hp)
			hp = 0;
		else
			hp -= damage;

		cout << " took " << damage << " damage!" << endl;
	}
	else {
		cout << " avoided the attack!" << endl;
	}
}

bool character::levelup(const short ex)
{
	if (exp + ex < 0) {
		exp = 0;
	} else if (exp + ex >= maxexp) {
		level++;
		exp += ex - maxexp;
		return (true);
	} else {
		exp += ex;
	}
	return (false);
}

void character::heal(const unsigned short h)
{
	if (h >= maxhp)
		hp = maxhp;
	else
		hp += h;
}

bool character::usegold(unsigned int g)
{
	if (g > gold)
		return (false);
	else
		gold -= g;

	return (true);
}