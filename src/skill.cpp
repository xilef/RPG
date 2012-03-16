#include "skill.h"

skill::skill(list<mods*>* pm, list<effects*>* pe, list<mods*>* em, list<effects*>* ee, unsigned short id,
				unsigned short sp, enum skill_type t, string* n, string* desc, skill* sk)
			:init_damage(id), sp_cost(sp), type(t), name(*n), description(*desc), nextlevel(sk)
{
	if (pm != NULL)
		pl_mods = *pm;

	if (pe != NULL)
		pl_effects = *pe;

	if (em != NULL)
		en_mods = *em;

	if (ee != NULL)
		en_effects = *ee;
}