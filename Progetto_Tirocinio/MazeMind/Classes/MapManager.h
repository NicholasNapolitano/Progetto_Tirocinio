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
#define WRONG -2
#define START 100
#define GOAL 1000

class HudLayer;

class MapManager : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void update(float dt) override;
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);

	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	//void setPlayerPosition(cocos2d::Point position);
	Point tileCoordForPosition(cocos2d::Point position);
	Point positionCoordForTile(cocos2d::Point position);
	void createMap();
	//void update(float dt) override;
	int** getMap();
	Camera* getCamera();
	TMXTiledMap* getTileMap();


private:
	Player* _player;
	Enemy* _enemy;
	cocos2d::ui::Button *button;
	cocos2d::ui::Button *closeButton;
	cocos2d::TMXTiledMap* tile;
	cocos2d::TMXLayer* layer;
	int** mat;
	Camera* camera;
	Camera* zoom;
	float deltaTime;
	HudLayer* hud;
	Node* container;

	// implement the "static create()" method manually
	CREATE_FUNC(MapManager);
};

#endif // __MAP_MANAGER_H__
