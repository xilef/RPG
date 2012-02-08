#include "character.h"
#include <stdlib.h>

character::character()
	: name("New Player"),
		maxhp(1),
		hp(1),
		maxsp(1),
		sp(1),
		minatk(1),
		maxatk(1),
		def(1),
		exp(0),
		maxexp(100),
		turn(1),
		level(1),
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

unsigned short character::attack(character &e) const
{
	int d = rand() % (maxatk - minatk) + minatk;
	e.receivedamage(d);

	return (d);
}

void character::receivedamage(const unsigned short damage)
{
	if (damage > hp)
		hp = 0;
	else
		hp -= damage;
}

bool character::levelup(const unsigned short ex)
{
	if (exp + ex >= maxexp) {
		level++;
		exp += ex - maxexp;
		return (true);
	} else {
		exp += ex;
		return (false);
	}
}