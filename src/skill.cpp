#include "skill.h"

skill::skill(struct mods& p, struct mods& e
				unsigned short idm, unsigned short cdm, unsigned short sp,
				enum skill_type st, string nm, string desc, skill* sk = NULL);
	: pl_mods(p), en_mods(e), init_damage(idm), cons_damage(cdm), spcost(sp),
		sk_type(st), name(nm), description(desc), nextlevel(sk)
{
}