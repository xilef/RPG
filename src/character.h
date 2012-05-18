#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <vector>
#include <utility>
#include "main.h"
#include "skillmanager.h"

using std::string;
using std::vector;
using std::pair;

class character
{
	public:
		character();

		string getName() const {return (name);};
		unsigned short getMaxHp() const {return (maxHp);};
		unsigned short getHp() const {return (currentHp);};
		unsigned short getMaxSp() const {return (maxSp);};
		unsigned short getSp() const {return (currentSp);};
		unsigned short getMinAtk() const {return (minAtk);};
		unsigned short getMaxAtk() const {return (maxAtk);};
		unsigned short getExp() const {return (exp);};
		unsigned short getMaxExp() const {return (maxExp);};
		unsigned short getDodge() const {return (dodge);};
		unsigned char getLevel() const {return (level);};
		unsigned char getTurn() const {return (turn);};
		unsigned char getSkillPt() const {return (skillPt);};
		unsigned int getGold() const {return (gold);};
		string getStringClass() const;
		enum location getLocation() const {return (loc);};
		enum classSystem getClass() const {return (type);};
		vector<skillKey>getSkillList() const {return (skills);};

		void setName(const string &n) {name = n;};
		void setMaxHp(const unsigned short h) {maxHp = currentHp = h;};
		void setMaxSp(const unsigned short s) {maxSp = currentSp = s;};
		void setMinAtk(const unsigned short min) {minAtk = min;};
		void setMaxAtk(const unsigned short max) {maxAtk = max;};
		void setMaxExp(const unsigned short maxep) {maxExp = maxep;};
		void setDodge(const unsigned short d) {dodge = d;};
		void setClass(const enum classSystem &c) {type = c;};
		void setLocation(const enum location &l) {loc = l;};
		void setLevel(const unsigned char l) {level = l;};
		void setTurn(const unsigned char t) {turn = t;};
		void setSkillPt(const unsigned char s) {skillPt = s;};
		void addSkillPt(const unsigned char s) {skillPt += s;};
		void setGold(const unsigned int g) {gold = g;};
		void setSkill(const vector<skillKey> sl) {skills = sl;};

		void heal(const unsigned short h);
		void attack(character &e);
		void receiveDamage(const unsigned short damage);
		bool levelUp(const short ex);
		bool isDead() const;
		bool useGold(unsigned int g);
		void addGold(unsigned int g) {gold += g;};

	private:
		unsigned short baseMaxHp, baseMaxSp, baseMaxAtk, baseMinAtk, baseDef, baseDodge;
		unsigned short currentHp, currentSp, maxHp, maxSp, maxAtk, minAtk, currentDef, dodge;
		unsigned short maxExp, exp;
		unsigned char skillPt, turn, level;
		unsigned int gold;
		enum classSystem type;
		enum location loc;
		string name;
		vector<skillKey> skills;
};
#endif