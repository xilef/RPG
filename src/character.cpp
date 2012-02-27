#include "character.h"
#include <stdlib.h>
#include <iostream>

using std::cout;
using std::endl;

character::character()
	: maxhp(1), maxsp(1), maxatk(1), minatk(1), curr_hp(1), curr_sp(1),
		maxexp(100), exp(0), turn(1), level(1), mods_count(0), dodge(1), gold(1),
		name("New Player")
{

}

string character::getstringclass() const
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

bool character::isdead() const
{
	if (hp == 0)
		return (true);

	return (false);
}

void character::attack(character &e)
{
	int dmg = rand() % (maxatk - minatk) + minatk;
	e.receivedamage(dmg);
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

void character::useskill(skill &sk, character &e)
{
	e.receivedamage(sk.getdamage());
}

void character:applymods(mods &mod)
{
	maxhp += base_maxhp * (mod.hp / 100);
	maxsp += base_maxsp * (mod.sp / 100);
	minatk += base_minatk * (mod.atk / 100);
	maxatk += base_maxatk * (mod.atk / 100);
	dodge += base_dodge * (mod.dodge / 100);

	current_mods[mod_count] = mod;
	mod_count = (++mod_count) % 5;
}

void character::removemods(unsigned char mod_num)
{
	int x;
	
	for (x = mod_num; x < 4; x++)
		current_mods[x] = current_mods[x + 1];

	current_mods[4] = NULL;

	mod_count = (--mod_count) % 5;
}