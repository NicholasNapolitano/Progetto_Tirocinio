#include "Player.h"
#include "EnemyBullet.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SoundManager.h"

USING_NS_CC;

EnemyBullet* EnemyBullet::create(const std::string& filename)
{
	EnemyBullet *bullet = new (std::nothrow) EnemyBullet();
	if (bullet && bullet->initWithFile(filename))
	{
		bullet->autorelease();
		//default state
		bullet->SetPreviousState(IDLE);
		bullet->deltaTime = 1.0f;
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void EnemyBullet::setTargetPlayer(Player* player) {
	this->player = player;
}

void EnemyBullet::hitPlayer() {
	if (this->getBoundingBox().intersectsRect(this->player->getBoundingBox())) {
		player->hurt();
		this->getParent()->removeChild(this);
		return;
	}
}

void EnemyBullet::SetState(State state)
{
	this->previousState = _state;
	_state = state;
	switch (_state) {
	case IDLE:
		break;
	case MOVING:
		break;
	}
}

const State EnemyBullet::getState() const
{
	return _state;
}

const char* EnemyBullet::getStateName() const
{
	return typeid(_state).name();
}

void EnemyBullet::input(State input)
{
	this->SetState(input);
}


void EnemyBullet::update(float dt)
{
	deltaTime += dt;
	auto location = map->tileCoordForPosition(this->getPosition());
	auto mappa = map->getMap();
	if (mappa[(int)location.x][(int)location.y] == WALL)
	{
		this->unscheduleUpdate();
		this->getParent()->removeChild(this);
		return;
	}
	hitPlayer();

	if (deltaTime >= 1.0f) {
		auto prevState = this->previousState;
		if (previousState == MOVING) {
			this->input(IDLE);
			deltaTime = 0;
			return;
		}
		if (previousState == IDLE) {
			this->input(MOVING);
			auto offset = Point(player->getPosition() - this->getPosition());
			offset.normalize();
			auto shootAmount = offset * 600;
			auto realDest = shootAmount + this->getPosition();


			// Move projectile to actual endpoint
			this->runAction(Sequence::create(
				MoveTo::create(1.501f, realDest),
				RemoveSelf::create(), nullptr));
			deltaTime = 0;
		}
		deltaTime = 0;
	}
}

void EnemyBullet::SetPreviousState(State state)
{
	previousState = state;
}

void EnemyBullet::setManager(MapManager* map)
{
	this->map = map;
}