// A very simple Text based RPG
// written by Felix Isaac Palomares
//
// TODO:
// 		Skill usage in the main game

#include "main.h"
#include "character.h"
#include "skill.h"
#include <iostream>
#include <string>
#include <map>
#include <stdlib.h>
#include <limits>

using namespace::std;

bool running;
character player;
map<string, skill*> skill_list;

void init();
void change_class(character &p, int choice);
void init_skills();
void cleanup();
void view_full_stats(const character &ch);
void view_stats(const character &ch);
void show_pub_menu();
void show_outside_menu();
void random_encounter();
void fight(character &enemy);
void increase_stats(character &p);
void make_enemy(character &e, const unsigned char level);

int main()
{
	init();

	while (running) {
		switch (player.getlocation()) {
		case PUB:
			show_pub_menu();
			break;
		case OUTSIDE:
			show_outside_menu();
			break;
		}
	}

	cleanup();
	return (0);
}

void init()
{
	int choice;
	string name;

	init_skills();

	running = true;
	player.setlocation(PUB);
	player.setgold(500);

	cout << "You wake up with a headache trying to remember eveything..." << endl;
	cout << "What is your name?" << endl << ": ";
	cin >> name;
	player.setname(name);

	cout << endl;
	cout << "1. Warrior" << endl;
	cout << "2. Mage" << endl;
	cout << "3. Ranger" << endl;
	cout << "And you are a ..." << endl;
	do {
		cout << ": ";
		cin >> choice;
	} while (choice < 1 || choice > 3);

	// Setup initial player stats
	change_class(player, choice);

	// Seed for the random encounters, dodge and skill hit chance
	srand(time(NULL));

	cout << endl;
}

void change_class(character &p, int choice)
{
	switch (choice) {
	case 1:
		p.setclass(WARRIOR);
		p.setmaxhp(50);
		p.setmaxsp(10);
		p.setminatk(20);
		p.setmaxatk(25);
		p.setdodge(30);
		break;
	case 2:
		p.setclass(MAGE);
		p.setmaxhp(20);
		p.setmaxsp(30);
		p.setminatk(5);
		p.setmaxatk(10);
		p.setdodge(40);
		break;
	case 3:
		p.setclass(RANGER);
		p.setmaxhp(30);
		p.setmaxsp(5);
		p.setminatk(13);
		p.setmaxatk(18);
		p.setturn(2);
		p.setdodge(60);
		break;
	}
}

