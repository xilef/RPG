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
				unsigned short sp, unsigned char l, enum skillType t, enum classSystem c, string* n, string* desc);
		~skill();

		unsigned short getDamage() const {return (initDamage);};
		unsigned short getSpCost() const {return (spCost);};
		unsigned char getLevel() const {return (level);};
		enum classSystem getClassType() const {return (cs);};
		string getName() const {return (name);};
		string getDescription() const {return (description);};

	private:
		// Player mods:
		list<mods*>* playerMods;
		list<effects*>* playerEffects;

		// Enemy mods:
		list<mods*>* enemyMods;
		list<effects*>* enemyEffects;

		unsigned short initDamage, spCost;
		unsigned char level;

		enum skillType type;
		enum classSystem cs;
		string name, description;

	friend class skillManager;
};
#endif