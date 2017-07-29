#ifndef __ENEMY_BULLET_H__
#define __ENEMY_BULLET_H__

#include "cocos2d.h"
#include "Enums.h"
#include "Bullet.h"

USING_NS_CC;

class Player;
class MapManager;
class GameManager;


class EnemyBullet : public Bullet
{
public:
	static EnemyBullet* create(const std::string& filename);
	void setManager(MapManager* map);

	void setTargetPlayer(Player* target);
	void hitPlayer();

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
	MapManager* map;
	int** mappa;
	float deltaTime;

};

#endif //__ENEMY_BULLET_H__