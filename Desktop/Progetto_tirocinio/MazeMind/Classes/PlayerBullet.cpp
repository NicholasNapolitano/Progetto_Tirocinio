#include "Enemy.h"
#include "PlayerBullet.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "CombatScene.h"

USING_NS_CC;

PlayerBullet* PlayerBullet::create(const std::string& filename)
{
	PlayerBullet *bullet = new (std::nothrow) PlayerBullet();
	if (bullet && bullet->initWithFile(filename))
	{
		bullet->autorelease();
		//default state
		bullet->setPreviousState(IDLE);
		bullet->deltaTime = 1.0f;
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void PlayerBullet::setTargetEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

void PlayerBullet::hitEnemy() {
	if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
		enemy->hurt();
		this->getParent()->removeChild(this);
		return;
	}
}

void PlayerBullet::setState(State state)
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

const State PlayerBullet::getState() const
{
	return _state;
}

const char* PlayerBullet::getStateName() const
{
	return typeid(_state).name();
}

void PlayerBullet::update(float dt)
{
	deltaTime += dt;
	auto location = scene->tileCoordForPosition(this->getPosition());
	auto mappa = scene->getMap();
	if (mappa[(int)location.x][(int)location.y] == WALL)
	{
		this->unscheduleUpdate();
		this->getParent()->removeChild(this);
		return;
	}
	hitEnemy();
	
	if (deltaTime >= 1.0f) {
		auto prevState = this->previousState;
		if (previousState == MOVING) {
			this->setState(IDLE);
			deltaTime = 0;
			return;
		}
		if (previousState == IDLE) {
			this->setState(MOVING);
			auto offset = Point(enemy->getPosition() - this->getPosition());
			offset.normalize();
			if (this->weapon == GUN) {
				auto shootAmount = offset * 60;
				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(1.0f, realDest),
					RemoveSelf::create(), nullptr));
			}
			else if (this->weapon == RIFLE) {
				auto shootAmount = offset * 130;
				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.7f, realDest),
					RemoveSelf::create(), nullptr));
			}
			deltaTime = 0;
		}
	}
}

void PlayerBullet::setPreviousState(State state)
{
	previousState = state;
}

void PlayerBullet::setCombatScene(CombatScene* scene)
{
	this->scene = scene;
}

void PlayerBullet::setWeapon(Weapon weapon) {
	this->weapon = weapon;
}