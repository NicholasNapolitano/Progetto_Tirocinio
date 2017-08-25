#include "Player.h"
#include <typeinfo>
#include "MapManager.h"
#include "GameManager.h"
#include "SoundManager.h"
#include "PlayerBullet.h"
#include "CombatScene.h"
#include "StrategyManager.h"
#include "Item.h"


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
		player->totalTime = 0;
		player->wait = 0;
		player->life = 3.0f;
		player->power = 1;
		player->defense = 1;
		player->actualScene = EMPTY;
		player->actualWeapon = NO_ONE;
		player->crawlingStrategy = NORMAL;
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
	case ATTACKING:
		break;
	case STUNNING:
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
	totalTime += dt;
	

	if (this->life <= 0) {
		this->runAction(FadeOut::create(1.0f));
		GameManager::getInstance()->loseGame();
	}

	auto tileCoord = arena->tileCoordForPosition(this->getPosition());
	auto map = this->getMap();
	if (this->getActualScene() == EXPLORATION) {
		this->controlPosition(this->getPosition());
	}
	if (this->getActualScene() == FIGHT) {
		if (map[(int)tileCoord.x][(int)tileCoord.y] == ESCAPE) {
			this->getParent()->unscheduleAllCallbacks();
			SoundManager::getInstance()->startWinSound();
			this->getMapFight()->finishBattle();
			return;
		}
	}
	if (deltaTime >= 0.5f) {
		auto prevState = this->previousState;
		if (previousState == MOVING || previousState == ATTACKING || previousState == DEFENDING || previousState == STUNNING) {
			this->setState(IDLE);
			return;
		}
		if (previousState == IDLE) {
			if (this->getActualScene() == EXPLORATION) {
				this->setState(MOVING);
				if (this->getCrawlingStrategy() == NORMAL) {
					Point destination = this->path.front();
					auto move = Sequence::create(MoveTo::create(0.5f, Vec2(destination.x, destination.y)), nullptr);
					this->runAction(move);
					this->path.pop_front();
				}
				else if(this->getCrawlingStrategy() == GO_TO_GOAL){
					//StrategyManager::getInstance()->goToGoal(this);
					/*Point destination = this->pathToGoal.front();
					auto move = Sequence::create(MoveTo::create(0.5f, Vec2(destination.x, destination.y)), nullptr);
					this->runAction(move);
					this->pathToGoal.pop_front();*/
					Point destination = this->route.front();
					auto move = Sequence::create(MoveTo::create(0.5f, Vec2(destination.x, destination.y)), nullptr);
					this->runAction(move);
					this->route.pop_front();
					
				}
				deltaTime = 0;
			}
			else if (this->getActualScene() == FIGHT) {
				if (totalTime >= 20.0f) {
					this->setState(DEFENDING);
				}
				if (_state == STUNNING) {
					this->runAction(DelayTime::create(0.5f));
				}
				else if (_state == DEFENDING) {
					StrategyManager::getInstance()->defensiveAsset(this);
				}
				else if (this->getStrategy() == DEFEAT_ENEMY) {
					StrategyManager::getInstance()->defeatEnemy(this);
				}
				else if (this->getStrategy() == DISTANCE_ATTACK) {
					StrategyManager::getInstance()->distanceAttack(this);
				}
				else if (this->getStrategy() == RETREAT) {
					StrategyManager::getInstance()->retreat(this);
				}
				else if (this->getStrategy() == BE_PATIENT) {
					StrategyManager::getInstance()->be_Patient(this);
				}
				else if (this->getStrategy() == STUN_ENEMY) {
					StrategyManager::getInstance()->stun_Enemy(this);
				}
			}
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
	if (this->getActualScene() == EXPLORATION) {
		auto tileCoordLeft = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y));
		if (tileCoordLeft.x == 0 || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == NONE || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WALL || mappa[(int)tileCoordLeft.x][(int)tileCoordLeft.y] == WATER) {
			return false;
		}
	}

	else if (this->getActualScene() == FIGHT) {
		auto tileCoordLeftBattle = arena->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y));
		if (tileCoordLeftBattle.x == 0 || mappa[(int)tileCoordLeftBattle.x][(int)tileCoordLeftBattle.y] == NONE || mappa[(int)tileCoordLeftBattle.x][(int)tileCoordLeftBattle.y] == WALL || mappa[(int)tileCoordLeftBattle.x][(int)tileCoordLeftBattle.y] == WATER) {
			return false;
		}
	}

	return true;
}

