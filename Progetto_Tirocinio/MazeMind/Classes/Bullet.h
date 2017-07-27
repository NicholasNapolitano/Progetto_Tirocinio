#ifndef __BULLET_H__
#define __BULLET_H__

#include "cocos2d.h"

USING_NS_CC;

class Player;
class Enemy;
class MapManager;

class Bullet : public cocos2d::Sprite
{
public:
	static Bullet* create(const std::string& filename);
	void setTargetPlayer(Player* target);
	void setTargetEnemy(Enemy* enemy);
	void setManager(MapManager* map);
	void hitPlayer();
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
	Player* player;
	Enemy* enemy;
	MapManager* map;
	float deltaTime;
};

#endif //__BULLET_H__