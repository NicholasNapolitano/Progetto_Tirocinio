#ifndef __PLAYER_BULLET_H__
#define __PLAYER_BULLET_H__

#include "cocos2d.h"
#include "Enums.h"
#include "Bullet.h"

USING_NS_CC;

class Enemy;
class MapManager;
class GameManager;


class PlayerBullet : public Bullet
{
public:
	static PlayerBullet* create(const std::string& filename);
	void setManager(MapManager* map);

	void setTargetEnemy(Enemy* enemy);
	void hitEnemy();

	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;
	void input(State input);
	void SetPreviousState(State state);

protected:

	void SetState(State state);

private:
	State _state;
	State previousState;
	Enemy* enemy;
	MapManager* map;
	float deltaTime;

};

#endif //__PLAYER_BULLET_H__