bool Player::beCarefulRight(Point position) {
	if (this->getActualScene() == EXPLORATION) {
		auto tileCoordRight = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y));
		if (tileCoordRight.x == 40 || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == NONE || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WALL || mappa[(int)tileCoordRight.x][(int)tileCoordRight.y] == WATER) {
			return false;
		}
	}

	else if (this->getActualScene() == FIGHT) {
		auto tileCoordRightBattle = arena->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y));
		if (tileCoordRightBattle.x == 7 || mappa[(int)tileCoordRightBattle.x][(int)tileCoordRightBattle.y] == NONE || mappa[(int)tileCoordRightBattle.x][(int)tileCoordRightBattle.y] == WALL || mappa[(int)tileCoordRightBattle.x][(int)tileCoordRightBattle.y] == WATER) {
			return false;
		}
	}

	return true;
}

bool Player::beCarefulUp(Point position) {
	//auto mappa = mapGame->getMap();

	if (this->getActualScene() == EXPLORATION) {
		auto tileCoordUp = mapGame->tileCoordForPosition(Point(position.x, position.y + TILE_HEIGHT));
		if (tileCoordUp.y == 40 || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == NONE || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WALL || mappa[(int)tileCoordUp.x][(int)tileCoordUp.y] == WATER) {
			return false;
		}
	}

	else if (this->getActualScene() == FIGHT) {
		auto tileCoordUpBattle = arena->tileCoordForPosition(Point(position.x, position.y + TILE_HEIGHT));
		if (tileCoordUpBattle.y == 7 || mappa[(int)tileCoordUpBattle.x][(int)tileCoordUpBattle.y] == NONE || mappa[(int)tileCoordUpBattle.x][(int)tileCoordUpBattle.y] == WALL || mappa[(int)tileCoordUpBattle.x][(int)tileCoordUpBattle.y] == WATER) {
			return false;
		}
	}

	return true;
}

bool Player::beCarefulDown(Point position) {
	//auto mappa = mapGame->getMap();

	if (this->getActualScene() == EXPLORATION) {
		auto tileCoordDown = mapGame->tileCoordForPosition(Point(position.x, position.y - TILE_HEIGHT));
		if (tileCoordDown.y == 0 || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == NONE || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WALL || mappa[(int)tileCoordDown.x][(int)tileCoordDown.y] == WATER) {
			return false;
		}
	}

	else if (this->getActualScene() == FIGHT) {
		auto tileCoordDownBattle = arena->tileCoordForPosition(Point(position.x, position.y - TILE_HEIGHT));
		if (tileCoordDownBattle.y == 0 || mappa[(int)tileCoordDownBattle.x][(int)tileCoordDownBattle.y] == NONE || mappa[(int)tileCoordDownBattle.x][(int)tileCoordDownBattle.y] == WALL || mappa[(int)tileCoordDownBattle.x][(int)tileCoordDownBattle.y] == WATER) {
			return false;
		}
	}

	return true;
}

