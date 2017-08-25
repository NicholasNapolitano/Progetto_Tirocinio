#ifndef __ENEMY_H__
#define __ENEMY_H__

#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class MapManager;
class Player;
class EnemyBullet;
class CombatScene;

class Enemy : public cocos2d::Sprite
{
public:
	static Enemy* create(const std::string& filename);
	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;

	void setMovingState(Moving state);
	void setTarget(Player* player);

	void startGoingUp();
	void startGoingDown();
	void startGoingLeft();
	void startGoingRight();

	void startAttacking();

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
	void setDestination(Point destination);
	void setMappa(int** mappa);

	Point getFirstDestination();
	Point getSecondDestination();
	Point getDestination();

	void controlPosition(Point position);
	void setMapGame(MapManager* mapGame);
	void setPreviousState(State state);
    
	void setTileMap(TMXTiledMap* tile);
	void hurt();
	void setState(State state);
	void setCombatScene(CombatScene* arena);
	void setActualScene(Field scene);
	void setActualWeapon(Weapon weapon);
	void setActualProtection(Protection protection);
	Weapon getActualWeapon();
	Protection getActualProtection();
	Player* getTarget();
	MapManager* getMapGame();
	CombatScene* getMapFight();

	void setWait(int wait);
	int getWait();
	Field getActualScene();
	int**  getMap();
	TMXTiledMap* getTileMap();

	void setType(EnemyType type);
	EnemyType getType();

	void setLife(float life);
	float getLife();
	float getTotalTime();
	void setDeltaTime(float time);
	void boom();
	int decision = 3;
	void controlLeft();
	void controlRight();
	void controlUp();
	void controlDown();

	void lookingAround();
	void bestChoise();

protected:

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
	float totalTime;
	EnemyBullet* projectile;
	TMXTiledMap* tile;
	CombatScene* arena;
	float life;
	Field actualScene;
	Weapon actualWeapon;
	Protection actualProtection;
	EnemyType type;
	int wait;
	Sprite* booom;
	Point neighbours[4];
};

#endif // __ENEMY_H__