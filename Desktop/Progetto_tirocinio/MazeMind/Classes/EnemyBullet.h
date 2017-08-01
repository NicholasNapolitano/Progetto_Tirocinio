#ifndef __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "cocos2d.h"
#include "Enums.h"
#include "Bullet.h"

USING_NS_CC;

class Player;
class CombatScene;
class GameManager;


class EnemyBullet : public Bullet
{
public:
	static EnemyBullet* create(const std::string& filename);
	void setCombatScene(CombatScene* scene);

	void setTargetPlayer(Player* target);
	void hitPlayer();

	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;
	void setPreviousState(State state);
	void setWeapon(Weapon weapon);

protected:

	void setState(State state);

private:
	State _state;
	State previousState;
	Player* player;
	CombatScene* scene;
	int** mappa;
	float deltaTime;
	Weapon weapon;

};

#endif //__ENEMY_BULLET_H__