bool Player::beCarefulLeftUp(Point position) {
	auto tileCoordLeftUp = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y + TILE_HEIGHT));

	if (mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == NULL || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == NONE || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WALL || mappa[(int)tileCoordLeftUp.x][(int)tileCoordLeftUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulLeftDown(Point position) {
	auto tileCoordLeftDown = mapGame->tileCoordForPosition(Point(position.x - TILE_WIDTH, position.y - TILE_HEIGHT));

	if (mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == NULL || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == NONE || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WALL || mappa[(int)tileCoordLeftDown.x][(int)tileCoordLeftDown.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulRightUp(Point position) {
	auto tileCoordRightUp = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y + TILE_HEIGHT));

	if (mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == NULL || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == NONE || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WALL || mappa[(int)tileCoordRightUp.x][(int)tileCoordRightUp.y] == WATER) {
		return false;
	}

	return true;
}

bool Player::beCarefulRightDown(Point position) {
	auto tileCoordRightDown = mapGame->tileCoordForPosition(Point(position.x + TILE_WIDTH, position.y - TILE_HEIGHT));

	if (mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == NULL || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == NONE || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WALL || mappa[(int)tileCoordRightDown.x][(int)tileCoordRightDown.y] == WATER) {
		return false;
	}

	return true;
}

void Player::controlPosition(Point position) {
	auto mappa = this->getMap();
	auto tileCoord = this->getMapGame()->tileCoordForPosition(position);
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
	if (this->path.size() > 0) {
		prev = path.back();
	}

	// Check if we have reached our goal.
	if (X == (int) goal.x && Y == (int) goal.y){
		path.push_back(Point(x, y));
		return true;
	}

	// If you are on a wall or already were here
	if (matrix[X][Y] == WALL || matrix[X][Y] == STEP) return false;

	matrix[X][Y] = STEP;
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

bool Player::solve2(int x, int y)
{
	Point A = mapGame->tileCoordForPosition(Point(x, y));
	int X = (int)A.x;
	int Y = (int)A.y;
	auto goal = mapGame->tileCoordForPosition(this->getDestination());

	Point prev;
	if (this->pathToGoal.size() > 0) {
		prev = pathToGoal.back();
	}

	// Check if we have reached our goal.
	if (X == (int)goal.x && Y == (int)goal.y) {
		pathToGoal.push_back(Point(x, y));
		return true;
	}

	// If you are on a wall or already were here
	if (matrix[X][Y] == WALL || matrix[X][Y] == WATER || matrix[X][Y] == NONE || matrix[X][Y] == STEP) return false;

	matrix[X][Y] = STEP;
	pathToGoal.push_back(Point(x, y));

	// Recursively search for our goal.
	if (x < MAP_SIZE_WIDTH && solve2(x + TILE_WIDTH, y))
	{
		return true;
	}
	if (y > 0 && solve2(x, y + TILE_HEIGHT))
	{
		return true;
	}
	if (x > 0 && solve2(x - TILE_WIDTH, y))
	{
		return true;
	}
	if (y < MAP_SIZE_HEIGHT && solve2(x, y - TILE_HEIGHT))
	{
		return true;
	}

	// Otherwise we need to backtrack and find another solution.
	this->pathToGoal.pop_back();

	return false;
}


int Player::solve3(int x, int y) {
	a = new queueNode[1600];
	auto goal = mapGame->tileCoordForPosition(this->getDestination());

	Point src = mapGame->tileCoordForPosition(Point(x,y));
	
	// Mark the source cell as visited
	matrix[(int)src.x][(int)src.y] = STEP;
	// distance of source cell is 0
	queueNode s = { Point(x,y), 0, help};
	q.push(s);  // Enqueue source cell
	int i = s.dist;

	while (!q.empty()) {
		queueNode current = q.front();
		Point point = current.pt;
		Point A = mapGame->tileCoordForPosition(point);
		a[i] = current;

		// If we have reached the destination cell,
		// we are done
		if (A.x == goal.x && A.y == goal.y) {
			this->createRoad();
			return current.dist;
		}

		// Otherwise dequeue the front cell in the queue
		// and enqueue its adjacent cells
		q.pop();

		matrix[(int)A.x][(int)A.y] = STEP;
		if (beCarefulRight(point)) {
			Point nextPRight = Point(point.x + TILE_WIDTH, point.y);
			Point B = mapGame->tileCoordForPosition(nextPRight);
			if (matrix[(int)B.x][(int)B.y] != STEP) {
				queueNode adjCellRight = { nextPRight, current.dist + 1, &a[i] };
				q.push(adjCellRight);
				matrix[(int)B.x][(int)B.y] = STEP;
				if (!this->contain(parents, adjCellRight)) {
					parents.push_back(adjCellRight);
				}
			}
		}
		if (beCarefulLeft(point)) {
			Point nextPLeft = Point(point.x - TILE_WIDTH, point.y);
			Point C = mapGame->tileCoordForPosition(nextPLeft);
			if (matrix[(int)C.x][(int)C.y] != STEP) {
				queueNode adjCellLeft = { nextPLeft, current.dist + 1, &a[i] };
				q.push(adjCellLeft);
				matrix[(int)C.x][(int)C.y] = STEP;
				if (!this->contain(parents, adjCellLeft)) {
					parents.push_back(adjCellLeft);
				}
			}
		}
		if (beCarefulUp(point)) {
			Point nextPUp = Point(point.x, point.y + TILE_HEIGHT);
			Point D = mapGame->tileCoordForPosition(nextPUp);
			if (matrix[(int)D.x][(int)D.y] != STEP) {
				queueNode adjCellUp = { nextPUp, current.dist + 1, &a[i] };
				q.push(adjCellUp);
				matrix[(int)D.x][(int)D.y] = STEP;
				if (!this->contain(parents, adjCellUp)) {
					parents.push_back(adjCellUp);
				}
			}
		}
		if (beCarefulDown(point)) {
			Point nextPDown = Point(point.x, point.y - TILE_HEIGHT);
			Point E = mapGame->tileCoordForPosition(nextPDown);
			if (matrix[(int)E.x][(int)E.y] != STEP) {
				queueNode adjCellDown = { nextPDown, current.dist + 1, &a[i] };
				q.push(adjCellDown);
				matrix[(int)E.x][(int)E.y] = STEP;
				if (!this->contain(parents, adjCellDown)) {
					parents.push_back(adjCellDown);
				}
			}
		}
		
		i += 1;
		

	}
	return 999999;
}

void Player::createRoad() {

	queueNode q = parents.back();
	Point p = q.pt;
	route.push_front(p);
	help = q.parent;
	while (help->pt != Point(32, 32)) {
		route.push_front(help->pt);
		help = help->parent;
	}

	route.push_front(help->pt);
}

bool Player::contain(std::list<queueNode> parents, queueNode p) {
	if (parents.empty()) {
		return false;
	}
	std::list<queueNode> aux = parents;
	while (!aux.empty()) {
		queueNode it = parents.front();
		if (it.pt == p.pt) {
			return true;
		}
		aux.pop_front();
	}
	return false;
}


void Player::lookingAround() {
	auto pos = this->getPosition();

	if (beCarefulUp(pos)) {
		neighbours[0] = Point(pos.x, pos.y + TILE_HEIGHT);
	}
	else {
		neighbours[0] = Point(0, 0);
	}
	
	if (beCarefulRight(pos)) {
		neighbours[1] = Point(pos.x + TILE_WIDTH, pos.y);
	}
	else {
		neighbours[1] = Point(0, 0);
	}
	
	if (beCarefulLeft(pos)) {
		neighbours[2] = Point(pos.x - TILE_WIDTH, pos.y);
	}
	else {
		neighbours[2] = Point(0, 0);
	}
	
	if (beCarefulDown(pos)) {
		neighbours[3] = Point(pos.x, pos.y - TILE_HEIGHT);
	}
	else {
		neighbours[3] = Point(0, 0);
	}
}

void Player::bestChoise() {
	auto position = this->getPosition();
	auto target = this->getDestination();
	auto coord = mapGame->tileCoordForPosition(position);
	int X = (int)coord.x;
	int Y = (int)coord.y;
	auto dist = target - position;
	if (dist.x >= 0) {
			if (neighbours[1] != Point(0,0) && matrix[X + 1][Y] != STEP) {
				this->setMovingState(MOVE_RIGHT);
				matrix[X + 1][Y] = STEP;
				return;
			}
		}
	if (dist.x < 0) {
			if (neighbours[2] != Point(0, 0) && matrix[X - 1][Y] != STEP) {
				this->setMovingState(MOVE_LEFT);
				matrix[X - 1][Y] = STEP;
				return;
			}
		}

	if (dist.y >= 0) {
			if (neighbours[0] != Point(0, 0) && matrix[X][Y + 1] != STEP) {
				this->setMovingState(MOVE_UP);
				matrix[X][Y + 1] = STEP;
				return;
			}
		}
	if (dist.y < 0) {
			if (neighbours[3] != Point(0, 0) && matrix[X][Y - 1] != STEP) {
				this->setMovingState(MOVE_DOWN);
				matrix[X][Y - 1] = STEP;
				return;
		}
	}
}


void Player::controlLeft() {
	if (neighbours[2] != Point(0, 0)) {
		this->setMovingState(MOVE_LEFT);
		return;
	}
}

void Player::controlUp() {
	if (neighbours[0] != Point(0, 0)) {
		this->setMovingState(MOVE_UP);
		return;
	}
}

void Player::controlRight() {
	if (neighbours[1] != Point(0, 0)) {
		this->setMovingState(MOVE_RIGHT);
		return;
	}
}

void Player::controlDown() {
	if (neighbours[3] != Point(0, 0)) {
		this->setMovingState(MOVE_DOWN);
		return;
	}
}


void Player::setTarget(Enemy* enemy) {
	target = enemy;
}

void Player::setTileMap(TMXTiledMap* tile) {
	this->tile = tile;
}

TMXTiledMap* Player::getTileMap(){
	return this->tile;
}

void Player::hurt() {
	SoundManager::getInstance()->startHurtScream();
	if (target->getActualWeapon() == GUN) {
		if (this->getActualProtection() == SHIELD)
		{
			this->life -= 0.5f / this->defense;
			return;
		}
		else {
			this->life -= 1.0f / this->defense;
			return;
		}
	}
	else if (target->getActualWeapon() == RIFLE) {
		if (this->getActualProtection() == SHIELD)
		{
			this->life -= 0.25f / this->defense;
			return;
		}
		else {
			this->life -= 0.5f / this->defense;
			return;
		}
	}
	else if (target->getActualWeapon() == SNIPER) {
		if (this->getActualProtection() == SHIELD)
		{
			this->life -= 0.75f / this->defense;
			return;
		}
		else {
			this->life -= 1.5f / this->defense;
			return;
		}
	}
	else if (target->getActualWeapon() == KNIFE) {
		if (this->getActualProtection() == ARMGUARD)
		{
			this->life -= 1.0f / this->defense;
			return;
		}
		else {
			this->life -= 2.0f / this->defense;
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
			this->life -= 1.0f / this->defense;
			return;
		}
		else
		{
		    this->life -= 2.0f / this->defense;
		    return;
	    }
	}
}

void Player::startAttacking() {
	auto w = this->getActualWeapon();
	if (w == GUN) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startGunSound();
			projectile = PlayerBullet::create("GunBullet.png");
			this->setWait(1);
		}
		else {
			this->setWait(this->getWait() - 1);
			return;
		}
	}
	else if (w == RIFLE) {
		SoundManager::getInstance()->startRifleSound();
		projectile = PlayerBullet::create("RifleBullet.png");
	}
	else if (w == KNIFE) {
		SoundManager::getInstance()->startKnifeSound();
		projectile = PlayerBullet::create("Knife.png");
	}
	else if (w == SNIPER) {
		if (this->getWait() == 0) {
		      SoundManager::getInstance()->startSniperSound();
		      projectile = PlayerBullet::create("SniperBullet.png");
			  this->setWait(2);
		}
		else {
			this->setWait(this->getWait() - 1);
			return;
		}
	}
	else if (w == GRENADE) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startGrenadeOutSound();
			projectile = PlayerBullet::create("Grenade.png");
			this->setWait(6);
		}
		else {
			this->setWait(this->getWait() - 1);
			return;
		}
	}
	else if (w == RADIATION) {
		if (this->getWait() == 0) {
			SoundManager::getInstance()->startGrenadeOutSound();
			projectile = PlayerBullet::create("Radiation.png");
			this->setWait(6);
		}
		else {
			this->setWait(this->getWait() - 1);
			return;
		}
	}
	if (projectile != nullptr) {
		projectile->setCombatScene(arena);
		projectile->setTargetEnemy(this->target);
		projectile->setWeapon(w);
		projectile->setPosition(this->getPosition());
		tile->addChild(projectile, 5);
		projectile->scheduleUpdate();
	}
}


