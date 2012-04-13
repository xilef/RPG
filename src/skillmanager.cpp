#include "skillmanager.h"

skillManager::~skillManager()
{
	skillMap::iterator it;
	skill* sk;

	for (it = skillList.begin(); it != skillList.end(); it++) {
		sk = it->second;
		delete sk;
	}
	skillList.clear();
}

vector<pair<const string, skill*>*> skillManager::getSkillList(const enum classSystem &cl)
{
	skillMap::iterator it;
	vector<pair<const string, skill*>*> list;

	for (it = skillList.begin(); it != skillList.end(); it++) {
		if (it->second->getClassType() == cl)
			list.push_back(&(*it));
	}

	return (list);
}