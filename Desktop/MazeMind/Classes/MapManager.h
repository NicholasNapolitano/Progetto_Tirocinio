#ifndef __MAP_MANAGER_H__
#define __MAP_MANAGER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Enemy.h"

USING_NS_CC;

#define MAP_WIDTH   40
#define MAP_HEIGHT  40
#define TILE_WIDTH   25
#define TILE_HEIGHT  25
#define MAP_SIZE_WIDTH  MAP_WIDTH*TILE_WIDTH
#define MAP_SIZE_HEIGHT  MAP_HEIGHT*TILE_HEIGHT

#define NONE -1
#define WALL 0
#define GROUND 1
#define GRASS 2
#define WATER 3
#define STEP 10
#define GOAL 1000

class GameManager;
class HudLayer;
class StrategyMenu;
class Player;
class Enemy;

class MapManager : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void update(float dt) override;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);


	Point tileCoordForPosition(cocos2d::Point position);
	Point positionCoordForTile(cocos2d::Point position);

	void beginBattle(Enemy* enemy);
	void createMapI();
	void createMapII();
	void createMapIII();
	void createMapIV();
	void createMapV();
	void createMapVI();
	int** getMap();
	TMXTiledMap* getTileMap();
	void setStrategyMenu(StrategyMenu* strategy);
	void setPlayer(Player* player);
	Player* getPlayer();
	HudLayer* getHud();
	void setHud(HudLayer* hud);


private:
	Player* _player;
	Enemy* _enemy;
	cocos2d::TMXTiledMap* tile;
	cocos2d::TMXLayer* layer;
	int** mat;
	float deltaTime;
	HudLayer* hud;
	Node* container;
	GameManager* core;
	StrategyMenu* strategy;

	// implement the "static create()" method manually
	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__
