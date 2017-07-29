#ifndef __COMBAT_SCENE_H__
#define __COMBAT_COMBAT_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "Enemy.h"
#include "MapManager.h"

USING_NS_CC;

#define ARENA_WIDTH   5
#define ARENA_HEIGHT  5
#define TILE_WIDTH   25
#define TILE_HEIGHT  25
#define ARENA_SIZE_WIDTH  ARENA_WIDTH*TILE_WIDTH
#define ARENA_SIZE_HEIGHT  ARENA_HEIGHT*TILE_HEIGHT

#define NONE -1
#define WALL 0
#define GROUND 1
#define GRASS 2
#define WATER 3

class GameManager;
class HudLayer;

class CombatScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt) override;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);


	Point tileCoordForPosition(cocos2d::Point position);
	Point positionCoordForTile(cocos2d::Point position);

	void createMap();
	int** getMap();
	TMXTiledMap* getTileMap();


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

	// implement the "static create()" method manually
	CREATE_FUNC(CombatScene);
};

#endif // __MAP_MANAGER_H__