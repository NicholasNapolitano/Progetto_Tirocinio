#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class MapManager;
class Enemy;
class PlayerBullet;
class CombatScene;

class Player : public cocos2d::Sprite
{
public:
	static Player* create(const std::string& filename);
	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;

	void setMovingState(Moving state);
	void setTarget(Enemy* enemy);
	void startAttacking();

	void startGoingUp();
	void startGoingDown();
	void startGoingLeft();
	void startGoingRight();

	bool beCarefulLeft(Point position);
	bool beCarefulRight(Point position);
	bool beCarefulUp(Point position);
	bool beCarefulDown(Point position);

	bool beCarefulLeftUp(Point position);
	bool beCarefulRightUp(Point position);
	bool beCarefulLeftDown(Point position);
	bool beCarefulRightDown(Point position);

	void setDestination(Point destination);
	void setMappa(int** mappa);
	void setTileMap(TMXTiledMap* tile);

	Point getDestination();
	void controlPosition(Point position);
	void setMapGame(MapManager* mapGame);
	void setPreviousState(State state);

	void followTheWall();
	bool solve(int x, int y);
	void setState(State state);
	void hurt();
	void setCombatScene(CombatScene* arena);
	void setActualScene(Field scene);
	void setActualWeapon(Weapon weapon);
	void setActualProtection(Protection weapon);
	void setStrategy(Strategy strategy);
	Strategy getStrategy();
	Weapon getActualWeapon();
	Protection getActualProtection();
	Field getActualScene();

	void setWait(int wait);
	int getWait();

	TMXTiledMap* getTileMap();
	int**  getMap();

	void setDeltaTime(float time);
	void setLife(float life);
	float getLife();
    
	MapManager* getMapGame();
	CombatScene* getMapFight();
	Enemy* getTarget();

	void setMatrix();


protected:

	Point destination;

private:

	State _state;
	Moving MState;
	MapManager* mapGame;
	State previousState;
	Enemy* target;
	int**  mappa;
	int** matrix;
	std::list<Point> path;
	PlayerBullet* projectile;
	CombatScene* arena;
	TMXTiledMap* tile;
	float deltaTime;
	float totalTime;
	float life;
	Field actualScene;
	Weapon actualWeapon;
	Protection actualProtection;
	Strategy strategy;
	static Player* player;
	int wait;
};

#endif // __PLAYER_H__