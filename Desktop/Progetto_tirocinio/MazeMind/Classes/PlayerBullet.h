#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "cocos2d.h"
#include "Enums.h"
#include "Bullet.h"

USING_NS_CC;

class Enemy;
class CombatScene;
class GameManager;


class PlayerBullet : public Bullet
{
public:
	static PlayerBullet* create(const std::string& filename);
	void setCombatScene(CombatScene* scene);

	void setTargetEnemy(Enemy* enemy);
	void hitEnemy();

	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;
	void setPreviousState(State state);
	void setWeapon(Weapon Weapon);

protected:

	void setState(State state);

private:
	State _state;
	State previousState;
	Enemy* enemy;
	CombatScene* scene;
	float deltaTime;
	Weapon weapon;

};

#endif //__PLAYER_BULLET_H__