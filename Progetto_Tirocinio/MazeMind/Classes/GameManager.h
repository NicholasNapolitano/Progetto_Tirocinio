#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class MapManager;
class Player;
class Enemy;
class GameOverScene;
class HudLayer;
class StartMenu;

class GameManager
{
public:
	GameManager();
	~GameManager();

	void startGame();
	static GameManager* getCore();

	/*void setMapGame(MapManager* mapGame);
	void setMap(int** mappa);
	void setPlayer(Player* player);*/

private:
	MapManager* mManager;
	Player* gamer;
	int** gameMap;
	StartMenu* start;
};

#endif // __GAME_MANAGER_H__