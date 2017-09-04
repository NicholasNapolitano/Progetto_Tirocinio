#include "Enemy.h"
#include "PlayerBullet.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "CombatScene.h"

USING_NS_CC;

//Method which create an PlayerBullet based on a image file stored in the "Resources" Directory of the project

PlayerBullet* PlayerBullet::create(const std::string& filename)
{
	PlayerBullet *bullet = new (std::nothrow) PlayerBullet();
	if (bullet && bullet->initWithFile(filename))
	{
		bullet->autorelease();
		//default state
		bullet->setPreviousState(IDLE);
		bullet->deltaTime = 3.0f;
		return bullet;
	}
	CC_SAFE_DELETE(bullet);
	return nullptr;
}

//Method which described what happens when the PlayerBullet hits the Enemy (based on the Weapon)

void PlayerBullet::hitEnemy() {
	if (this->weapon == GRENADE){
		if (explode != NULL) {
			if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
				enemy->hurt();
			}
			if (this->getBoundingBox().intersectsRect(this->enemy->getTarget()->getBoundingBox())) {
				enemy->getTarget()->hurt();
			}
        }
		else return;
	}
	else if (this->weapon == RADIATION) {
		if (gas != NULL) {
			if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
				enemy->hurt();
			}
			if (this->getBoundingBox().intersectsRect(this->enemy->getTarget()->getBoundingBox())) {
				enemy->getTarget()->hurt();
			}
		}
		else return;
	}
	else {
		if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
			enemy->hurt();
			this->getParent()->removeChild(this);
			return;
		}
	}
}

//Method which described what happens when during a grenade explosion

void PlayerBullet::explosion(Ref *pSender) {
	auto map = this->scene->getTileMap();
	auto mat = this->scene->getMap();
	auto location = this->scene->tileCoordForPosition(this->getPosition());
	map->getLayer("Ground")->setTileGID(104, Point(location.x, location.y));
	mat[(int)location.x][(int)location.y] = BURN;
	this->runAction(FadeOut::create(0.1f));
	explode->runAction(FadeOut::create(0.5f));
}

//Method which described what happens when during a Radiation grenade explosion

void PlayerBullet::stun(Ref *pSender) {
	auto map1 = this->scene->getTileMap();
	auto mat1 = this->scene->getMap();
	auto location = this->scene->tileCoordForPosition(this->getPosition());
	map1->getLayer("Ground")->setTileGID(289, Point(location.x, location.y));
	mat1[(int)location.x][(int)location.y] = STUN;
	this->runAction(FadeOut::create(0.1f));
	gas->runAction(FadeOut::create(1.5f));
	return;
}

//Method which places the sprite of the Granade's explosion

void PlayerBullet::setExplosionSprite(Ref *pSender) {
	SoundManager::getInstance()->startGrenadeSound();
	explode = Sprite::create("Explosion.png");
	explode->setPosition(this->getPosition());
	this->getParent()->addChild(explode);
}

//Method which places the sprite of the Radiation granade's explosion

void PlayerBullet::setRadiationSprite(Ref *pSender) {
	SoundManager::getInstance()->startGasSound();
	gas = Sprite::create("RadiationExplosion.png");
	gas->setPosition(this->getPosition());
	this->getParent()->addChild(gas);
}

//Method which removes the sprite of the Granade's explosion

void PlayerBullet::deleteExplosionSprite(Ref *pSender) {
	this->getParent()->removeChild(explode);
	this->unscheduleUpdate();
	this->getParent()->removeChild(this);
	return;
}

//Method which removes the sprite of the Radiation granade's explosion

void PlayerBullet::deleteRadiationSprite(Ref *pSender) {
	this->getParent()->removeChild(gas);
	this->unscheduleUpdate();
	this->getParent()->removeChild(this);
	return;
}

//Method used to set the State of the PlayerBullet and discriminates its behaviour

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

//Method to schedule the PlayerBullet every frame

void PlayerBullet::update(float dt)
{
	deltaTime += dt;
	auto location = scene->tileCoordForPosition(this->getPosition());
	auto mappa = scene->getMap();
	if (mappa[(int)location.x][(int)location.y] == WALL && this->weapon != GRENADE && this->weapon != RADIATION)
	{
		this->unscheduleUpdate();
		this->getParent()->removeChild(this);
		return;
	}
	hitEnemy();

	if (deltaTime >= 1.0f && this->weapon != GRENADE && this->weapon != RADIATION) {
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

			else if (this->weapon == KNIFE) {
				auto shootAmount = offset * 30;
				auto realDest = shootAmount + this->getPosition();


				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.3f, realDest),
					RemoveSelf::create(), nullptr));
			}
			deltaTime = 0;
		}
	}
	else if (deltaTime >= 2.5f && this->weapon != RADIATION) {
		if (this->weapon == GRENADE) {
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

				auto callBack0 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::explosion, this));
				auto callBack1 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::setExplosionSprite, this));
				auto callBack2 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::deleteExplosionSprite, this));
				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.5f, realDest),
					DelayTime::create(1.4f), callBack1, DelayTime::create(0.05f), callBack0, DelayTime::create(0.5f), callBack2, nullptr));
			}
			deltaTime = 0;
		}
	}
	else if (deltaTime >= 3.0f) {
		if (this->weapon == RADIATION) {
			if (previousState == MOVING) {
				this->setState(IDLE);
				deltaTime = 0;
				return;
			}
			if (previousState == IDLE) {
				this->setState(MOVING);
				auto offset1 = Point(enemy->getPosition() - this->getPosition());
				offset1.normalize();
				auto shootAmount1 = offset1 * 130;
				auto realDest1 = shootAmount1 + this->getPosition();

				auto callBack3 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::stun, this));
				auto callBack4 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::setRadiationSprite, this));
				auto callBack5 = CallFuncN::create(CC_CALLBACK_1(PlayerBullet::deleteRadiationSprite, this));
				// Move projectile to actual endpoint
				this->runAction(Sequence::create(
					MoveTo::create(0.5f, realDest1),
					DelayTime::create(0.4f), callBack4, DelayTime::create(0.09f), callBack3, DelayTime::create(1.5f), callBack5, nullptr));
			}
			deltaTime = 0;
		}
	}
}

//Getters & Setters

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

void PlayerBullet::setTargetEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

const State PlayerBullet::getState() const
{
	return _state;
}

const char* PlayerBullet::getStateName() const
{
	return typeid(_state).name();
}