void Player::gotcha(Item* item) {

	if (item->getType() == CURE) {
		this->setLife(3.0f);
	}
	if (item->getType() == POWER_UP) {
		this->power = this->getPower() + 1;
	}
	if (item->getType() == DEFENSE_UP) {
		this->defense = this->getDefense() + 1;
	}

}

void Player::setCombatScene(CombatScene* arena) {
	this->arena = arena;
}

void Player::setActualScene(Field scene) {
	this->actualScene = scene;
}

void Player::setActualWeapon(Weapon weapon) {
	this->actualWeapon = weapon;
}

void Player::setStrategy(Strategy strategy) {
	this->strategy = strategy;
}

Weapon Player::getActualWeapon() {
	return this->actualWeapon;
}

Field Player::getActualScene() {
	return this->actualScene;
}

Strategy Player::getStrategy() {
	return this->strategy;
}

void Player::setWait(int wait) {
	this->wait = wait;
}

int Player::getWait() {
	return this->wait;
}

int** Player::getMap() {
	return this->mappa;
}

void Player::setLife(float life) {
	this->life = life;
}

float Player::getLife() {
	return this->life;
}

MapManager* Player::getMapGame() {
	return this->mapGame;
}

CombatScene* Player::getMapFight() {
	return this->arena;
}

