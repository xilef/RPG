#ifndef SKILL_M_H
#define SKILL_M_H
#include "skill.h"
#include <map>
#include <vector>
#include <utility>

using std::map;
using std::vector;
using std::pair;

typedef map<const string, skill*> skillMap;

class skillManager
{
	public:
		skillMap skillList;
		~skillManager();
		vector<pair<const string, skill*>*> getSkillList(const enum classSystem &cl);
};
#endif