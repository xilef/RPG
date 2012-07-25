#include "skill.h"

skill::skill(list<mods>* pm, list<effects>* pe, list<mods>* em, list<effects>* ee, unsigned short id,
				unsigned short sp, unsigned char l, enum skillType t, enum classSystem c, string* n, string* desc)
			:playerMods(pm), playerEffects(pe), enemyMods(em), enemyEffects(ee),
				initDamage(id), spCost(sp), level(l), type(t), cs(c), name(*n), description(*desc)
{

}

skill::~skill()
{
	delete playerMods;
	delete enemyMods;
	delete playerEffects;
	delete enemyEffects;
}