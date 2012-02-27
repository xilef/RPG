#ifndef SKILL_H
#define SKILL_H
#include <string>
#include "main.h"

using std::string;

class skill
{
	public:
		skill(struct mods& p, struct mods& e,
				unsigned short idm, unsigned short cdm, unsigned short sp,
				enum skill_type st, string nm, string desc, skill* sk = NULL);
	private:
		// Player mods:
		struct mods pl_mods;

		// Enemy mods:
		struct mods en_mods;
		unsigned short init_damage, spcost;

		enum skill_type sk_type;
		string name, description;
		skill* nextlevel;
};
#endif