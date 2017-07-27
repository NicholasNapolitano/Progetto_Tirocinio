#include "Player.h"
#include <typeinfo>
#include "MapManager.h"
#include "GameManager.h"
#include "SoundManager.h"


USING_NS_CC;

Player* Player::create(const std::string& filename)
{
	Player *player = new (std::nothrow) Player();
	if (player && player->initWithFile(filename))
	{
		player->autorelease();
		//default state
		player->setPreviousState(IDLE);
		player->deltaTime = 0;
		player->life = 3;
		return player;
	}
	CC_SAFE_DELETE(player);
	return nullptr;
}

void Player::setState(State state)
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

void Player::setMovingState(Moving state)
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

const State Player::getState() const
{
	return _state;
}

const char* Player::getStateName() const
{
	return typeid(_state).name();
}

void Player::setDestination(Point destination)
{
	this->destination = destination;
}

Point Player::getDestination()
{
	return this->destination;
}

void Player::update(float dt)
{
	deltaTime += dt;
	if (this->life == 0) {
		this->runAction(FadeOut::create(1.0f));
		GameManager::getInstance()->loseGame();
	}
	if (deltaTime >= 1.0f) {
		auto prevState = this->previousState;
		if (previousState == MOVING) {
			this->setState(IDLE);
			this->controlPosition(this->getPosition());
			return;
		}
		if (previousState == IDLE) {
			this->setState(MOVING);
			auto location = this->getPosition();
			auto goal = this->getDestination();
			if (location == goal) {
				this->setState(IDLE);
				return;
			}
			auto diff = goal - location;
			if (path.size() != 0) {
				Point destination = this->path.front();
				auto move = Sequence::create(MoveTo::create(0.999f, Vec2(destination.x, destination.y)), nullptr);
				this->runAction(move);
				this->path.pop_front();
			}
			deltaTime = 0;
		}
	}
}


void Player::startGoingUp() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x, position.y + TILE_HEIGHT);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}

void Player::startGoingDown() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x, position.y - TILE_HEIGHT);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;

}

void Player::startGoingLeft() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x - TILE_WIDTH, position.y);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}

void Player::startGoingRight() {
	auto position = this->getPosition();
	auto newPosition = Point(position.x + TILE_WIDTH, position.y);
	log("newPosition: (%d %d)", (int)newPosition.x, (int)newPosition.y);
	auto move = Sequence::create(MoveTo::create(0.5f, Vec2(newPosition.x, newPosition.y)), nullptr);
	this->runAction(move);
	return;
}


bool Player::beCarefulLeft(Point position) {
	auto tileCoordLeft = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y));

	if (mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == NONE || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WALL || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulRight(Point position) {
	auto tileCoordRight = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y));

	if (mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == NONE || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WALL || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulUp(Point position) {
	auto tileCoordUp = mapGame->tileCoordForPosition(Point(position.x, position.y + TILE_HEIGHT));

	if (mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == NONE || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WALL || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulDown(Point position) {
	auto tileCoordDown = mapGame->tileCoordForPosition(Point(position.x, position.y - TILE_HEIGHT));

	if (mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == NONE || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WALL || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulLeftUp(Point position) {
	auto tileCoordLeftUp = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y + TILE_HEIGHT));

	if (mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == NONE || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WALL || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulLeftDown(Point position) {
	auto tileCoordLeftDown = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y - TILE_HEIGHT));

	if (mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == NONE || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WALL || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulRightUp(Point position) {
	auto tileCoordRightUp = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y + TILE_HEIGHT));

	if (mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == NONE || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WALL || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulRightDown(Point position) {
	auto tileCoordRightDown = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y - TILE_HEIGHT));

	if (mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == NONE || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WALL || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WATER) {
		return false;
	}

	return true;
}

void Player::controlPosition(Point position) {
	auto tileCoord = mapGame->tileCoordForPosition(position);
	GameManager* core = GameManager::getInstance();

	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == GOAL) {
		log("YOU WIN!");
		this->unscheduleUpdate();
		this->runAction(FadeOut::create(1.0f));
		core->winGame();
		return;
	}

	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == NONE) {
		log("YOU FAILED!");
		this->unscheduleUpdate();
		this->runAction(FadeOut::create(1.0f));
		core->loseGame();
		return;
	}

	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == WALL) {
		log("COLLISION!");
		this->unscheduleUpdate();
		return;
	}
	if (mappa[(int)tileCoord.x][(int)tileCoord.y] == WATER) {
		log("YOU CAN'T SWIM!");
		this->unscheduleUpdate();
		core->loseGame();
		return;
	}

}

