#include "Enemy.h"
#include <typeinfo>
#include "MapManager.h"
#include "Enums.h"
#include "Player.h"
#include "SoundManager.h"
#include "EnemyBullet.h"
#include "GameManager.h"
#include "CombatScene.h"
#include "StrategyManager.h"

USING_NS_CC;

Enemy* Enemy::create(const std::string& filename)
{
	Enemy *enemy = new (std::nothrow) Enemy();
	if (enemy && enemy->initWithFile(filename))
	{
		enemy->autorelease();
		//default state
		enemy->setPreviousState(IDLE);
		enemy->destination = enemy->getFirstDestination();
		enemy->deltaTime = 0;
		enemy->totalTime = 0;
		enemy->wait = 0;
		enemy->life = 2.0f;
		enemy->actualScene = EXPLORATION;
		enemy->actualWeapon = GUN;

		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return nullptr;
}


void Enemy::setState(State state)
{
	this->previousState = _state;
	_state = state;
	switch (_state) {
	case IDLE:
		break;
	case MOVING:
		break;
	case ATTACKING:
		break;
	case STUNNING:
		break;
	}
}

void Enemy::setMovingState(Moving state)
{
	if (_state = MOVING) {
		MState = state;
		switch (MState) {

		case MOVE_UP:
			startGoingUp();
			break;
		case MOVE_DOWN:
			startGoingDown();
			break;
		case MOVE_LEFT:
			startGoingLeft();
			break;
		case MOVE_RIGHT:
			startGoingRight();
			break;
		}
	}
	else return;
}

const State Enemy::getState() const
{
	return _state;
}

const char* Enemy::getStateName() const
{
	return typeid(_state).name();
}


void Enemy::setFirstDestination(Point first)
{
	this->FDestination = first;
}

void Enemy::setSecondDestination(Point second)
{
	this->SDestination = second;
}

Point Enemy::getFirstDestination()
{
	return this->FDestination;
}

Point Enemy::getSecondDestination()
{
	return this->SDestination;
}

void Enemy::update(float dt)
{
	deltaTime += dt;
	if (this->life <= 0) {
		if (this->getType() == KAMIKAZE) {
				this->boom();
			}
		this->getParent()->unscheduleAllCallbacks();
		SoundManager::getInstance()->startWinSound();
		this->getMapFight()->finishBattle();
		return;
	}
	auto tileCoord = arena->tileCoordForPosition(this->getPosition());
	auto map = this->getMap();
	if (this->getActualScene() == EXPLORATION) {
		this->controlPosition(this->getPosition());
	}
	if (this->getActualScene() == FIGHT) {
		if (map[(int)tileCoord.x][(int)tileCoord.y] == START) {
			this->getParent()->unscheduleAllCallbacks();
			SoundManager::getInstance()->startWinSound();
			this->getMapFight()->finishBattle();
			return;
		}
		if (this->getType() == KAMIKAZE) {
			if (this->getBoundingBox().intersectsRect(this->getTarget()->getBoundingBox())) {
				this->boom();
				this->getParent()->unscheduleAllCallbacks();
				SoundManager::getInstance()->startWinSound();
				this->getMapFight()->finishBattle();
				return;
			}
		}
	}
	if (deltaTime >= 0.5f) {
		auto prevState = this->previousState;
		if (previousState == MOVING || previousState == ATTACKING || previousState == DEFENDING || previousState == STUNNING) {
			this->setState(IDLE);
			return;
		}
		if (_state == STUNNING) {
			this->runAction(DelayTime::create(0.5f));

		}
		if (previousState == IDLE) {
			if (this->getType() == SENTRY) {
				StrategyManager::getInstance()->sentryBehaviour(this);
			}
			else if (this->getType() == KAMIKAZE) {
				StrategyManager::getInstance()->kamikazeBehaviour(this);
			}
			else if (this->getType() == TOWER) {
				StrategyManager::getInstance()->towerBehaviour(this);
			}
			else if (this->getType() == SCOUT) {
				StrategyManager::getInstance()->scoutBehaviour(this);
			}
		}
	}
}



void Enemy::startGoingUp() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x, position.y + TILE_HEIGHT);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}