void init_skills()
{
	skill* sk1, * sk2, * sk3;
	effects* temp_epl, * temp_een;
	mods* temp_mpl, * temp_men;
	string temp_name, temp_desc;
	list<mods*>* temp_pl_mods, * temp_en_mods;
	list<effects*>* temp_pl_effects, * temp_en_effects;

	// Warrior skills

	// Mage skills
	//	Hell Fire
	//	Level 1:
	//		init damage: 150
	//		sp cost: 10
	//		effect:
	//			consecutive damage: 25
	//			turns: 1
	//	Level 2:
	//		init damage: 250
	//		sp cost: 20
	//		effect:
	//			consecutive damage: 25
	//			turns: 2
	//	Level 3:
	//		init damage: 350
	//		sp cost: 30
	//		effect:
	//			consecutive damage: 35
	//			turns: 3

	// Level 3
	temp_name = "Hell Fire";
	temp_desc = "Burn your target with a incredible flame, the target recieve 100 damage and another 30 damage for the next 3 turns.";
	temp_epl = NULL;
	temp_een = new effects();
	temp_een->eff = CONSECUTIVE_DAMAGE;
	temp_een->val = 30;
	temp_een->turns = 3;
	temp_een->chance = 100;
	temp_mpl = NULL;
	temp_men = NULL;

	temp_pl_mods = NULL;
	temp_en_mods = NULL;
	temp_pl_effects = NULL;
	temp_en_effects = new list<effects*>;
	temp_en_effects->push_back(temp_een);

	sk3 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 100, 35, ACTIVE, MAGE,
					&temp_name, &temp_desc, NULL);

	// Level 2
	temp_desc = "Burn your target with a incredible flame, the target recieve 50 damage and another 20 damage for the next 2 turns.";
	temp_een = new effects();
	temp_een->eff = CONSECUTIVE_DAMAGE;
	temp_een->val = 20;
	temp_een->turns = 2;
	temp_een->chance = 100;
	temp_en_effects = new list<effects*>;
	temp_en_effects->push_back(temp_een);

	sk2 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 50, 25, ACTIVE, MAGE,
					&temp_name, &temp_desc, sk3);

	// Level 1
	temp_desc = "Burn your target with a incredible flame, the target recieve 20 damage and another 10 damage for the next turn.";
	temp_een = new effects();
	temp_een->eff = CONSECUTIVE_DAMAGE;
	temp_een->val = 10;
	temp_een->turns = 1;
	temp_een->chance = 100;
	temp_en_effects = new list<effects*>;
	temp_en_effects->push_back(temp_een);

	sk1 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 20, 15, ACTIVE, MAGE,
					&temp_name, &temp_desc, sk2);

	skill_list["Hell Fire"] = sk1;

	//	Frostbite
	//	Level 1:
	//		init damage: 10
	//		sp cost: 5
	//		mods:
	//			enemy atk: 20%
	//			turns: 1
	//	Level 2:
	//		init damage: 50
	//		sp cost: 20
	//		mods:
	//			enemy atk: 30%
	//			turns: 1
	//	Level 3:
	//		init damage: 150
	//		sp cost: 50
	//		mods:
	//			enemy atk: 60%
	//			turns: 1

	// Level 3
	temp_name = "Frostbite";
	temp_desc = "Freeze your target dealing 150 damage and the target attack will be reduced by 60% in the next turn.";
	temp_epl = NULL;
	temp_een = NULL;
	temp_mpl = NULL;
	temp_men = new mods();
	temp_men->stat = ATK;
	temp_men->val = 60;
	temp_men->turns = 1;
	temp_men->chance = 100;

	temp_pl_mods = NULL;
	temp_en_mods = new list<mods*>;
	temp_en_mods->push_back(temp_men);
	temp_pl_effects = NULL;
	temp_en_effects = NULL;

	sk3 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 150, 50, ACTIVE, MAGE,
					&temp_name, &temp_desc, NULL);

	// Level 2
	temp_desc = "Freeze your target dealing 50 damage and the target attack will be reduced by 30% in the next turn.";
	temp_men = new mods();
	temp_men->stat = ATK;
	temp_men->val = 30;
	temp_men->turns = 1;
	temp_men->chance = 100;
	temp_en_mods = new list<mods*>;
	temp_en_mods->push_back(temp_men);

	sk2 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 50, 20, ACTIVE, MAGE,
					&temp_name, &temp_desc, sk3);

	// Level 1
	temp_desc = "Freeze your target dealing 10 damage and the target attack will be reduced by 20% in the next turn.";
	temp_men = new mods();
	temp_men->stat = ATK;
	temp_men->val = 20;
	temp_men->turns = 1;
	temp_men->chance = 100;
	temp_en_mods = new list<mods*>;
	temp_en_mods->push_back(temp_men);

	sk1 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 10, 5, ACTIVE, MAGE,
					&temp_name, &temp_desc, sk2);

	skill_list["Frostbite"] = sk1;

	//	Thunder Burst
	//	Level 1:
	//		init damage: 20
	//		sp cost: 5
	//		effect:
	//			stun/knockback: 1
	//			chance: 20%
	//			turns: 0
	//	Level 2:
	//		init damage: 75
	//		sp cost: 20
	//		effect:
	//			stun/knockback: 1
	//			chance: 35%
	//			turns: 0
	//	Level 3:
	//		init damage: 175
	//		sp cost: 50
	//		effect:
	//			stun/knockback: 1
	//			chance: 50%
	//			turns: 0
	//
	//			hp drain: 35%
	//			chance: 50%
	//			turn: 0

	// Level 3
	temp_name = "Thunder Burst";
	temp_desc = "Call the force of thunder and lightning to hit the target dealing 175 damage, 50% chance of stunning the target and 50% chance of draining 35% of target's max hp.";
	temp_epl = NULL;
	temp_een = new effects();
	temp_een->eff = KNOCKBACK;
	temp_een->val = 1;
	temp_een->turns = 0;
	temp_een->chance = 50;
	temp_mpl = NULL;
	temp_men = NULL;

	temp_pl_mods = NULL;
	temp_en_mods = NULL;
	temp_pl_effects = NULL;
	temp_en_effects = new list<effects*>;
	temp_en_effects->push_back(temp_een);
	
	temp_een = new effects();
	temp_een->eff = HP_DRAIN;
	temp_een->val = 35;
	temp_een->turns = 0;
	temp_een->chance = 50;
	temp_en_effects->push_back(temp_een);

	sk3 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 175, 50, ACTIVE, MAGE,
					&temp_name, &temp_desc, NULL);

	// Level 2
	temp_desc = "Call the force of thunder and lightning to hit the target dealing 75 damage, 35% chance of stunning the target.";
	temp_een = new effects();
	temp_een->eff = KNOCKBACK;
	temp_een->val = 1;
	temp_een->turns = 0;
	temp_een->chance = 35;
	temp_en_effects = new list<effects*>;
	temp_en_effects->push_back(temp_een);

	sk2 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 75, 20, ACTIVE, MAGE,
					&temp_name, &temp_desc, sk3);

	// Level 1
	temp_desc = "Call the force of thunder and lightning to hit the target dealing 20 damage, 20% chance of stunning the target.";
	temp_een = new effects();
	temp_een->eff = KNOCKBACK;
	temp_een->val = 1;
	temp_een->turns = 0;
	temp_een->chance = 20;
	temp_en_effects = new list<effects*>;
	temp_en_effects->push_back(temp_een);

	sk1 = new skill(temp_pl_mods, temp_pl_effects, temp_en_mods, temp_en_effects, 20, 5, ACTIVE, MAGE,
					&temp_name, &temp_desc, sk2);

	skill_list["Thunder Burst"] = sk1;

	// Ranger skills

}

