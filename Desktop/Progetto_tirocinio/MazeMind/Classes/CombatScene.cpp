#include "MapManager.h"
#include "ui/CocosGUI.h"
#include "Enums.h"
#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include "HudLayer.h"
#include "GameManager.h"
#include "CombatScene.h"


USING_NS_CC;

Scene* CombatScene::createScene()
{

	auto scene = Scene::create();
	auto layer = CombatScene::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool CombatScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}

	this->core = GameManager::getInstance();
	this->deltaTime = 0;
	this->createMap();

	container = Node::create();
	this->addChild(container, 4);

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto winSize = Director::getInstance()->getWinSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	Point center = Point(winSize.width + origin.x, winSize.height + origin.y);

	tile = TMXTiledMap::create("GroundMap.tmx");
	tile->setPosition(Vec2(0, 0));
	layer = tile->getLayer("Ground");
	container->addChild(tile, 1, "Mappa");

	for (int i = 0; i < ARENA_WIDTH; i++) {
		for (int j = 0; j < ARENA_HEIGHT; j++) {
			switch (mat[i][j])
			{
			case NONE:
				layer->setTileGID(118, Vec2(i, j));
				break;
			case GROUND:
				break;
			case WALL:
				layer->setTileGID(448, Vec2(i, j));
				break;
			case GRASS:
				layer->setTileGID(289, Vec2(i, j));
				break;
			case WATER:
				layer->setTileGID(121, Vec2(i, j));
				break;
			case GOAL:
				layer->setTileGID(400, Vec2(i, j));
				break;
			}
		}
	}

	_player = Player::create("Player.png");
	_player->setCombatScene(this);
	_player->setMappa(this->getMap());
	_player->setState(IDLE);
	_player->setTileMap(this->getTileMap());
	_player->setPosition(Point(0, 0));
	tile->addChild(_player, 5, "Player");


	_enemy = Enemy::create("Enemy.png");
	_enemy->setState(IDLE);
	_enemy->setTarget(_player);
	_enemy->setPosition(Point(125, 125));
	_enemy->setTileMap(this->getTileMap());
	_enemy->setFirstDestination(Point(0, 0));
	_enemy->setSecondDestination(Point(125, 125));
	tile->addChild(_enemy, 5, "Enemy");
	_enemy->setMappa(this->getMap());
	_enemy->setCombatScene(this);

	_player->setTarget(_enemy);

	hud = new HudLayer();
	this->addChild(hud, 15);

	// Register Touch Event
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(CombatScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CombatScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	log("WELCOME IN MY GAME. YOU HAVE TO REACH THE GOAL (THE STAIRS) TO WIN IT. GOOD LUCK!");

	_player->solve((int)_player->getPosition().x, (int)_player->getPosition().y);

	this->scheduleUpdate();
	_player->scheduleUpdate();
	_enemy->scheduleUpdate();


	return true;
}



void CombatScene::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	deltaTime += dt;
	if (deltaTime >= 1.0f) {

		Point position = _player->getPosition();

		Size winSize = Director::getInstance()->getWinSize();

		int x = MAX(position.x, winSize.width / 2);
		int y = MAX(position.y, winSize.height / 2);
		x = MIN(x, (MAP_SIZE_WIDTH)-winSize.width / 2);
		y = MIN(y, (MAP_SIZE_HEIGHT)-winSize.height / 2);
		Point actualPosition = Point(x, y);

		Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
		Point viewPoint = Point(centerOfView) - Point(actualPosition);
		container->runAction(MoveTo::create(0.999f, Vec2(viewPoint.x, viewPoint.y)));
		deltaTime = 0;
	}

}


bool CombatScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}


void CombatScene::onTouchEnded(Touch *touch, Event *event)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (core->inPause()) {
		core->resumeGame();
		return;
	}
	core->pauseGame();
	return;
}

Point CombatScene::tileCoordForPosition(Point position)
{
	int x = position.x / TILE_WIDTH;
	int y = (MAP_SIZE_HEIGHT - position.y) / TILE_HEIGHT;
	return Point(x, y);
}

Point CombatScene::positionCoordForTile(Point position)
{
	int x = position.x * TILE_WIDTH;
	int y = MAP_SIZE_HEIGHT - position.y * TILE_HEIGHT;
	return Point(x, y);
}

void CombatScene::createMap() {

	mat = new int*[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i)
		mat[i] = new int[MAP_HEIGHT];

	int random = RandomHelper::random_int(GROUND, WATER);
	int random2 = RandomHelper::random_int(GROUND, WATER);
	int random3 = RandomHelper::random_int(GROUND, WATER);

	int map[ARENA_WIDTH][ARENA_HEIGHT] = {
		{GROUND, GROUND, GROUND, GROUND, GROUND},
		{GROUND, GROUND, GROUND, GROUND, GROUND},
		{GROUND, GROUND, GROUND, GROUND, GROUND},
		{GROUND, GROUND, GROUND, GROUND, GROUND},
		{GROUND, GROUND, GROUND, GROUND, GROUND}
	};

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			mat[i][j] = map[i][j];
		}
	}
}

int** CombatScene::getMap() {
	return mat;
}

TMXTiledMap* CombatScene::getTileMap() {
	return tile;
}