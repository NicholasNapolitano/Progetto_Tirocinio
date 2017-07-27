#include "Player.h"
#include "Bullet.h"
#include "Enemy.h"
#include "MapManager.h"
#include "GameOverScene.h"

USING_NS_CC;

Bullet* Bullet::create(const std::string& filename)
{
	Bullet *bullet = new (std::nothrow) Bullet();
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

void Bullet::setTargetEnemy(Enemy* enemy) {
	this->enemy = enemy;
}

void Bullet::setTargetPlayer(Player* player) {
	this->player = player;
}

void Bullet::hitPlayer() {
	if (this->getBoundingBox().intersectsRect(this->player->getBoundingBox())) {
		this->runAction(FadeOut::create(0.5f));
		player->runAction(FadeOut::create(1.0f));
		player->unscheduleUpdate();
		map->cleanup();
		this->unscheduleUpdate();
		GameOverScene *gameOverScene = GameOverScene::create();
		gameOverScene->getLayer()->getLabel()->setString("You Win!");
		Director::getInstance()->replaceScene(gameOverScene);
	}
}

void Bullet::hitEnemy() {
	if (this->getBoundingBox().intersectsRect(this->enemy->getBoundingBox())) {
		this->runAction(FadeOut::create(0.01f));
		enemy->runAction(FadeOut::create(1.0f));
		enemy->unscheduleUpdate();
	}
}

void Bullet::SetState(State state)
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

const State Bullet::getState() const
{
	return _state;
}

const char* Bullet::getStateName() const
{
	return typeid(_state).name();
}

void Bullet::input(State input)
{
	this->SetState(input);
}


void Bullet::update(float dt)
{
	deltaTime += dt;
	hitPlayer();
	if (deltaTime >= 1.0f) {
		auto prevState = this->previousState;
		if (previousState == MOVING) {
			this->input(IDLE);
			hitPlayer();
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
				MoveTo::create(1.001f, realDest),
				RemoveSelf::create(), nullptr));
			hitPlayer();
			deltaTime = 0;
		}
		deltaTime = 0;
	}
}

void Bullet::SetPreviousState(State state) 
{
	previousState = state;
}

void Bullet::setManager(MapManager* map) 
{
	this->map = map;
}