void cleanup()
{
	map<string, skill*>::iterator it;
	skill* sk;

/*	for (it = skill_list.begin(); it != skill_list.end(); it++) {
		sk = (*it).second;
		delete sk;
	}*/
	skill_list.clear();
}

void view_full_stats(character &ch)
{
	cout << endl;
	cout << "Name: " << ch.getname() << endl;
	cout << "Class: " << ch.getstringclass() << endl;
	cout << "Level: " << (int)ch.getlevel() << endl;
	cout << "Exp: " << ch.getexp() << "/" << ch.getmaxexp()<< endl;
	cout << "HP: " << ch.gethp() << "/" << ch.getmaxhp() << endl;
	cout << "SP: " << ch.getsp() << "/" << ch.getmaxsp() << endl;
	cout << "Attack: " << ch.getminatk() << "-" << ch.getmaxatk() << endl;
	cout << "Dodge: " << (int)ch.getdodge() << endl;
	cout << "Current gold: " << ch.getgold() << endl;
	cout << endl;
}

void view_stats(character &ch)
{
	cout << "Name: " << ch.getname() << endl;
	cout << "HP: " << ch.gethp() << "/" << ch.getmaxhp() << endl;
	cout << "SP: " << ch.getsp() << "/" << ch.getmaxsp() << endl;
	cout << endl;
}

void show_pub_menu()
{
	int choice;

	cout << "You are in the pub" << endl;
	cout << EXPLORE_CHOICE << ". Explore outside" << endl;
	cout << REST_CHOICE << ". Rest" << endl;
	cout << BUY_CHOICE << ". Buy items" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do?" << endl;

	do {
		cout << ": ";
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case EXPLORE_CHOICE:
		cout << endl << "Going outside" << endl;
		player.setlocation(OUTSIDE);
		break;
	case REST_CHOICE:
		if (player.usegold(REST_COST)) {
			cout << endl << "You slept and is now refreshed" << endl;
			player.heal(player.getmaxhp());
		} else {
			cout << endl << "Insufficient gold!" << endl;
		}
		break;
	case BUY_CHOICE:
		break;
	case STAT_CHOICE:
		cout << endl << "Your stats" << endl;
		view_full_stats(player);
		break;
	case EXIT_CHOICE:
		running = false;
		break;
	}

	cout << endl;
}

void show_outside_menu()
{
	int choice;

	cout << "You are outside exploring" << endl;
	cout << MOVE_CHOICE << ". Move" << endl;
	cout << PUB_CHOICE << ". Go back to the pub" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do?" << endl;

	do {
		cout << ": ";
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case MOVE_CHOICE:
		random_encounter();
		break;
	case PUB_CHOICE:
		cout << endl << "Going to the pub" << endl;
		player.setlocation(PUB);
		break;
	case STAT_CHOICE:
		cout << endl << "Your stats" << endl;
		view_full_stats(player);
		break;
	case EXIT_CHOICE:
		running = false;
		break;
	}

	cout << endl;
}

