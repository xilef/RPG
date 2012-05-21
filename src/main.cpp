// A very simple Text based RPG
// written by Felix Isaac Palomares
//
// TODO:
// 		Skill usage in battle

#include "main.h"
#include "character.h"
#include "skill.h"
#include "skillmanager.h"
#include <iostream>
#include <utility>
#include <string>
#include <cstdlib>
#include <cctype>
#include <limits>
#include <typeinfo>

using namespace::std;

bool running;
character player;
skillManager skillMan;

void init();
void initPlayer(character &p, int choice);
void initSkills();
void useSkillPt(character &ch, const bool init);

void cleanup();

void viewFullStats(const character &ch);
void viewBattleStats(const character &ch);
void showPubMenu();
void showOutsideMenu();

void randomEncounter();
void fight(character &enemy);
void useSkill(character &ch, character &en);
void increaseStats(character &p);
void makeEnemy(character &e, const unsigned char level);

int main()
{
	init();

	while (running) {
		switch (player.getLocation()) {
		case PUB:
			showPubMenu();
			break;
		case OUTSIDE:
			showOutsideMenu();
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

	initSkills();

	running = true;
	player.setLocation(PUB);
	player.setGold(500);

	cout << "You wake up with a headache trying to remember eveything..." << endl;
	cout << "What is your name?" << endl << ": ";
	cin >> name;
	player.setName(name);

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
	initPlayer(player, choice);

	cout << endl;
	useSkillPt(player, true);

	// Seed for the random encounters, dodge and skill hit chance
	srand(time(NULL));

	cout << endl;
}

void initPlayer(character &p, int choice)
{
	switch (choice) {
	case 1:
		p.setClass(WARRIOR);
		p.setMaxHp(50);
		p.setMaxSp(10);
		p.setMinAtk(20);
		p.setMaxAtk(25);
		p.setDodge(30);
		p.setSkill(skillMan.getSkillList(WARRIOR));
		break;
	case 2:
		p.setClass(MAGE);
		p.setMaxHp(30);
		p.setMaxSp(30);
		p.setMinAtk(5);
		p.setMaxAtk(10);
		p.setDodge(60);
		p.setSkill(skillMan.getSkillList(MAGE));
		break;
	case 3:
		p.setClass(RANGER);
		p.setMaxHp(35);
		p.setMaxSp(5);
		p.setMinAtk(13);
		p.setMaxAtk(18);
		p.setTurn(2);
		p.setDodge(70);
		p.setSkill(skillMan.getSkillList(RANGER));
		break;
	}
}

void initSkills()
{
	skill* sk;
	effects* tempPlayerEffects, * tempEnemyEffects;
	mods* tempPlayerMods, * tempEnemyMods;
	string tempName, tempDescription;
	list<mods*>* tempPlayerModsList, * tempEnemyModsList;
	list<effects*>* tempPlayerEffectsList, * tempEnemyEffectsList;

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
	tempName = "Hell Fire";
	tempDescription = "Burn your target with a incredible flame, the target recieves 100 damage and another 30 damage for the next 3 turns.";
	tempPlayerEffects = NULL;
	tempEnemyEffects = new effects(CONSECUTIVE_DAMAGE, 30, 3, 100);
	tempPlayerMods = NULL;
	tempEnemyMods = NULL;

	tempPlayerModsList = NULL;
	tempEnemyModsList = NULL;
	tempPlayerEffectsList = NULL;
	tempEnemyEffectsList = new list<effects*>;
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 100, 35, 3, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	// Level 2
	tempDescription = "Burn your target with a incredible flame, the target recieves 50 damage and another 20 damage for the next 2 turns.";
	tempEnemyEffects = new effects(CONSECUTIVE_DAMAGE, 20, 2, 100);
	tempEnemyEffectsList = new list<effects*>;
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 50, 25, 2, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	// Level 1
	tempDescription = "Burn your target with a incredible flame, the target recieves 20 damage and another 10 damage for the next turn.";
	tempEnemyEffects = new effects(CONSECUTIVE_DAMAGE, 10, 1, 100);
	tempEnemyEffectsList = new list<effects*>;
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 20, 15, 1, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	sk = new skill(NULL, NULL, NULL, NULL, 0, 0, 0, ACTIVE, MAGE, &tempName, &tempDescription);
	skillMan.addSkill(sk);
	//skillMan.skillList[tempName] = sk0;

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
	tempName = "Frostbite";
	tempDescription = "Freeze your target dealing 150 damage and the target attack will be reduced by 60% in the next turn.";
	tempPlayerEffects = NULL;
	tempEnemyEffects = NULL;
	tempPlayerMods = NULL;
	tempEnemyMods = new mods(ATK, 60, 1, 100);

	tempPlayerModsList = NULL;
	tempEnemyModsList = new list<mods*>;
	tempEnemyModsList->push_back(tempEnemyMods);
	tempPlayerEffectsList = NULL;
	tempEnemyEffectsList = NULL;

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 150, 50, 3, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	// Level 2
	tempDescription = "Freeze your target dealing 50 damage and the target attack will be reduced by 30% in the next turn.";
	tempEnemyMods = new mods(ATK, 30, 1, 100);
	tempEnemyModsList = new list<mods*>;
	tempEnemyModsList->push_back(tempEnemyMods);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 50, 20, 2, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	// Level 1
	tempDescription = "Freeze your target dealing 10 damage and the target attack will be reduced by 20% in the next turn.";
	tempEnemyMods = new mods(ATK, 20, 1, 100);
	tempEnemyModsList = new list<mods*>;
	tempEnemyModsList->push_back(tempEnemyMods);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 10, 5, 1, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	sk = new skill(NULL, NULL, NULL, NULL, 0, 0, 0, ACTIVE, MAGE, &tempName, &tempDescription);

	skillMan.addSkill(sk);
	//skillMan.skillList[tempName] = sk0;

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
	tempName = "Thunder Burst";
	tempDescription = "Call the force of thunder and lightning to hit the target dealing 175 damage, 50% chance of stunning the target and 50% chance of draining 35% of target's max hp.";
	tempPlayerEffects = NULL;
	tempEnemyEffects = new effects(KNOCKBACK, 1, 0, 50);
	tempPlayerMods = NULL;
	tempEnemyMods = NULL;

	tempPlayerModsList = NULL;
	tempEnemyModsList = NULL;
	tempPlayerEffectsList = NULL;
	tempEnemyEffectsList = new list<effects*>;
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	tempEnemyEffects = new effects(HP_DRAIN, 35, 0, 50);
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 175, 50, 3, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	// Level 2
	tempDescription = "Call the force of thunder and lightning to hit the target dealing 75 damage, 35% chance of stunning the target.";
	tempEnemyEffects = new effects(KNOCKBACK, 1, 0, 35);
	tempEnemyEffectsList = new list<effects*>;
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 75, 20, 2, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	// Level 1
	tempDescription = "Call the force of thunder and lightning to hit the target dealing 20 damage, 20% chance of stunning the target.";
	tempEnemyEffects = new effects(KNOCKBACK, 1, 0, 50);
	tempEnemyEffectsList = new list<effects*>;
	tempEnemyEffectsList->push_back(tempEnemyEffects);

	sk = new skill(tempPlayerModsList, tempPlayerEffectsList, tempEnemyModsList, tempEnemyEffectsList, 20, 5, 1, ACTIVE, MAGE,
					&tempName, &tempDescription);
	skillMan.addSkill(sk);

	sk = new skill(NULL, NULL, NULL, NULL, 0, 0, 0, ACTIVE, MAGE, &tempName, &tempDescription);

	skillMan.addSkill(sk);
	//skillMan.skillList[tempName] = sk0;

	// Ranger skills

}

void useSkillPt(character &ch, const bool init)
{
	unsigned char pt = ch.getSkillPt();
	unsigned char ans = 'Y';
	int choice, x, size;
	vector<skillKey> skillList = ch.getSkillList();
	vector<skillKey>::iterator sk;
	vector<skillKey> upgradeableSkills;
	vector<skillKey>::iterator uSk_it;

	if (pt == 0) {
		cout << "No Skill point to use!" << endl;
	} else {
		do {
			for (sk = skillList.begin(); sk != skillList.end(); sk++) {
				if (skillMan.exists(sk->first, sk->second + 1))
					upgradeableSkills.push_back(*sk);
			}

			for (uSk_it = upgradeableSkills.begin(), x = 1; uSk_it != upgradeableSkills.end(); uSk_it++, x++)
				cout << x << ". " << uSk_it->first << endl;

			size = upgradeableSkills.size();
			
			if (size < 1) {
				cout << "No available skills to upgrade!" << endl;
				break;
			}

			if (init)
				cout << "Which initial skill would you like to have?" << endl;
			else
				cout << "Which skill do you want to improve?" << endl;

			do {
				cout << ":";
				cin >> choice;
			} while (choice < 0 || choice > size);

			for (uSk_it = upgradeableSkills.begin(), x = 1; uSk_it != upgradeableSkills.end(); uSk_it++, x++) {
				if (x == choice) {
					cout << uSk_it->first << " level-up!" << endl;
					skillList.push_back(make_pair((*uSk_it).first, (*uSk_it).second + 1));
					pt--;
					ch.setSkill(skillList);
					ch.setSkillPt(pt);
					break;
				}
			}

			if (pt > 0) {
				cout << "Use more points? [Y/N]" << endl;
				do {
					cout << ":";
					cin >> ans;
				} while (toupper(ans) != 'Y' && toupper(ans) != 'N');
			}
		} while (toupper(ans) == 'Y' && pt > 0);
	}
}

void cleanup()
{

}

void viewFullStats(character &ch)
{
	vector<skillKey> skillList = ch.getSkillList();
	vector<skillKey>::const_iterator it;

	cout << endl;
	cout << "Name: " << ch.getName() << endl;
	cout << "Class: " << ch.getStringClass() << endl;
	cout << "Level: " << (int)ch.getLevel() << endl;
	cout << "Exp: " << ch.getExp() << "/" << ch.getMaxExp()<< endl;
	cout << "HP: " << ch.getHp() << "/" << ch.getMaxHp() << endl;
	cout << "SP: " << ch.getSp() << "/" << ch.getMaxSp() << endl;
	cout << "Attack: " << ch.getMinAtk() << "-" << ch.getMaxAtk() << endl;
	cout << "Dodge: " << (int)ch.getDodge() << endl;
	cout << "Current gold: " << ch.getGold() << endl;
	cout << "Skill points: " << (int)ch.getSkillPt() << endl;
	cout << "Skills: " << endl;

	for (it = skillList.begin(); it != skillList.end(); it++) {
		if (it->second > 0) {
			cout << "\t" << it->first << " Level " << (int)it->second << " - " 
					<< skillMan.getSkill(*it)->getDescription() << endl;
		}
	}

	cout << endl;
}

void viewBattleStats(character &ch)
{
	cout << "Name: " << ch.getName() << endl;
	cout << "HP: " << ch.getHp() << "/" << ch.getMaxHp() << endl;
	cout << "SP: " << ch.getSp() << "/" << ch.getMaxSp() << endl;
	cout << endl;
}

void showPubMenu()
{
	int choice;

	cout << "You are in the pub" << endl;
	cout << EXPLORE_CHOICE << ". Explore outside" << endl;
	cout << REST_CHOICE << ". Rest" << endl;
	cout << BUY_CHOICE << ". Buy items" << endl;
	cout << STAT_CHOICE << ". Show stats" << endl;
	cout << USE_SKILLPT << ". Use skill point" << endl;
	cout << EXIT_CHOICE << ". End your Journey" << endl;
	cout << "What do you want to do?" << endl;

	do {
		cout << ": ";
		cin >> choice;
	} while (choice < 1 || choice > EXIT_CHOICE);

	switch (choice) {
	case EXPLORE_CHOICE:
		cout << endl << "Going outside" << endl;
		player.setLocation(OUTSIDE);
		break;
	case REST_CHOICE:
		if (player.useGold(REST_COST)) {
			cout << endl << "You slept and is now refreshed" << endl;
			player.heal(player.getMaxHp());
		}
		break;
	case BUY_CHOICE:
		break;
	case STAT_CHOICE:
		cout << endl << "Your stats" << endl;
		viewFullStats(player);
		break;
	case USE_SKILLPT:
		useSkillPt(player, false);
		break;
	case EXIT_CHOICE:
		running = false;
		break;
	}

	cout << endl;
}

void showOutsideMenu()
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
		randomEncounter();
		break;
	case PUB_CHOICE:
		cout << endl << "Going to the pub" << endl;
		player.setLocation(PUB);
		break;
	case STAT_CHOICE:
		cout << endl << "Your stats" << endl;
		viewFullStats(player);
		break;
	case EXIT_CHOICE:
		running = false;
		break;
	}

	cout << endl;
}

