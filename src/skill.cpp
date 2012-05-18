#include "skill.h"

skill::skill(list<mods*>* pm, list<effects*>* pe, list<mods*>* em, list<effects*>* ee, unsigned short id,
				unsigned short sp, unsigned char l, enum skillType t, enum classSystem c, string* n, string* desc)
			:playerMods(pm), playerEffects(pe), enemyMods(em), enemyEffects(ee),
				initDamage(id), spCost(sp), level(l), type(t), cs(c), name(*n), description(*desc)
{

}

skill::~skill()
{
	mods* m;
	effects* e;

	if (playerMods != NULL) {
		while (!playerMods->empty()) {
			m = playerMods->front();
			delete m;
			playerMods->pop_front();
		}
		delete playerMods;
	}

	if (enemyMods != NULL) {
		while (!enemyMods->empty()) {
			m = enemyMods->front();
			delete m;
			enemyMods->pop_front();
		}
		delete enemyMods;
	}

	if (playerEffects != NULL) {
		while (!playerEffects->empty()) {
			e = playerEffects->front();
			delete e;
			playerEffects->pop_front();
		}
		delete playerEffects;
	}

	if (enemyEffects != NULL) {
		while (!enemyEffects->empty()) {
			e = enemyEffects->front();
			delete e;
			enemyEffects->pop_front();
		}
		delete enemyEffects;
	}
}