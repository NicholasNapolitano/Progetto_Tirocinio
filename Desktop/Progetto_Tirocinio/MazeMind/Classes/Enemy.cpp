#include "Enemy.h"
#include <typeinfo>
#include "MapManager.h"
#include "Enums.h"
#include "Player.h"
#include "SoundManager.h"
#include "Bullet.h"

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

void Enemy::input(State input)
{
	this->setState(input);
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
	if (deltaTime >= 1.0f) {
		auto prevState = this->previousState;
		if (previousState == MOVING || previousState == ATTACKING) {
			this->input(IDLE);
			this->controlPosition(this->getPosition());
			return;
		}
		if (previousState == IDLE) {
			auto diff = target->getPosition() - this->getPosition();
			if (abs(diff.x) < 100 || abs(diff.x) < 100) {
				this->input(ATTACKING);
				startAttacking();
				deltaTime = 0;
				return;
			}
			this->input(MOVING);
			auto location = this->getPosition();
			auto distance = this->destination - location;
			if (abs(distance.x) > abs(distance.y)) {
				if (distance.x > 0) {
					this->setMovingState(MOVE_RIGHT);
				}
				else {
					this->setMovingState(MOVE_LEFT);
				}
			}
			else {
				if (distance.y > 0) {
					this->setMovingState(MOVE_UP);
				}
				else {
					this->setMovingState(MOVE_DOWN);
				}
			}
			if (mapGame->tileCoordForPosition(location) == mapGame->tileCoordForPosition(this->getFirstDestination()))
				this->destination = this->getSecondDestination();
			else if (mapGame->tileCoordForPosition(location) == mapGame->tileCoordForPosition(this->getSecondDestination()))
				this->destination = this->getFirstDestination();
		}
		deltaTime = 0;
	}
}



void Enemy::startGoingUp() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x, position.y + TILE_HEIGHT);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(1.001f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}

void Enemy::startGoingDown() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x, position.y - TILE_HEIGHT);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(1.001f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;

}

void Enemy::startGoingLeft() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x - TILE_WIDTH, position.y);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(1.001f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}

void Enemy::startGoingRight() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x + TILE_WIDTH, position.y);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(1.001f, Vec2(newPosition.x, newPosition.y)), nullptr);
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

	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == WATER) {
		this->unscheduleUpdate();
		this->runAction(FadeOut::create(1.0f));
		tile->removeChild(this);
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
	projectile = Bullet::create("Projectile.png");
	projectile->setPosition(this->getPosition());
	projectile->setTargetPlayer(this->target);
	projectile->setManager(mapGame);
	tile->addChild(projectile, 5);
	projectile->scheduleUpdate();
	SoundManager::getInstance()->startShotSound();
}


void Enemy::setTarget(Player* player) {
	target = player;
}

void Enemy::setTileMap(TMXTiledMap* tile) {
	this->tile = tile;
}