void randomEncounter()
{
	int i = rand() % 100;
	unsigned char level = player.getLevel();

	if (i <= ENEMY_CHANCE) {
		character enemy;
		makeEnemy(enemy, level);
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

	pturn = player.getTurn();
	eturn = enemy.getTurn();
	exp = enemy.getMaxHp();
	gold = enemy.getGold();

	cout << endl;
	cout << "An enemy has appeared!" << endl;
	while (!player.isDead() && !enemy.isDead() && !escape) {
		viewBattleStats(player);
		viewBattleStats(enemy);

		if (pturn > 0) {
			//do {
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
					cout << endl << "You attacked " << enemy.getName() << "!" << endl;
					player.attack(enemy);
					cin.get();
					break;
				case ITEM_CHOICE:
					cin.get();
					break;
				case SKILL_CHOICE:
					if (player.getSp() > 0)
						useSkill(player, enemy);
					else
						cout << endl << "No SP to use any skill!" << endl;

					cin.get();
					break;
				case RUN_CHOICE:
					cout << "Escaped!" << endl;
					escape = true;
					break;
				}
			//} while (true);

			// End player turn
			pturn--;
			if (eturn <= 0) 
				eturn++;
		} else if (eturn > 0) {
			cout << enemy.getName() << " attacks you!" << endl;
			enemy.attack(player);

			cin.get();

			// End enemy's turn
			eturn--;
			if (pturn <= 0) 
				pturn++;
		}
	}

	if (enemy.isDead()) {
		cout << enemy.getName() << " defeated!" << endl;
		cout << "You received " << exp << " exp" << endl;
		cout << "You received " << gold << " gold" << endl;

		player.addGold(gold);
		if (player.levelUp(exp)) {
			cout << "You leveled-up!" << endl;
			increaseStats(player);
			if (player.getLevel() % 5 == 0)
				player.addSkillPt(1);
			viewFullStats(player);
		}
	} else if (player.isDead()) {
		cout << "You died!" << endl;
		cout << "Lost half of your gold and experience points!" << endl;
		player.levelUp(-(player.getExp() / 2));
		player.setLocation(PUB);
		player.heal(player.getMaxHp());
	} else if (escape) {
		cout << "Escaped!" << endl;
	}

	cout << endl;
}

