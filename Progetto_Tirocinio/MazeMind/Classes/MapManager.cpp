#include "MapManager.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "Enums.h"
#include "Player.h"
#include <iostream>
#include "Bullet.h"
#include "HudLayer.h"


USING_NS_CC;

Scene* MapManager::createScene()
{

	auto scene = Scene::create();
	auto layer = MapManager::create();

	scene->addChild(layer);

	return scene;
}

// on "init" you need to initialize your instance
bool MapManager::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
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

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
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

	/*auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("Crash3.mp3");
	audio->playBackgroundMusic("Crash3.mp3");*/

	_player = Player::create("Player.png");
	_player->setMapGame(this);
	_player->setMappa(this->getMap());
	_player->input(IDLE);
	_player->setPosition(Point(32, 32));
	_player->setDestination(Point(957, 32));
	tile->addChild(_player, 5, "Player");


	_enemy = Enemy::create("Enemy.png");
	_enemy->input(IDLE);
	_enemy->setTarget(_player);
	_enemy->setPosition(Point(50, 294));
	_enemy->setTileMap(this->getTileMap());
	_enemy->setFirstDestination(Point(925, 294));
	_enemy->setSecondDestination(Point(50, 294));
	tile->addChild(_enemy, 5, "Enemy");
	_enemy->setMappa(this->getMap());
	_enemy->setMapGame(this);

	hud = new HudLayer();
	this->addChild(hud, 15);

	//this->setCameraMask((unsigned short)CameraFlag::USER2, true);

	/*
	camera = Camera::createPerspective(74, (float)visibleSize.width / visibleSize.height, 1.0, 1000);
	camera->setCameraFlag(CameraFlag::USER2);
	//the calling order matters, we should first call setPosition3D, then call lookAt.
	camera->setPosition3D(Vec3(center.x, center.y, 800));
	this->addChild(camera);
	*/


	//auto followAction = Follow::create(_player, Rect());
	// The Rect you give is the bounds the player can move before 
	// the camera (layer) starts following it. Giving empty rect will make sure the camera
	// follows as soon as your player starts moving.

	//this->runAction(followAction);

	/*
	button = ui::Button::create("initNormal.png", "initSelected.png");
	button->setTitleText("Reload");
	button->setTitleFontSize(17.0f);
	button->setTitleColor(Color3B::BLACK);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("Button pressed");
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(MapManager::createScene());
			break;
		default:
			break;
		}
	});

	button->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height));
	button->setAnchorPoint(Vec2(1, 1));
	tile->addChild(button, 1);

	closeButton = ui::Button::create("closeNormal.png", "closeSelected.png");
	closeButton->setTitleFontSize(17.0f);
	closeButton->setTitleColor(Color3B::BLACK);
	closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("Button pressed");
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	});
	
	closeButton->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
	closeButton->setAnchorPoint(Point(1, 0));
	tile->addChild(closeButton, 1);*/

	//this->setViewPointCenter(_player->getPosition());

	// Register Touch Event
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(MapManager::onTouchBegan, this);
	listener->onTouchEnded = CC_CALLBACK_2(MapManager::onTouchEnded, this);

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	log("WELCOME IN MY GAME. YOU HAVE TO REACH THE GOAL (THE STAIRS) TO WIN IT. GOOD LUCK!");
	_player->Solve((int)_player->getPosition().x, (int)_player->getPosition().y);
	this->scheduleUpdate();
	_player->scheduleUpdate();
	_enemy->scheduleUpdate();


	return true;
}



void MapManager::update(float dt) 
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
		container->runAction(MoveTo::create(1.001f, Vec2(viewPoint.x, viewPoint.y)));
		/*button->runAction(MoveTo::create(0.5f, Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height)));
		closeButton->runAction(MoveTo::create(0.5f, Vec2(origin.x + visibleSize.width, origin.y))); */
		deltaTime = 0;
	}
 
}


bool MapManager::onTouchBegan(Touch *touch, Event *event)
{   
	
	return true;
}


void MapManager::onTouchEnded(Touch *touch, Event *event)
{  
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
		return;
	}
	Director::getInstance()->pause();
	return;

	
}

/*
void MapManager::setPlayerPosition(Point position) {

Point tileCoord = this->tileCoordForPosition(position);
if (matrice[(int) tileCoord.x][(int) tileCoord.y] == NONE) {
log("YOU FAILED!");
auto move = Sequence::create(MoveTo::create(0.2f, Vec2(position.x, position.y)), FadeOut::create(1.0f), nullptr);
_player->runAction(move);
this->removeChild(_player);;
return;
}
if (matrice[(int)tileCoord.x][(int)tileCoord.y] == WALL) {
log("COLLISION!");
return;
}
if (matrice[(int)tileCoord.x][(int)tileCoord.y] == WATER) {
log("YOU CAN'T SWIM!");
return;
}
if (matrice[(int)tileCoord.x][(int)tileCoord.y] == GOAL) {
log("YOU WIN!");
auto move = Sequence::create(MoveTo::create(0.2f, Vec2(position.x, position.y)), FadeOut::create(1.0f), nullptr);
_player->runAction(move);
this->removeChild(_player);
return;
}

auto move = Sequence::create(MoveTo::create(0.2f, Vec2(position.x, position.y)), nullptr);
_player->runAction(move);
//this->setViewPointCenter(position);


} */

Point MapManager::tileCoordForPosition(Point position)
{
	int x = position.x / TILE_WIDTH;
	int y = (MAP_SIZE_HEIGHT - position.y) / TILE_HEIGHT;
	return Point(x, y);
}

Point MapManager::positionCoordForTile(Point position)
{
	int x = position.x * TILE_WIDTH;
	int y = MAP_SIZE_HEIGHT - position.y * TILE_HEIGHT;
	return Point(x, y);
}

Camera* MapManager::getCamera() {
	return this->camera;
}


void MapManager::createMap() {

	mat = new int*[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i)
		mat[i] = new int[MAP_HEIGHT];

	int random = RandomHelper::random_int(GROUND, WATER);
	int random2 = RandomHelper::random_int(GROUND, WATER);
	int random3 = RandomHelper::random_int(GROUND, WATER);

	int map[MAP_WIDTH][MAP_HEIGHT] = {
		{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL},
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, WALL, WALL, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, WALL, WALL, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, WALL, WALL, WALL },
		{ WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, WALL, GROUND, GROUND, GOAL, WALL },
		{ WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL, WALL}
	};

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			mat[i][j] = map[i][j];
		}
	}
}

int** MapManager::getMap() {
	return mat;
}

TMXTiledMap* MapManager::getTileMap() {
	return tile;
}
