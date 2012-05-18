#ifndef SKILL_M_H
#define SKILL_M_H
#include "skill.h"
#include <map>
#include <vector>
#include <utility>

using std::map;
using std::vector;
using std::pair;

typedef pair<string, unsigned char> skillKey;
typedef map<skillKey, skill *> skillMap;

class skillManager
{
	private:
		skillMap skillList;

	public:
		~skillManager();
		void addSkill(skill *sk);
		vector<skillKey> getSkillList(const enum classSystem &cl);
		bool exists(const string &name, const unsigned char level) const;
		skill * getSkill(const skillKey search) const;
		
};
#endif