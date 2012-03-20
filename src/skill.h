#ifndef SKILL_H
#define SKILL_H
#include <string>
#include <list>
#include "main.h"

using std::string;
using std::list;

class skill
{
	public:
		skill(list<mods*>* pm, list<effects*>* pe, list<mods*>* em, list<effects*>* ee, unsigned short id,
				unsigned short sp, enum skill_type t, enum class_system c, string* n, string* desc, skill* sk);
		~skill();

		unsigned short getdamage() const {return (init_damage);};

	private:
		// Player mods:
		list<mods*>* pl_mods;
		list<effects*>* pl_effects;

		// Enemy mods:
		list<mods*>* en_mods;
		list<effects*>* en_effects;

		unsigned short init_damage, sp_cost;

		enum skill_type type;
		enum class_system cs;
		string name, description;
		skill* nextlevel;
};
#endif