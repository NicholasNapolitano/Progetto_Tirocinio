#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class MapManager;

class Player : public cocos2d::Sprite
{
public:
	static Player* create(const std::string& filename);
	const State getState() const;
	const char* getStateName() const;
	void update(float dt) override;
	void input(State input);

	void setMovingState(Moving state);

	void StartGoingUp();
	void StartGoingDown();
	void StartGoingLeft();
	void StartGoingRight();

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

	Point getDestination();
	void controlPosition(Point position);
	void setMapGame(MapManager* mapGame);
	void SetPreviousState(State state);

	void followTheWall();
	bool Solve(int x, int y);
	Player* getPlayer();

protected:

	void SetState(State state);
	Point destination;

private:

	State _state;
	Moving MState;
	MapManager* mapGame;
	State previousState;
	int**  mappa;
	std::list<Point> path;
	float deltaTime;
};

#endif // __PLAYER_H__