void Player::setMapGame(MapManager* pMap) {
	mapGame = pMap;
}

void Player::setMappa(int** map) {
	mappa = map;
}

void Player::setPreviousState(State state) {
	previousState = state;
}

void Player::followTheWall() {
	auto playerPos = this->getPosition();

	auto tileCoordLeft = mapGame->tileCoordForPosition(Point(playerPos.x - TILE_WIDTH, playerPos.y));
	auto tileCoordRight = mapGame->tileCoordForPosition(Point(playerPos.x + TILE_WIDTH, playerPos.y));
	auto tileCoordUp = mapGame->tileCoordForPosition(Point(playerPos.x, playerPos.y + TILE_HEIGHT));
	auto tileCoordDown = mapGame->tileCoordForPosition(Point(playerPos.x, playerPos.y - TILE_HEIGHT));

	auto tileCoordLeftUp = mapGame->tileCoordForPosition(Point(playerPos.x - TILE_WIDTH, playerPos.y + TILE_HEIGHT));
	auto tileCoordRightUp = mapGame->tileCoordForPosition(Point(playerPos.x + TILE_WIDTH, playerPos.y + TILE_HEIGHT));
	auto tileCoordLeftDown = mapGame->tileCoordForPosition(Point(playerPos.x - TILE_WIDTH, playerPos.y - TILE_HEIGHT));
	auto tileCoordRightDown = mapGame->tileCoordForPosition(Point(playerPos.x + TILE_WIDTH, playerPos.y - TILE_HEIGHT));

	/*
	if (mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WALL && mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WALL && mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WALL) {
		this->input(MOVE_UP);
		this->previousState = MOVE_UP;
		return;
	}
	else if (mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WALL && mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WALL && mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WALL) {
		this->input(MOVE_RIGHT);
		this->previousState = MOVE_RIGHT;
		return;
	}
	else if (mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WALL && mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WALL && mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WALL) {
		this->input(MOVE_DOWN);
		this->previousState = MOVE_DOWN;
		return;
	}
	else if (mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WALL && mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WALL && mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WALL) {
		this->input(MOVE_LEFT);
		this->previousState = MOVE_LEFT;
		return;
	}
	else if (mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WALL) {
		this->input(MOVE_DOWN);
		this->previousState = MOVE_DOWN;
		return;
	}
	else if (mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WALL) {
		this->input(MOVE_UP);
		this->previousState = MOVE_UP;
		return;
	}
	else if (mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WALL) {
		this->input(MOVE_LEFT);
		this->previousState = MOVE_LEFT;
		return;
	}
	else if (mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WALL) {
		this->input(MOVE_RIGHT);
		this->previousState = MOVE_RIGHT;
		return;
	}
	else if (mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WALL) {
		this->input(MOVE_LEFT);
		this->previousState = MOVE_LEFT;
		return;
	}
	else if (mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WALL) {
		this->input(MOVE_UP);
		this->previousState = MOVE_UP;
		return;
	}
	else if (mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WALL) {
		this->input(MOVE_RIGHT);
		this->previousState = MOVE_RIGHT;
		return;
	}
	else if (mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WALL) {
		this->input(MOVE_DOWN);
		this->previousState = MOVE_DOWN;
		return;
	}*/
}


bool Player::solve(int x, int y)
{
	Point A = mapGame->tileCoordForPosition(Point(x, y));
	int X = (int) A.x;
	int Y = (int) A.y;
	auto goal = mapGame->tileCoordForPosition(this->getDestination());
	
	Point prev;
	if (path.size() > 0) {
		prev = path.back();
	}

	// Check if we have reached our goal.
	if (X == (int) goal.x && Y == (int) goal.y){
		path.push_back(Point(x, y));
		return true;
	}

	if (mappa[X][Y] == WALL || mappa[X][Y] == STEP) return false;
	// If you are on a wall or already were here

	mappa[X][Y] = STEP;
	path.push_back(Point(x, y));

	// Recursively search for our goal.
	if (x > 0 && solve(x - TILE_WIDTH, y))
	{
		return true;
	}
	if (x < MAP_SIZE_WIDTH && solve(x + TILE_WIDTH, y))
	{
		return true;
	}
	if (y > 0 && solve(x, y + TILE_HEIGHT))
	{
		return true;
	}
	if (y < MAP_SIZE_HEIGHT && solve(x, y - TILE_HEIGHT))
	{
		return true;
	}

	// Otherwise we need to backtrack and find another solution.
	this->path.push_back(prev);

	return false;
}

Player* Player::getPlayer() {
	return this;
}

void Player::hurt() {
	this->life -= 1;
	SoundManager::getInstance()->startDeathScream();
}
