#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Enums.h"
#include <stdio.h>
#include <stdlib.h>

USING_NS_CC;

class MapManager;
class Enemy;
class PlayerBullet;
class CombatScene;
class Item;

class Player : public cocos2d::Sprite
{
	// An Data Structure for queue used in BFS
	struct queueNode
	{
		Point pt;  // The cordinates of a cell
		int dist;  // cell's distance of from the source
		queueNode *parent; // The coordinates of the predecessor
	};


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
	bool solve2(int x, int y);
	int solve3(int x, int y);
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
	std::list<Point> getPath();
	std::list<Point> getPathToGoal();

	void lookingAround();
	void bestChoise();

	void setCrawlingStrategy(Crawling crwaling);
	Crawling getCrawlingStrategy();

	void controlLeft();
	void controlRight();
	void controlUp();
	void controlDown();

	void gotcha(Item* item);

	void setPower(int power);
	int getPower();

	void setDefense(int defense);
	int getDefense();
	void createRoad();

	bool contain(std::list<queueNode> parents, queueNode p);


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
	Point neighbours[4];
	std::list<Point> path;
	std::list<Point> pathToGoal;
	PlayerBullet* projectile;
	CombatScene* arena;
	TMXTiledMap* tile;
	float deltaTime;
	float totalTime;
	float life;
	Field actualScene;
	Weapon actualWeapon;
	Protection actualProtection;
	Crawling crawlingStrategy;
	Strategy strategy;
	static Player* player;
	int wait;
	int power;
	int defense;
	std::list<Point> route;
	std::queue<Point> aux;
	int *dist;

	

	std::queue<queueNode> q;
	std::list<queueNode> parents;
	queueNode *help;
	queueNode *a;

};

#endif // __PLAYER_H__