void random_encounter()
{
	int i = rand() % 100;
	unsigned char level = player.getlevel();

	if (i <= ENEMY_CHANCE) {
		character enemy;
		make_enemy(enemy, level);
		fight(enemy);
	}
}

void fight(character &enemy)
{
	int choice;
	unsigned int gold;
	unsigned short exp;
	unsigned char pturn, eturn;
	bool escape = false;

	pturn = player.getturn();
	eturn = enemy.getturn();
	exp = enemy.getmaxhp();
	gold = enemy.getgold();

	cout << endl;
	cout << "An enemy has appeared!" << endl;
	while (!player.isdead() && !enemy.isdead() && !escape) {
		view_stats(player);
		view_stats(enemy);

		if (pturn > 0) {
			cout << ATTACK_CHOICE << ". Attack" << endl;
			cout << ITEM_CHOICE << ". Use an item" << endl;
			cout << SKILL_CHOICE << ". Use a skill" << endl;
			cout << RUN_CHOICE << ". Run away" << endl;
			cout << "What do you want to do?" << endl;

			do {
				cout << ": ";
				cin >> choice;
			} while (choice < 1 || choice > RUN_CHOICE);
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			switch (choice) {
			case ATTACK_CHOICE:
				cout << endl << "You attacked " << enemy.getname() << "!" << endl;
				player.attack(enemy);
				cin.get();
				break;
			case ITEM_CHOICE:
				cin.get();
				break;
			case SKILL_CHOICE:
				cin.get();
				break;
			case RUN_CHOICE:
				escape = true;
				break;
			}

			// End player turn
			pturn--;
			if (eturn <= 0) 
				eturn++;
		} else if (eturn > 0) {
			cout << enemy.getname() << " attacks you!" << endl;
			enemy.attack(player);

			cin.get();

			// End enemy's turn
			eturn--;
			if (pturn <= 0) 
				pturn++;
		}
	}

	if (enemy.isdead()) {
		cout << enemy.getname() << " defeated!" << endl;
		cout << "You received " << exp << " exp" << endl;
		cout << "You received " << gold << " gold" << endl;

		player.addgold(gold);
		if (player.levelup(exp)) {
			cout << "You leveled-up!" << endl;
			increase_stats(player);
			view_full_stats(player);
		}
	} else if (player.isdead()) {
		cout << "You died!" << endl;
		cout << "Lost half of your gold and experience points!" << endl;
		player.levelup(-(player.getexp() / 2));
		player.setlocation(PUB);
		player.heal(player.getmaxhp());
	} else if (escape) {
		cout << "Escaped!" << endl;
	}

	cout << endl;
}

// Increase stats for the player
void increase_stats(character &p)
{
	unsigned short hp, sp, minatk, maxatk, maxexp;
	unsigned char level;
	hp = p.getmaxhp();
	sp = p.getmaxsp();
	minatk = p.getminatk();
	maxatk = p.getmaxatk();
	maxexp = p.getmaxexp();
	level = p.getlevel();

	maxexp += maxexp / 2;
	switch (p.getclass()) {
	case WARRIOR:
		hp += 10 + (7 * level);
		sp += 1.25 * level;
		minatk += 2 * level;
		maxatk += 2 * level;
		break;
	case MAGE:
		hp += 5 + (2.5 * level);
		sp += 3 * level;
		minatk += 0.75 * level;
		maxatk += 0.75 * level;
		break;
	case RANGER:
		hp += 5 + (3 * level);
		sp += 1.5 * level;
		minatk += 3 * level;
		maxatk += 3 * level;
		break;
	case ENEMY:
		break;
	}

	p.setmaxhp(hp);
	p.setmaxsp(sp);
	p.setminatk(minatk);
	p.setmaxatk(maxatk);
	p.setmaxexp(maxexp);
}

// Make enemy stats relative to player's current level
void make_enemy(character &e, const unsigned char level)
{
	unsigned char x;
	unsigned short hp, sp, minatk, maxatk;
	hp = 28;
	sp = 10;
	minatk = 24;
	maxatk = 29;

	for (x = 0; x < level; x++) {
		hp += 7 + (5 * level);
		sp += 10 + (2 * level);
		minatk += 1.5 * level;
		maxatk += 1.5 * level;
	}

	e.setname("Pikachu");
	e.setclass(ENEMY);
	e.setmaxhp(hp);
	e.setmaxsp(sp);
	e.setminatk(minatk);
	e.setmaxatk(maxatk);
	e.setlevel(level);
	e.setgold(50);
}