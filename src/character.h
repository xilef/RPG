#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include <list>
#include "main.h"
#include "skill.h"

using std::string;
using std::list;

class character
{
	public:
		character();

		string getname() const {return (name);};
		unsigned short getmaxhp() const {return (maxhp);};
		unsigned short gethp() const {return (curr_hp);};
		unsigned short getmaxsp() const {return (maxsp);};
		unsigned short getsp() const {return (curr_sp);};
		unsigned short getminatk() const {return (minatk);};
		unsigned short getmaxatk() const {return (maxatk);};
		unsigned short getexp() const {return (exp);};
		unsigned short getmaxexp() const {return (maxexp);};
		unsigned short getdodge() const {return (dodge);};
		unsigned char getlevel() const {return (level);};
		unsigned char getturn() const {return (turn);};
		unsigned int getgold() const {return (gold);};
		string getstringclass() const;
		enum location getlocation() const {return (loc);};
		enum class_system getclass() const {return (type);};

		void setname(const string &n) {name = n;};
		void setmaxhp(const unsigned short h) {maxhp = curr_hp = h;};
		void setmaxsp(const unsigned short s) {maxsp = curr_sp = s;};
		void setminatk(const unsigned short min) {minatk = min;};
		void setmaxatk(const unsigned short max) {maxatk = max;};
		void setmaxexp(const unsigned short maxep) {maxexp = maxep;};
		void setdodge(const unsigned short d) {dodge = d;};
		void setclass(const enum class_system &c) {type = c;};
		void setlocation(const enum location &l) {loc = l;};
		void setlevel(const unsigned char l) {level = l;};
		void setturn(const unsigned char t) {turn = t;};
		void setgold(const unsigned int g) {gold = g;};

		void heal(const unsigned short h);
		void attack(character &e);
		void useskill(skill &sk, character &e);
		void receivedamage(const unsigned short damage);
		bool levelup(const short ex);
		bool isdead() const;
		bool usegold(unsigned int g);
		void addgold(unsigned int g) {gold += g;};

	private:
		unsigned short base_maxhp, base_maxsp, base_maxatk, base_minatk, base_def, base_dodge;
		unsigned short curr_hp, curr_sp, maxhp, maxsp, maxatk, minatk, curr_def, dodge;
		unsigned short maxexp, exp;
		unsigned char skill_pt, turn, level, mods_count;
		unsigned int gold;
		enum class_system type;
		enum location loc;
		string name;
		list<skill*> skills;
};
#endif