#include "character.h"

character::character()
	: name("New Player"),
		maxhp(1),
		hp(1),
		maxsp(1),
		sp(1),
		minatk(1),
		maxatk(1),
		def(1),
		turn(1),
		exp(0),
		level(1),
		gold(1)
{

}

string character::getclass() const
{
	if (type == WARRIOR)
		return ("Warrior");
	else if (type == MAGE)
		return ("Mage");
	else if (type == RANGER)
		return ("Ranger");
	else
		return ("Unknown");
}