void Enemy::startGoingDown() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x, position.y - TILE_HEIGHT);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;

}

void Enemy::startGoingLeft() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x - TILE_WIDTH, position.y);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}

void Enemy::startGoingRight() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x + TILE_WIDTH, position.y);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}


bool Enemy::beCarefulLeft(Point position) {
	auto tileCoordLeft = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y));


	if (mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == NONE || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WALL || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulRight(Point position) {
	auto tileCoordRight = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y));

	if (mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == NONE || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WALL || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulUp(Point position) {
	auto tileCoordUp = mapGame->tileCoordForPosition(Point(position.x, position.y + TILE_HEIGHT));
	//auto mappa = mapGame->getMap();

	if (mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == NONE || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WALL || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulDown(Point position) {
	auto tileCoordDown = mapGame->tileCoordForPosition(Point(position.x, position.y - TILE_HEIGHT));

	if (mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == NONE || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WALL || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulLeftUp(Point position) {
	auto tileCoordLeftUp = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y + TILE_HEIGHT));

	if (mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == NONE || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WALL || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulLeftDown(Point position) {
	auto tileCoordLeftDown = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y - TILE_HEIGHT));


	if (mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == NONE || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WALL || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulRightUp(Point position) {
	auto tileCoordRightUp = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y + TILE_HEIGHT));


	if (mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == NONE || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WALL || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Enemy::beCarefulRightDown(Point position) {
	auto tileCoordRightDown = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y - TILE_HEIGHT));


	if (mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == NONE || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WALL || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WATER) {
		return false;
	}

	return true;
}

void Enemy::controlPosition(Point position) {
	auto tileCoord = mapGame->tileCoordForPosition(position);


	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == NONE) {
		this->unscheduleUpdate();
		this->runAction(FadeOut::create(1.0f));
		tile->removeChild(this);
		return;
	}
	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == WALL) {
		log("COLLISION!");
		this->unscheduleUpdate();
		return;
	}
	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == WATER) {
		this->unscheduleUpdate();
		this->runAction(FadeOut::create(1.0f));
		tile->removeChild(this);
		return;
	}
	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == STUN) {
		log("OPS!");
		this->setMovingState((Moving)RandomHelper::random_int(0, 3));
		return;
	}
	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == BURN) {
		log("OUCH!");
		SoundManager::getInstance()->startHurtScream();
		this->setLife(this->getLife() - 0.5f);
		return;
	}
}


void Enemy::setMapGame(MapManager* pMap) {
	mapGame = pMap;
}

void Enemy::setMappa(int** map) {
	mappa = map;

}

void Enemy::setPreviousState(State state) {
	previousState = state;
}

void Enemy::startAttacking() {
	auto w = this->actualWeapon;
	if (w == GUN) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startGunSound();
			projectile = EnemyBullet::create("GunBullet.png");
			this->setWait(1);
		}
		this->setWait(this->getWait() - 1);
	}
	else if (w == RIFLE) {
		SoundManager::getInstance()->startRifleSound();
		projectile = EnemyBullet::create("RifleBullet.png");
	}
	else if (w == KNIFE) {
		SoundManager::getInstance()->startKnifeSound();
		projectile = EnemyBullet::create("Knife.png");
	}
	else if (w == SNIPER) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startSniperSound();
			projectile = EnemyBullet::create("SniperBullet.png");
			this->setWait(2);
		}
		this->setWait(this->getWait() - 1);
	}
	else if (w == RADIATION) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startGrenadeOutSound();
			projectile = EnemyBullet::create("Radiation.png");
			this->setWait(6);
		}
		else {
			this->setWait(this->getWait() - 1);
		}
	}
	else if (w == GRENADE) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startGrenadeOutSound();
			projectile = EnemyBullet::create("Grenade.png");
			this->setWait(6);
		}
		this->setWait(this->getWait() - 1);

	}
	projectile->setPosition(this->getPosition());
	projectile->setTargetPlayer(this->target);
	projectile->setWeapon(w);
	projectile->setCombatScene(arena);
	tile->addChild(projectile, 5);
	projectile->scheduleUpdate();
}


