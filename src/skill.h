#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "main.h"

using std::string;

class skill
{
	public:
		skill(short h, short s, short a, short d, short e,
				char t, char n, char dd, char l, short idm,
				short cdm, short sp, enum skill_type st, enum class_system cs,
				string nm, string desc, skill* sk = NULL);
	private:
		// Stat mods:
		unsigned short hp, sp, atk, def, expgain;
		unsigned char turn, numatk, dodge, level;

		// Immediate effect and cost
		unsigned short init_damage, cons_damage, spcost;

		enum skill_type sk_type;
		enum class_system sk_class;
		string name, description;
		skill* nextlevel;
};
#endif