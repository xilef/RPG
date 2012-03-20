#include "skill.h"

skill::skill(list<mods*>* pm, list<effects*>* pe, list<mods*>* em, list<effects*>* ee, unsigned short id,
				unsigned short sp, enum skill_type t, enum class_system c, string* n, string* desc, skill* sk)
			:pl_mods(pm), pl_effects(pe), en_mods(em), en_effects(ee),
				init_damage(id), sp_cost(sp), type(t), cs(c), name(*n), description(*desc), nextlevel(sk)
{

}

skill::~skill()
{
	mods* m;
	effects* e;

	if (pl_mods != NULL) {
		while (!pl_mods->empty()) {
			m = pl_mods->front();
			delete m;
			pl_mods->pop_front();
		}
		delete pl_mods;
	}

	if (en_mods != NULL) {
		while (!en_mods->empty()) {
			m = en_mods->front();
			delete m;
			en_mods->pop_front();
		}
		delete en_mods;
	}

	if (pl_effects != NULL) {
		while (!pl_effects->empty()) {
			e = pl_effects->front();
			delete e;
			pl_effects->pop_front();
		}
		delete pl_effects;
	}

	if (en_effects != NULL) {
		while (!en_effects->empty()) {
			e = en_effects->front();
			delete e;
			en_effects->pop_front();
		}
		delete en_effects;
	}
	
	if (nextlevel != NULL)
		delete nextlevel;
}