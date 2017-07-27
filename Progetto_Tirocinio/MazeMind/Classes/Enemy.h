#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class MapManager;
class Player;
class Bullet;

class Enemy : public cocos2d::Sprite
{
public:
	static Enemy* create(const std::string& filename);
	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;
	void input(State input);

	void setMovingState(Moving state);
	void setTarget(Player* player);

	void StartGoingUp();
	void StartGoingDown();
	void StartGoingLeft();
	void StartGoingRight();

	void StartAttacking();

	bool beCarefulLeft(Point position);
	bool beCarefulRight(Point position);
	bool beCarefulUp(Point position);
	bool beCarefulDown(Point position);

	bool beCarefulLeftUp(Point position);
	bool beCarefulRightUp(Point position);
	bool beCarefulLeftDown(Point position);
	bool beCarefulRightDown(Point position);

	void setFirstDestination(Point destination);
	void setSecondDestination(Point destination);
	void setMappa(int** mappa);

	Point getFirstDestination();
	Point getSecondDestination();

	void controlPosition(Point position);
	void setMapGame(MapManager* mapGame);
	void SetPreviousState(State state);
    
	void setTileMap(TMXTiledMap* tile);

protected:

	void SetState(State state);
	Point FDestination;
	Point SDestination;
	Point destination;

private:

	State _state;
	Moving MState;
	MapManager* mapGame;
	State previousState;
	int**  mappa;
	Player* target;
	float deltaTime;
	Bullet* projectile;
	TMXTiledMap* tile;
};

#endif // __ENEMY_H__