Enemy* Player::getTarget() {
	return this->target;
}

void Player::setDeltaTime(float time) {
	this->deltaTime = time;
}

void Player::setActualProtection(Protection protection) {
	this->actualProtection = protection;
}

Protection Player::getActualProtection() {
	return this->actualProtection;
}

std::list<Point> Player::getPath() {
	return this->path;
}

std::list<Point> Player::getPathToGoal() {
	return this->pathToGoal;
}

void Player::setCrawlingStrategy(Crawling crawling) {
	this->crawlingStrategy = crawling;
}

Crawling Player::getCrawlingStrategy() {
	return this->crawlingStrategy;
}

void Player::setPower(int power) {
	this->power = power;
}

int Player::getPower() {
	return this->power;
}

void Player::setDefense(int defense) {
	this->defense = defense;
}

int Player::getDefense() {
	return this->defense;
}




void Player::setMatrix() {
	auto map = this->getMap();

	matrix = new int*[MAP_WIDTH];
	for (int i = 0; i < MAP_WIDTH; ++i)
		matrix[i] = new int[MAP_HEIGHT];

	for (int i = 0; i < MAP_WIDTH; i++) {
		for (int j = 0; j < MAP_HEIGHT; j++) {
			matrix[i][j] = map[i][j];
		}
	}
}