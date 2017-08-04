#include "Player.h"
#include "EnemyBullet.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "CombatScene.h"

USING_NS_CC;

EnemyBullet* EnemyBullet::create(const std::string& filename)
{
	EnemyBullet *bullet = new (std::nothrow) EnemyBullet();
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

void EnemyBullet::setTargetPlayer(Player* player) {
	this->player = player;
}

void EnemyBullet::hitPlayer() {
	if (this->weapon == GRANADE) {
		return;
	}
	if (this->getBoundingBox().intersectsRect(this->player->getBoundingBox())) {
		player->hurt();
		this->getParent()->removeChild(this);
		return;
	}
}

void EnemyBullet::explosion() {
	if (this->getBoundingBox().intersectsRect(this->player->getBoundingBox())) {
		player->hurt();
		this->getParent()->removeChild(this);
		return;
	}
}

void EnemyBullet::setState(State state)
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


void EnemyBullet::update(float dt)
{
	deltaTime += dt;
	auto location = scene->tileCoordForPosition(this->getPosition());
	auto mappa = scene->getMap();
	if (mappa[(int)location.x][(int)location.y] == WALL && this->weapon != GRANADE)
	{
		this->unscheduleUpdate();
		this->getParent()->removeChild(this);
		return;
	}
	if (player != NULL) {
		hitPlayer();
	}

	if (deltaTime >= 1.0f) {
		auto prevState = this->previousState;
		if (previousState == MOVING) {
			this->setState(IDLE);
			deltaTime = 0;
			return;
		}
		if (previousState == IDLE) {
			this->setState(MOVING);
			auto offset = Point(player->getPosition() - this->getPosition());
			offset.normalize();
			if (this->weapon == GUN) {
				auto shootAmount = offset * 60;

				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(1.501f, realDest),
					RemoveSelf::create(), nullptr));
			}
			else if (this->weapon == RIFLE) {
				auto shootAmount = offset * 130;

				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.85f, realDest),
					RemoveSelf::create(), nullptr));
			}

			else if (this->weapon == SNIPER) {
				auto shootAmount = offset * 200;
				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.55f, realDest),
					RemoveSelf::create(), nullptr));
			}

			else if (this->weapon == GRANADE) {
				auto shootAmount = offset * 150;
				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.65f, realDest),
					DelayTime::create(2.0f), RemoveSelf::create(), nullptr));
				SoundManager::getInstance()->startGranadeSound();
				explosion();
			}
			deltaTime = 0;
		}
		deltaTime = 0;
	}
}

void EnemyBullet::setPreviousState(State state)
{
	previousState = state;
}

void EnemyBullet::setCombatScene(CombatScene* scene)
{
	this->scene = scene;
}

void EnemyBullet::setWeapon(Weapon weapon) {
	this->weapon = weapon;
}