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

	scene->addChild(layer, 1, "CombatScene");

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

	tile = TMXTiledMap::create("Arena.tmx");
	tile->setPosition(Vec2(origin.x, origin.y));
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
			case ESCAPE:
				layer->setTileGID(213, Vec2(i, j));
				break;
			case START:
				layer->setTileGID(491, Vec2(i, j));
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
	_player->setScale(25 / layer->getTileAt(Vec2(0, 0))->getContentSize().width);
	_player->setCombatScene(this);
	_player->setMappa(this->getMap());
	_player->setTileMap(this->getTileMap());
	_player->setActualScene(FIGHT);
	_player->setState(IDLE);
	_player->setPosition(Point(origin.x + 10, origin.y + 10));
	tile->addChild(_player, 5, "Player");

	hud = new HudLayer();
	this->addChild(hud, 15);
	hud->setScore(0);

	// Register Touch Event
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(CombatScene::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(CombatScene::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	this->resizeMap();

	auto aux = winSize.width;
	auto aux2 = winSize.height;

	container->setScale(1 / layer->getTileAt(Vec2(0, 0))->getScale());
	container->setScaleX(3.43f * aux/600);
	container->setScaleY(3.43f * aux2 / 600);

	this->scheduleUpdate();


	return true;
}

//Method to schedule the CombatScene every frame

void CombatScene::update(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	deltaTime += dt;

	if (this->getHud()->getScore() == 0) {
		core->loseGame();
	}

	if (deltaTime >= 0.5f) {

		hud->setScore(hud->getScore() - 1);

		Point position = _player->getPosition();

		Size winSize = Director::getInstance()->getWinSize();

		int x = MAX(position.x * (layer->getTileAt(Vec2(0, 0))->getContentSize().width / 25), winSize.width / 2);
		int y = MAX(position.y * (layer->getTileAt(Vec2(0, 0))->getContentSize().width / 25), winSize.height / 2);
		x = MIN(x, (MAP_SIZE_WIDTH * (layer->getTileAt(Vec2(0, 0))->getContentSize().width / 25)) - winSize.width / 2);
		y = MIN(y, (MAP_SIZE_HEIGHT * (layer->getTileAt(Vec2(0, 0))->getContentSize().width / 25)) - winSize.height / 2);
		Point actualPosition = Point(x, y);

		Point centerOfView = Point(winSize.width / 2, winSize.height / 2);
		Point viewPoint = Point(centerOfView) - Point(actualPosition);
		container->runAction(MoveTo::create(0.5f, Vec2(viewPoint.x, viewPoint.y)));
		deltaTime = 0;
	}

}

//When you tap the screen nothing happens

bool CombatScene::onTouchBegan(Touch *touch, Event *event)
{
	return true;
}

//When you release the tap from the screen then the game goes in pause. Tap again to continue the execution.

void CombatScene::onTouchEnded(Touch *touch, Event *event)
{
	if (core->inPause()) {
		core->resumeGame();
		return;
	}
	core->pauseGame();
	return;
}

//Method which return the coordinates in TILE from the ones in POINT

Point CombatScene::tileCoordForPosition(Point position)
{
	int x = position.x / TILE_WIDTH;
	int y = (ARENA_SIZE_HEIGHT - position.y) / TILE_HEIGHT;
	return Point(x, y);
}

//Dynamic allocation of memory to instanziate the Arena and define the the type for all blocks

void CombatScene::createMap() {

	mat = new int*[ARENA_WIDTH];
	for (int i = 0; i < ARENA_WIDTH; ++i)
		mat[i] = new int[ARENA_HEIGHT];

	int random = RandomHelper::random_int(GROUND, WATER);
	int random2 = RandomHelper::random_int(GROUND, WATER);
	int random3 = RandomHelper::random_int(GROUND, WATER);

	int map[ARENA_WIDTH][ARENA_HEIGHT] = {
		{GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, START },
		{GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND },
		{GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND },
		{GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND },
		{GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND },
		{GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND },
		{ESCAPE, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND }
	};

	for (int i = 0; i < ARENA_WIDTH; i++) {
		for (int j = 0; j < ARENA_HEIGHT; j++) {
			mat[i][j] = map[i][j];
		}
	}
}

//Method which adaptes the Map according to device's screen resolution

void CombatScene::resizeMap() {

	for (int i = 0; i < ARENA_WIDTH; i++) {
		for (int j = 0; j < ARENA_HEIGHT; j++) {
			auto tiles = layer->getTileAt(Vec2(j, i));
			tiles->setScale(25 / tiles->getContentSize().width);
			tiles->setPosition(Vec2(Director::getInstance()->getVisibleOrigin().x + 25 * j, -25 + Director::getInstance()->getVisibleOrigin().y + ARENA_SIZE_HEIGHT - 25 * i));
		}
	}

}

//Method to place the correct Enemy based on its EnemyType

void CombatScene::setEnemy(EnemyType type) {
	switch (type) {
	case SENTRY:
		_enemy = Enemy::create("Sentry.png");
		_enemy->setScale(layer->getTileAt(Vec2(0, 0))->getScale());
		_enemy->setCombatScene(this);
		_enemy->setMappa(this->getMap());
		_enemy->setTileMap(this->getTileMap());
		_enemy->setActualScene(FIGHT);
		_enemy->setState(IDLE);
		_enemy->setType(SENTRY);
		_enemy->setPosition(Point(155, 155));
		_enemy->setFirstDestination(Point(100, 10));
		_enemy->setSecondDestination(Point(170, 170));
		tile->addChild(_enemy, 5, "Sentry");
		_enemy->setTarget(_player);
		_player->setTarget(_enemy);
		_player->scheduleUpdate();
		_enemy->scheduleUpdate();
		break;
	case KAMIKAZE:
		_enemy = Enemy::create("Kamikaze.png");
		_enemy->setScale(layer->getTileAt(Vec2(0, 0))->getScale());
		_enemy->setCombatScene(this);
		_enemy->setMappa(this->getMap());
		_enemy->setTileMap(this->getTileMap());
		_enemy->setActualScene(FIGHT);
		_enemy->setState(IDLE);
		_enemy->setType(KAMIKAZE);
		_enemy->setLife(3.0f);
		_enemy->setPosition(Point(155, 155));
		tile->addChild(_enemy, 5, "Kamikaze");
		_enemy->setTarget(_player);
		_player->setTarget(_enemy);
		_player->scheduleUpdate();
		_enemy->scheduleUpdate();
		break;
	case TOWER:
		_enemy = Enemy::create("Tower.png");
		_enemy->setScale(layer->getTileAt(Vec2(0, 0))->getScale());
		_enemy->setCombatScene(this);
		_enemy->setMappa(this->getMap());
		_enemy->setTileMap(this->getTileMap());
		_enemy->setActualScene(FIGHT);
		_enemy->setState(IDLE);
		_enemy->setType(TOWER);
		_enemy->setLife(4.0f);
		_enemy->setPosition(Point(155, 155));
		tile->addChild(_enemy, 5, "Tower");
		_enemy->setTarget(_player);
		_player->setTarget(_enemy);
		_player->scheduleUpdate();
		_enemy->scheduleUpdate();
		break;
	case SCOUT:
		_enemy = Enemy::create("Scout.png");
		_enemy->setScale(layer->getTileAt(Vec2(0, 0))->getScale());
		_enemy->setCombatScene(this);
		_enemy->setMappa(this->getMap());
		_enemy->setTileMap(this->getTileMap());
		_enemy->setActualScene(FIGHT);
		_enemy->setState(IDLE);
		_enemy->setType(SCOUT);
		_enemy->setPosition(Point(155, 155));
		tile->addChild(_enemy, 5, "Scout");
		_enemy->setTarget(_player);
		_player->setTarget(_enemy);
		_player->scheduleUpdate();
		_enemy->scheduleUpdate();
		break;
	}
}

//Getters & Setters

int** CombatScene::getMap() {
	return mat;
}

TMXTiledMap* CombatScene::getTileMap() {
	return this->tile;
}

Player* CombatScene::getPlayer() {
	return this->_player;
}

Enemy* CombatScene::getEnemy() {
	return this->_enemy;
}

void CombatScene::finishBattle() {
	GameManager::getInstance()->resumeExploration(_player);
}

void CombatScene::setHud(HudLayer* hud) {
	this->hud = hud;
}

HudLayer* CombatScene::getHud() {
	return this->hud;
}

cocos2d::TMXLayer* CombatScene::getLayer() {
	return this->layer;
}
