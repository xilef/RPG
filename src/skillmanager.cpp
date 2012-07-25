#include "skillmanager.h"
#include <iostream>
using namespace::std;
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

vector<skillKey> skillManager::getSkillList(const enum classSystem &cl)
{
	skillMap::iterator it;
	vector<skillKey> list;

	for (it = skillList.begin(); it != skillList.end(); it++) {
		if (it->second->cs == cl && it->second->level == 0)
			list.push_back(it->first);
	}

	return (list);
}

void skillManager::addSkill(skill *sk)
{
	skillKey key (sk->name, sk->level);
	skillList[key] = sk;
}

bool skillManager::exists(const string &name, const unsigned char level) const
{
	skillKey search(name, level);
	if (!skillList.empty()) {
		if (skillList.find(search) != skillList.end())
			return true;
	}
	
	return false;
}

skill * skillManager::getSkill(const skillKey search) const
{
	if (skillList.find(search) != skillList.end())
		return skillList.find(search)->second;

	return NULL;
}