#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "main.h"

using std::string;

class character
{
	public:
		character();

		string getname() const {return(name);};
		unsigned short getmaxhp() const {return(maxhp);};
		unsigned short gethp() const {return(hp);};
		unsigned short getmaxsp() const {return(maxsp);};
		unsigned short getsp() const {return(sp);};
		unsigned short getminatk() const {return(minatk);};
		unsigned short getmaxatk() const {return(maxatk);};
		unsigned short getexp() const {return(exp);};
		unsigned short getmaxexp() const {return(maxexp);};
		unsigned char getlevel() const {return(level);};
		unsigned char getturn() const {return(turn);};
		unsigned char getdodge() const {return(dodge);};
		unsigned int getgold() const {return(gold);};
		string getstringclass() const;
		enum location getlocation() const {return(loc);};
		enum class_system getclass() const {return(type);};

		void setname(const string &n) {name = n;};
		void setmaxhp(const unsigned short h) {maxhp = hp = h;};
		void setmaxsp(const unsigned short s) {maxsp = sp = s;};
		void setminatk(const unsigned short min) {minatk = min;};
		void setmaxatk(const unsigned short max) {maxatk = max;};
		void setmaxexp(const unsigned short maxep) {maxexp = maxep;};
		void setclass(const enum class_system &c) {type = c;};
		void setlocation(const enum location &l) {loc = l;};
		void setlevel(const unsigned char l) {level = l;};
		void setturn(const unsigned char t) {turn = t;};
		void setdodge(const unsigned char d) {dodge = d;};
		void setgold(const unsigned int g) {gold = g;};

		void heal(const unsigned short h);
		void attack(character &e);
		void receivedamage(const unsigned short damage);
		bool levelup(const short ex);
		bool isdead() const;
		bool usegold(unsigned int g);
		void addgold(unsigned int g) {gold += g;};

	private:
		unsigned short maxhp, hp, maxsp, sp, maxatk, minatk, def, maxexp, exp;
		unsigned char turn, level, dodge;
		unsigned int gold;
		enum class_system type;
		enum location loc;
		string name;
};
#endif