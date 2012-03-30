// Global vars
#ifndef MAIN_H
#define MAIN_H

// Pub menu choices
#define EXPLORE_CHOICE 1
#define REST_CHOICE 2
#define BUY_CHOICE 3
#define STAT_CHOICE 4
#define EXIT_CHOICE 5

// Outside menu choices
#define MOVE_CHOICE 1
#define PUB_CHOICE 2

//Attack menu choices
#define ATTACK_CHOICE 1
#define ITEM_CHOICE 2
#define SKILL_CHOICE 3
#define RUN_CHOICE 4

#define ENEMY_CHANCE 60
#define REST_COST 20

enum class_system {WARRIOR, MAGE, RANGER, ENEMY};
enum location {OUTSIDE, PUB};
enum skill_type {ACTIVE, PASSIVE};
enum stats {HP, ATK, DODGE};
enum effect {CONSECUTIVE_DAMAGE, NUM_ATK, KNOCKBACK, HP_DRAIN, CRITICAL};

typedef struct _mods
{
	enum stats stat;
	unsigned char val, turns, chance;
	_mods(enum stats s, unsigned char v, unsigned char t, unsigned char ch): stat(s), val(v), turns(t), chance(ch) {};
} mods;


typedef struct _effects
{
	enum effect eff;
	unsigned char val, turns, chance;
	_effects(enum effect e, unsigned char v, unsigned char t, unsigned char ch): eff(e), val(v), turns(t), chance(ch) {};
} effects;

#endif