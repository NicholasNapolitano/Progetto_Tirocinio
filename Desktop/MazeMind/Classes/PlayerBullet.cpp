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
		bullet->deltaTime = 2.0f;
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

void PlayerBullet::setTargetEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

void PlayerBullet::hitEnemy() {
	if (this->weapon == GRANADE) {
		return;
	}
	if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
		enemy->hurt();
		this->getParent()->removeChild(this);
		return;
	}
}

void PlayerBullet::explosion(Ref *pSender) {
	if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
		enemy->hurt();
		this->getParent()->removeChild(this);
		return;
	}
	this->getParent()->removeChild(explode);
}

void PlayerBullet::setExplosionSprite(Ref *pSender) {
	SoundManager::getInstance()->startGranadeSound();
	explode = Sprite::create("Explosion.png");
	explode->setPosition(this->getPosition());
	this->getParent()->addChild(explode);
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
	if (mappa[(int)location.x][(int)location.y] == WALL && this->weapon != GRANADE)
	{
		this->unscheduleUpdate();
		this->getParent()->removeChild(this);
		return;
	}
	hitEnemy();

	if (deltaTime >= 1.0f && this->weapon != GRANADE) {
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

			else if (this->weapon == SNIPER) {
				auto shootAmount = offset * 200;
				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.4f, realDest),
					RemoveSelf::create(), nullptr));
			}
			deltaTime = 0;
		}
	}
	else if (deltaTime >= 2.0f && this->weapon == GRANADE) {
		if (previousState == MOVING) {
			this->setState(IDLE);
			deltaTime = 0;
			return;
		}
		if (previousState == IDLE) {
			this->setState(MOVING);
			auto offset = Point(enemy->getPosition() - this->getPosition());
			offset.normalize();
			auto shootAmount = offset * 130;
			auto realDest = shootAmount + this->getPosition();

			auto callBack1 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::explosion, this));
			auto callBack2 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::setExplosionSprite, this));
			// Move projectile to actual endpoint
			this->runAction(Sequence::create(
				MoveTo::create(0.5f, realDest),
				DelayTime::create(1.3f), callBack2, DelayTime::create(0.1f), callBack1, RemoveSelf::create(), nullptr));
			}
			deltaTime = 0;
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