#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "main.h"

using std::string;

class skill
{
	public:
		skill(unsigned short h, unsigned short s, unsigned short a,
				unsigned short d, unsigned short e,
				unsigned char t, unsigned char n,
				unsigned char dd, unsigned char l,
				unsigned short dm, unsigned short sp,
				string nm, string desc);
	private:
		// Stat mods:
		unsigned short hp, sp, atk, def, expgain;
		unsigned char turn, numatk, dodge, level;

		// Immediate effect and cost
		unsigned short damage, spcost;

		enum skill_type type;
		string name, description;
};
#endif