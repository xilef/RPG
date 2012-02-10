#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

using std::string;

enum class_system {WARRIOR, MAGE, RANGER, ENEMY};
enum location {OUTSIDE, PUB};

class character
{
	public:
		character();

		inline string getname() const {return(name);};
		inline unsigned short getmaxhp() const {return(maxhp);};
		inline unsigned short gethp() const {return(hp);};
		inline unsigned short getmaxsp() const {return(maxsp);};
		inline unsigned short getsp() const {return(sp);};
		inline unsigned short getminatk() const {return(minatk);};
		inline unsigned short getmaxatk() const {return(maxatk);};
		inline unsigned short getexp() const {return(exp);};
		inline unsigned short getmaxexp() const {return(maxexp);};
		inline unsigned char getlevel() const {return(level);};
		inline unsigned char getturn() const {return(turn);};
		inline unsigned int getgold() const {return(gold);};
		string getstringclass() const;
		inline enum location getlocation() const {return(loc);};
		inline enum class_system getclass() const {return(type);};

		inline void setname(const string &n) {name = n;};
		inline void setmaxhp(const unsigned short h) {maxhp = hp = h;};
		inline void setmaxsp(const unsigned short s) {maxsp = sp = s;};
		inline void setminatk(const unsigned short min) {minatk = min;};
		inline void setmaxatk(const unsigned short max) {maxatk = max;};
		inline void setmaxexp(const unsigned short maxep) {maxexp = maxep;};
		inline void setclass(const enum class_system &c) {type = c;};
		inline void setlocation(const enum location &l) {loc = l;};
		inline void setlevel(const unsigned char l) {level = l;};
		inline void setturn(const unsigned char t) {turn = t;};
		inline void setgold(const unsigned int g) {gold = g;};

		void heal(const unsigned short h);
		void attack(character &e);
		void receivedamage(const unsigned short damage);
		bool levelup(const short ex);
		bool isdead() const;
		bool usegold(unsigned int g);
		inline void addgold(unsigned int g) {gold += g;};

	private:
		string name;
		enum class_system type;
		enum location loc;
		unsigned short maxhp, hp, maxsp, sp, maxatk, minatk, def, maxexp, exp;
		unsigned char turn, level;
		unsigned int gold;
};
#endif