#ifndef __ENUMS_H__
#define __ENUMS_H__

enum State {
	IDLE = 0,
	MOVING,
	ATTACKING,
	DEFENDING,
	STUNNING
};

enum EnemyType {
	SENTRY,
	KAMIKAZE,
	TOWER,
	SCOUT
};

enum Strategy {
	NONE,
	DEFEAT_ENEMY,
	DISTANCE_ATTACK,
	RETREAT,
	BE_PATIENT,
	STUN_ENEMY
};

enum Weapon {
	NO_ONE,
	GUN,
	RIFLE,
	SNIPER,
	GRENADE,
	KNIFE,
	RADIATION
};

enum Protection {
	ANYTHING,
	SHIELD,
	ARMOR,
	MASK,
	ARMGUARD
};

enum Field {
	EMPTY,
	EXPLORATION,
	FIGHT
};

enum Moving {

	MOVE_UP,
	MOVE_RIGHT,
	MOVE_DOWN,
	MOVE_LEFT

};


#endif // __ENUMS_H__