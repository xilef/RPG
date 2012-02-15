#include "skill.h"

skill::skill(short h, short s, short a, short d, short e,
				char t, char n, char dd, char l, short idm,
				short cdm, short sp, enum skill_type st, enum class_system cs,
				string nm, string desc, skill* sk)
	: hp(h), sp(s), atk(a), def(d), expgain(e), turn(t), numatk(n),
		dodge(dd), level(l), init_damage(idm), cons_damage(cdm), spcost(sp),
		sk_type(st), sk_class(cs), name(nm), description(desc), nextlevel(sk)
{
}