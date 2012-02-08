#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>

using std::string;

enum class_system {WARRIOR, MAGE, RANGER};
enum location {OUTSIDE, PUB};

class character
{
	public:
		character();
		inline string getname() const {return (name);};
		inline unsigned short getmaxhp() const {return (maxhp);};
		inline unsigned short gethp() const {return (hp);};
		inline unsigned short getmaxsp() const {return (maxsp);};
		inline unsigned short getsp() const {return (sp);};
		inline unsigned short getlevel() const {return (level);};
		inline unsigned short getexp() const {return (exp);};
		inline unsigned short getminatk() const {return (minatk);};
		inline unsigned short getmaxatk() const {return (maxatk);};
		string getclass() const;
		enum location getlocation() const {return (loc);};

		inline void setname(const string &n) {name = n;};
		inline void setmaxhp(const unsigned short &h) {maxhp = hp = h;};
		inline void setmaxsp(const unsigned short &s) {maxsp = sp = s;};
		inline void setminatk(const unsigned short &min) {minatk = min;};
		inline void setmaxatk(const unsigned short &max) {maxatk = max;};
		inline void setclass(const enum class_system &c) {type = c;};
		inline void setlocation(const enum location &l) {loc = l;};
		
		void attack();

	private:
		string name;
		enum class_system type;
		enum location loc;
		unsigned short maxhp, hp, maxsp, sp, minatk, maxatk, def;
		unsigned char turn, exp, level;
		unsigned int gold;
};
#endif