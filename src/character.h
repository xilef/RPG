#include <string>

using std::string;

class character
{
	private:
		int hp, sp, maxhp, maxsp, atk, def, turn, gold;
		string name;
		
	public:
		inline string getname() {return (name);};
		inline void setname(string n) {name = n;};
};
