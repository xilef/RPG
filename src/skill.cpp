#include "skill.h"

skill::skill(unsigned short h, unsigned short s, unsigned short a,
				unsigned short d, unsigned short e,
				unsigned char t, unsigned char n,
				unsigned char dd, unsigned char l,
				unsigned short dm, unsigned short sp,
				string nm, string desc)
	: hp(h), sp(s), atk(a), def(d), expgain(e), turn(t), numatk(n),
		dodge(dd), level(l), damage(dm), spcost(sp), type(PASSIVE),
		name(nm), description(desc)
{
}