void useSkill(character &ch, character &en)
{
	vector<skillKey> skillList = ch.getSkillList();
	vector<skillKey>::const_iterator it;
	vector<skillKey> useableSkills;
	vector<skillKey>::iterator uSk_it;
	const skill *sk;
	int choice, x, size;
	unsigned short sp = ch.getSp();
	choice = 0;

	size = skillList.size();

	cout << endl;
	for (it = skillList.begin(), x = 1; it != skillList.end(); it++) {
		if (it->second > 0) {
			cout << x << ". " << it->first << " Level " << (int)it->second << endl;
			if (skillMan.getSkill(*it)->getSpCost() <= sp)
				choice = 1;
			useableSkills.push_back(*it);
			x++;
		}
	}

	if (!choice) {
		cout << endl << "No skill usable with current SP!" << endl;
		return;
	}
	cout << "Which skill do you want to use?" << endl;

	do {
		cout << ":";
		cin >> choice;
	} while (choice < 0 || choice > size);
	cin.ignore(numeric_limits<streamsize>::max(), '\n');

	sk = skillMan.getSkill(useableSkills[choice - 1]);
	ch.useSp(sk->getSpCost());
	cout << endl << "Used " << sk->getName() << "!" << endl;
	en.receiveDamage(sk->getDamage());
}