void Enemy::setTarget(Player* player) {
	this->target = player;
}

void Enemy::setTileMap(TMXTiledMap* tile) {
	this->tile = tile;
}

void Enemy::hurt() {

	SoundManager::getInstance()->startHurtScream();

	if (target->getActualWeapon() == GUN) {
		if (this->getActualProtection() == SHIELD)
		{
			this->life -= 0.5f;
			return;
		}
		else {
			this->life -= 1.0f;
			return;
		}
	}
	else if (target->getActualWeapon() == RIFLE) {
		if (this->getActualProtection() == SHIELD)
		{
			this->life -= 0.25f;
			return;
		}
		else {
			this->life -= 0.5f;
			return;
		}
	}
	else if (target->getActualWeapon() == SNIPER) {
		if (this->getActualProtection() == SHIELD)
		{
			this->life -= 0.75f;
			return;
		}
		else {
			this->life -= 1.5f;
			return;
		}
	}
	else if (target->getActualWeapon() == KNIFE) {
		if (this->getActualProtection() == ARMGUARD)
		{
			this->life -= 1.0f;
			return;
		}
		else {
			this->life -= 2.0f;
			return;
		}
	}
	else if (target->getActualWeapon() == RADIATION || this->getActualWeapon() == RADIATION) {
		if (this->getActualProtection() == MASK)
		{
			return;
		}
		else {
			this->setState(STUNNING);
			return;
		}
	}
	else if (target->getActualWeapon() == GRENADE || this->getActualWeapon() == GRENADE) {
		if (this->getActualProtection() == ARMOR)
		{
			this->life -= 1.0f;
			return;
		}
		else
		{
			this->life -= 2.0f;
			return;
		}
	}
}

void Enemy::boom() {
	SoundManager::getInstance()->startGrenadeSound();
	booom = Sprite::create("KamikazeExplosion.png");
	booom->setPosition(this->getPosition());
	tile->addChild(booom, 5);
	if (booom->getBoundingBox().intersectsRect(this->getTarget()->getBoundingBox())) {
		if (this->getTarget()->getActualProtection() == ARMOR) {
			this->getTarget()->setLife(this->getTarget()->getLife() - 1.0);
		}
		else {
			this->getTarget()->setLife(this->getTarget()->getLife() - 2.0);
		}
	}
	return;
}

void Enemy::setCombatScene(CombatScene* arena) {
	this->arena = arena;
}

void Enemy::setActualScene(Field scene) {
	this->actualScene = scene;
}

void Enemy::setActualWeapon(Weapon weapon) {
	this->actualWeapon = weapon;
}

Weapon Enemy::getActualWeapon() {
	return this->actualWeapon;
}

Player* Enemy::getTarget() {
	return this->target;
}

MapManager* Enemy::getMapGame() {
	return this->mapGame;
}

void Enemy::setWait(int wait) {
	this->wait = wait;
}

int Enemy::getWait() {
	return this->wait;
}

CombatScene* Enemy::getMapFight() {
	return this->arena;
}

Field Enemy::getActualScene() {
	return this->actualScene;
}

int** Enemy::getMap() {
	return this->mappa;
}

TMXTiledMap* Enemy::getTileMap() {
	return this->tile;
}

void Enemy::setActualProtection(Protection protection) {
	this->actualProtection = protection;
}

Protection Enemy::getActualProtection() {
	return this->actualProtection;
}

void Enemy::setType(EnemyType type) {
	this->type = type;
}

EnemyType Enemy::getType() {
	return this->type;
}

Point Enemy::getDestination() {
	return this->destination;
}

void Enemy::setDestination(Point destination) {
	this->destination = destination;
}

void Enemy::setDeltaTime(float time) {
	this->deltaTime = time;
}

void Enemy::setLife(float life) {
	this->life = life;
}

float Enemy::getLife() {
	return this->life;
}

float Enemy::getTotalTime() {
	return this->totalTime;
}
