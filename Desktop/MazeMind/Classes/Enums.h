#ifndef __ENUMS_H__
#define __ENUMS_H__

enum State {
	IDLE = 0,
	MOVING,
	ATTACKING,
	DEFENDING
};

enum Strategy {
	NONE,
	DEFEAT_ENEMY,
	DISTANCE_ATTACK,
	RETREAT
};

enum Weapon {
	NO_ONE,
	GUN,
	RIFLE,
	SNIPER,
	GRANADE,
	KNIFE
};

enum Field {
	EMPTY,
	EXPLORATION,
	FIGHT
};

enum Moving {

	MOVE_UP,
	MOVE_DOWN,
	MOVE_LEFT,
	MOVE_RIGHT

};


#endif // __ENUMS_H__