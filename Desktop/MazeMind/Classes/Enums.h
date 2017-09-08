#ifndef __ENUMS_H__
#define __ENUMS_H__

//Intestation class which lists enumerate types used in this project

//Enumerative Type used to change the behaviour of a character

enum State {

	IDLE = 0,
	MOVING,
	ATTACKING,
	DEFENDING,
	STUNNING
};

//Enumerative Type used to model the correct Enemy on the Screen

enum EnemyType {

	SENTRY,
	KAMIKAZE,
	TOWER,
	SCOUT
};

//Enumerative Type used to change the Player's behaviour during a battle

enum Strategy {

	NONE,
	DEFEAT_ENEMY,
	DISTANCE_ATTACK,
	RETREAT,
	BE_PATIENT,
	STUN_ENEMY
};

//Enumerative Type used to model the correct Weapon used by a Character

enum Weapon {

	NO_ONE,
	GUN,
	RIFLE,
	KNIFE,
	SNIPER,
	GRENADE,
	RADIATION
};

//Enumerative Type used to change the Player's behaviour to explore the Labyrinth

enum Crawling {

	NORMAL,
	GO_TO_GOAL
};

//Enumerative Type used to model the correct Protection used by a Character

enum Protection {
	ANYTHING,
	SHIELD,
	ARMOR,
	MASK,
	ARMGUARD
};

//Enumerative Type used to tell the Player in which Field it is walking on

enum Field {

	EMPTY,
	EXPLORATION,
	FIGHT
};

//Enumerative Type used to model the correct Object in the Labyrinth

enum Thing {

	ANY_ONE,
	CURE,
	POWER_UP,
	DEFENSE_UP,
	CHEST
};

//Enumerative Type used to change the Movement of a Character

enum Moving {

	MOVE_UP,
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT

};

#endif // __ENUMS_H__