#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

USING_NS_CC;

class CombatScene;
class GameManager;

//Abstract class to model a general bullet on the CombatScene

class Bullet : public cocos2d::Sprite
{
public:
	virtual void setCombatScene(CombatScene* scene) = 0;
	virtual const State getState() const = 0;
	virtual const char* getStateName() const = 0;
	virtual void update(float dt) override = 0;
	virtual void setPreviousState(State state) = 0;
	virtual void setWeapon(Weapon weapon) = 0;


protected:

	virtual void setState(State state) = 0;

private:
    State _state;
	State previousState;
	CombatScene* scene;
	float deltaTime;
	Weapon weapon;

};

#endif //__BULLET_H__