// Increase stats for level-up
void increaseStats(character &p)
{
	unsigned short hp, sp, minAtk, maxAtk, maxExp;
	unsigned char level;
	hp = p.getMaxHp();
	sp = p.getMaxSp();
	minAtk = p.getMinAtk();
	maxAtk = p.getMaxAtk();
	maxExp = p.getMaxExp();
	level = p.getLevel();

	maxExp += maxExp / 2;
	switch (p.getClass()) {
	case WARRIOR:
		hp += 10 + (7 * level);
		sp += 1.25 * level;
		minAtk += 2 * level;
		maxAtk += 2 * level;
		break;
	case MAGE:
		hp += 5 + (2.5 * level);
		sp += 3 * level;
		minAtk += 0.75 * level;
		maxAtk += 0.75 * level;
		break;
	case RANGER:
		hp += 5 + (3 * level);
		sp += 1.5 * level;
		minAtk += 3 * level;
		maxAtk += 3 * level;
		break;
	case ENEMY:
		break;
	}

	p.setMaxHp(hp);
	p.setMaxSp(sp);
	p.setMinAtk(minAtk);
	p.setMaxAtk(maxAtk);
	p.setMaxExp(maxExp);
}

// Make enemy stats relative to player's current level
void makeEnemy(character &e, const unsigned char level)
{
	unsigned char x;
	unsigned short hp, sp, minAtk, maxAtk;
	hp = 28;
	sp = 10;
	minAtk = 24;
	maxAtk = 29;

	for (x = 0; x < level; x++) {
		hp += 7 + (5 * level);
		sp += 10 + (2 * level);
		minAtk += 1.5 * level;
		maxAtk += 1.5 * level;
	}

	e.setName("Pikachu");
	e.setClass(ENEMY);
	e.setMaxHp(hp);
	e.setMaxSp(sp);
	e.setMinAtk(minAtk);
	e.setMaxAtk(maxAtk);
	e.setLevel(level);
	e.setGold(50);
}