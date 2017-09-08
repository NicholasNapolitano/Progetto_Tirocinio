#include "StrategyManager.h"
#include "Player.h"
#include "Enemy.h"
#include "CombatScene.h"

USING_NS_CC;

//Singleton instance of the class

StrategyManager* StrategyManager::instance = 0;

//Constructor

StrategyManager::StrategyManager() {
}

//Return the instance of the class

StrategyManager* StrategyManager::getInstance()
{
	if (instance == 0)
		instance = new StrategyManager;
	return instance;
}

//Defensive Strategy (on the CombatScene)

void StrategyManager::defensiveAsset(Player* player) {
	if (player->getTarget() != NULL) {
		player->lookingAround();
		auto diff2 = player->getTarget()->getPosition() - player->getPosition();
		if (((abs(diff2.x) <= 60 && abs(diff2.y) <= 60) && (player->getActualWeapon() == GUN)) || ((abs(diff2.x) <= 30 && abs(diff2.y) <= 30) && (player->getActualWeapon() == KNIFE))) {
			player->setState(ATTACKING);
			player->startAttacking();
			player->setDeltaTime(0);
			return;
		}
		else {
			player->setState(MOVING);
			auto road = Point(159, 159) - player->getPosition();
			if (road.x >= 0) {
				player->controlRight();
			}
			else if (road.y >= 0) {
				player->controlUp();
			}
			else if (road.x < 0) {
				player->controlLeft();
			}
			else if (road.y < 0) {
				player->controlDown();
			}
			player->setDeltaTime(0);
			return;
		}
	}
}

//    ----- DEFEAT ENEMY STRATEGY -----

void StrategyManager::defeatEnemy(Player* player) {
	if (player->getTarget() != NULL) {
		player->lookingAround();
		auto diff = player->getTarget()->getPosition() - player->getPosition();
		if (((abs(diff.x) <= 60 || abs(diff.y) <= 60) && (player->getActualWeapon() == GUN)) || ((abs(diff.x) <= 120 || abs(diff.y) <= 120) && (player->getActualWeapon() == RIFLE)) || ((abs(diff.x) <= 200 || abs(diff.y) <= 200) && (player->getActualWeapon() == SNIPER)) || ((abs(diff.x) <= 130 || abs(diff.y) <= 130) && (player->getActualWeapon() == GRENADE)) || ((abs(diff.x) <= 20 || abs(diff.y) <= 20) && (player->getActualWeapon() == KNIFE)) || ((abs(diff.x) <= 130 || abs(diff.y) <= 130) && (player->getActualWeapon() == RADIATION))) {
			player->setState(ATTACKING);
			player->startAttacking();
			player->setDeltaTime(0);
			return;
		}
		player->setState(MOVING);
		if (abs(diff.x) > abs(diff.y)) {
			if (diff.x > 0) {
				player->controlRight();
			}
			else {
				player->controlLeft();
			}
		}
		else {
			if (diff.y > 0) {
				player->controlUp();
			}
			else {
				player->controlDown();
			}
		}
		player->setDeltaTime(0);
		return;
	}
}

//    ----- DISTANCE ATTACK STRATEGY -----

void StrategyManager::distanceAttack(Player* player) {
	if (player->getTarget() != NULL) {
		player->lookingAround();
		auto diff1 = player->getTarget()->getPosition() - player->getPosition();
		if (((abs(diff1.x) >= 60 || abs(diff1.y) >= 60) && (player->getActualWeapon() == GUN)) || ((abs(diff1.x) >= 100 || abs(diff1.y) >= 100) && (player->getActualWeapon() == RIFLE)) || ((abs(diff1.x) >= 150 || abs(diff1.y) >= 150) && (player->getActualWeapon() == SNIPER)) || ((abs(diff1.x) >= 120 || abs(diff1.y) >= 120) && (player->getActualWeapon() == GRENADE)) || ((abs(diff1.x) >= 30 || abs(diff1.y) >= 30) && (player->getActualWeapon() == KNIFE)) || ((abs(diff1.x) >= 140 || abs(diff1.y) >= 140) && (player->getActualWeapon() == RADIATION))) {
			player->setState(ATTACKING);
			player->startAttacking();
			player->setDeltaTime(0);
			return;
		}
		else {
			player->setState(MOVING);
			if (abs(diff1.x) < 100 && player->getPosition().x < 150) {
				player->controlRight();
				player->setDeltaTime(0);
				return;
			}
			else if (abs(diff1.x) < 100 && player->getPosition().x >= 150) {
				if (player->getPosition().y < 150) {
					player->controlUp();
					player->setDeltaTime(0);
					return;
				}
				else if (player->getPosition().y >= 150) {
					player->controlLeft();
					player->setDeltaTime(0);
					return;
				}
			}
			else player->controlDown();
			player->setDeltaTime(0);
			return;
		}
	}
}

//    ----- RETREAT STRATEGY -----

void StrategyManager::retreat(Player* player) {
	auto meta = Point(159, 159);
	if (player->getTarget() != NULL) {
		player->lookingAround();
		auto diff2 = player->getTarget()->getPosition() - player->getPosition();
		if (((abs(diff2.x) <= 60 && abs(diff2.y) <= 60) && (player->getActualWeapon() == GUN)) || ((abs(diff2.x) <= 30 && abs(diff2.y) <= 30) && (player->getActualWeapon() == KNIFE))) {
			player->setState(ATTACKING);
			player->startAttacking();
			player->setDeltaTime(0);
			return;
		}
		else {
			player->setState(MOVING);
			auto road = meta - player->getPosition();
			if (road.y >= 0) {
				player->controlUp();
			}
			else if (road.x >= 0) {
				player->controlRight();
			}
			else if (road.x < 0) {
				player->controlLeft();
			}
			else if (road.y < 0) {
				player->controlDown();
			}
			player->setDeltaTime(0);
			return;
		}
	}
}

//    ----- BE PATIENT STRATEGY -----

void StrategyManager::be_Patient(Player* player) {
	if (player->getTarget() != NULL) {
		player->lookingAround();
		if (player->getTarget()->getState() == DEFENDING) {
			this->defensiveAsset(player);
		}
		auto diff3 = player->getTarget()->getPosition() - player->getPosition();
		if (((abs(diff3.x) <= 50 || abs(diff3.y) <= 50) && (player->getActualWeapon() == GUN)) || ((abs(diff3.x) <= 100 || abs(diff3.y) <= 100) && (player->getActualWeapon() == RIFLE)) || ((abs(diff3.x) <= 150 || abs(diff3.y) <= 150) && (player->getActualWeapon() == SNIPER)) || ((abs(diff3.x) <= 120 || abs(diff3.y) <= 120) && (player->getActualWeapon() == GRENADE)) || ((abs(diff3.x) <= 30 || abs(diff3.y) <= 30) && (player->getActualWeapon() == KNIFE))) {
			player->setState(ATTACKING);
			player->startAttacking();
			player->setDeltaTime(0);
			return;
		}
		else {
			player->setState(MOVING);
			auto fakePos = player->getTarget()->getPosition() - player->getPosition();
			if (fakePos.x < 20 || fakePos.y < 20) {
				Moving move = (Moving)RandomHelper::random_int(0, 1);
				if (move == MOVE_UP) {
					player->controlUp();
				}
				if (move == MOVE_RIGHT) {
					player->controlRight();
				}
			}
			else {
				//do Nothing
			}
			player->setDeltaTime(0);
			return;
		}
	}
}

//    ----- STUN ENEMY STRATEGY -----

void StrategyManager::stun_Enemy(Player* player) {
	if (player->getTarget() != NULL) {
		player->lookingAround();
		if (player->getTarget()->getState() == DEFENDING) {
			this->defensiveAsset(player);
		}
		else if (player->getTarget()->getState() == STUNNING){
			player->setState(MOVING);
			auto road1 = Point(159, 159) - player->getPosition();
			if (road1.x >= 0) {
				player->controlRight();
			}
			else if (road1.y >= 0) {
				player->controlUp();
			}
			else if (road1.x < 0) {
				player->controlLeft();
			}
			else if (road1.y < 0) {
				player->controlDown();
			}
			player->setDeltaTime(0);
			return;
		}
		else {
			auto diff3 = player->getTarget()->getPosition() - player->getPosition();
			if (player->getActualWeapon() == RADIATION) {
				player->setState(ATTACKING);
				player->startAttacking();
				player->setDeltaTime(0);
				return;
			}
		}
	}
}

//    ----- SENTRY BEHAVIOUR -----

void StrategyManager::sentryBehaviour(Enemy* enemy) {
	if (enemy->getActualScene() == EXPLORATION) {
		enemy->lookingAround();
		auto diff = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (abs(diff.x) < 100 || abs(diff.x) < 100) {
			enemy->setState(ATTACKING);
			auto dest = enemy->getTarget()->getPosition();
			auto location = enemy->getPosition();
			auto distance = dest - location;
			if (abs(distance.x) > abs(distance.y)) {
				if (distance.x > 0) {
					enemy->controlRight();
				}
				else {
					enemy->controlLeft();
				}
			}
			else {
				if (distance.y > 0) {
					enemy->controlUp();
				}
				else {
					enemy->controlDown();
				}
			}
			if (enemy->getBoundingBox().intersectsRect(enemy->getTarget()->getBoundingBox())) {
				enemy->getMapGame()->beginBattle(enemy);
				return;
			}
			enemy->setDeltaTime(0);
			return;
		}
		enemy->setState(MOVING);
		auto location = enemy->getPosition();
		auto distance = enemy->getDestination() - location;
		if (abs(distance.x) > abs(distance.y)) {
			if (distance.x > 0) {
				enemy->controlRight();
			}
			else {
				enemy->controlLeft();
			}
		}
		else {
			if (distance.y > 0) {
				enemy->controlUp();
			}
			else {
				enemy->controlDown();
			}
		}
		if (enemy->getMapGame()->tileCoordForPosition(location) == enemy->getMapGame()->tileCoordForPosition(enemy->getFirstDestination()))
			enemy->setDestination(enemy->getSecondDestination());
		else if (enemy->getMapGame()->tileCoordForPosition(location) == enemy->getMapGame()->tileCoordForPosition(enemy->getSecondDestination()))
			enemy->setDestination(enemy->getFirstDestination());
		enemy->setDeltaTime(0);
	}
	else if (enemy->getActualScene() == FIGHT) {
		enemy->lookingAround();
		if (enemy->getTotalTime() >= 20.0f || (enemy->getLife() <= 0.5f && enemy->getTarget()->getLife() > 2)) {
			enemy->setState(DEFENDING);
		}
		if (enemy->getState() == STUNNING) {
			enemy->runAction(DelayTime::create(0.5f));
			return;
		}
		if (enemy->getState() == DEFENDING) {
			auto meta = Point(6, 6);
			if (enemy->getTarget() != NULL) {
				auto diff2 = enemy->getTarget()->getPosition() - enemy->getPosition();
				if (((abs(diff2.x) <= 60 || abs(diff2.y) <= 60) && (enemy->getActualWeapon() == GUN)) || ((abs(diff2.x) <= 30 || abs(diff2.y) <= 30) && (enemy->getActualWeapon() == KNIFE))) {
				enemy->setState(ATTACKING);
				enemy->startAttacking();
				enemy->setDeltaTime(0);
				return;
				}
				else {
				enemy->setState(MOVING);
				auto road = meta - enemy->getPosition();
				if (abs(road.x) > abs(road.y)) {
					if (road.x > 0) {
						enemy->controlRight();
					}
					else {
						enemy->controlLeft();
					}
				}
				else {
					if (road.y > 0) {
						enemy->controlUp();
					}
					else {
						enemy->controlDown();
					}
				}
				enemy->setDeltaTime(0);
				return;
			}
		  }
		}
		auto diff = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (((abs(diff.x) <= 60 || abs(diff.y) <= 60) && (enemy->getActualWeapon() == GUN)) || ((abs(diff.x) <= 120 || abs(diff.y) <= 120) && (enemy->getActualWeapon() == RIFLE)) || ((abs(diff.x) <= 20 || abs(diff.y) <= 20) && (enemy->getActualWeapon() == KNIFE))) {
			enemy->setState(ATTACKING);
			enemy->startAttacking();
			enemy->setDeltaTime(0);
			return;
		}
		enemy->setState(MOVING);
		auto dist = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (abs(dist.x) > abs(dist.y)) {
			if (dist.x > 0) {
				enemy->controlRight();
			}
			else {
				enemy->controlLeft();
			}
		}
		else {
			if (dist.y > 0) {
				enemy->controlUp();
			}
			else {
				enemy->controlDown();
			}
		}
		enemy->setDeltaTime(0);
		return;
	}

}

//    ----- KAMIKAZE BEHAVIOUR -----

void StrategyManager::kamikazeBehaviour(Enemy* enemy) {
	if (enemy->getActualScene() == EXPLORATION) {
		enemy->lookingAround();
		auto diff = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (abs(diff.x) < 150 || abs(diff.x) < 150) {
			enemy->setState(ATTACKING);
			auto dest = enemy->getTarget()->getPosition();
			auto location = enemy->getPosition();
			auto distance = dest - location;
			if (abs(distance.x) > abs(distance.y)) {
				if (distance.x > 0) {
					enemy->controlRight();
				}
				else {
					enemy->controlLeft();
				}
			}
			else {
				if (distance.y > 0) {
					enemy->controlUp();
				}
				else {
					enemy->controlDown();
				}
			}
			if (enemy->getBoundingBox().intersectsRect(enemy->getTarget()->getBoundingBox())) {
				enemy->getMapGame()->beginBattle(enemy);
				return;
			}
			enemy->setDeltaTime(0);
			return;
		}
		enemy->setState(MOVING);
		if (enemy->getWait() == 0) {
			Moving random = (Moving)RandomHelper::random_int(0, 3);
			if (random == MOVE_UP) {
				enemy->controlUp();
			}
			if (random == MOVE_RIGHT) {
				enemy->controlRight();
			}
			if (random == MOVE_DOWN) {
				enemy->controlDown();
			}
			if (random == MOVE_LEFT) {
				enemy->controlLeft();
			}
			enemy->setWait(3);
		}
		enemy->setWait(enemy->getWait() - 1);
		enemy->setDeltaTime(0);
	}
	else if (enemy->getActualScene() == FIGHT) {
		auto dist1 = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (abs(dist1.x) <= 20 || abs(dist1.y) <= 20) {
			enemy->setState(ATTACKING);
			enemy->boom();
			return;
		}
		enemy->lookingAround();
		enemy->setState(MOVING);
		if (abs(dist1.x) > abs(dist1.y)) {
			if (dist1.x > 0) {
				enemy->controlRight();
			}
			else {
				enemy->controlLeft();
			}
		}
		else {
			if (dist1.y > 0) {
				enemy->controlUp();
			}
			else {
				enemy->controlDown();
			}
		}
		enemy->setDeltaTime(0);
		return;
	}

}

//    ----- TOWER BEHAVIOUR -----

void StrategyManager::towerBehaviour(Enemy* enemy) {
	if (enemy->getActualScene() == EXPLORATION) {
		//doNothing
		if (enemy->getBoundingBox().intersectsRect(enemy->getTarget()->getBoundingBox())) {
			enemy->getMapGame()->beginBattle(enemy);
			return;
		}
		enemy->setDeltaTime(0);
	}
	else if (enemy->getActualScene() == FIGHT) {
			enemy->setState(ATTACKING);
			enemy->startAttacking();
			enemy->setDeltaTime(0);
			return;
		}
}

//    ----- SCOUT BEHAVIOUR -----

void StrategyManager::scoutBehaviour(Enemy* enemy) {
	if (enemy->getActualScene() == EXPLORATION) {
		enemy->lookingAround();
		auto diff = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (abs(diff.x) < 200 || abs(diff.x) < 200) {
			enemy->setState(ATTACKING);
			auto dest = enemy->getTarget()->getPosition();
			auto location = enemy->getPosition();
			auto distance = dest - location;
			if (abs(distance.x) > abs(distance.y)) {
				if (distance.x > 0) {
					enemy->controlRight();
				}
				else {
					enemy->controlLeft();
				}
			}
			else {
				if (distance.y > 0) {
					enemy->controlUp();
				}
				else {
					enemy->controlDown();
				}
			}
			if (enemy->getBoundingBox().intersectsRect(enemy->getTarget()->getBoundingBox())) {
				enemy->getMapGame()->beginBattle(enemy);
				return;
			}
			enemy->setDeltaTime(0);
			return;
		}
		enemy->setState(MOVING);
		auto location1 = enemy->getPosition();
		auto distance = enemy->getDestination() - location1;
		if (abs(distance.x) > abs(distance.y)) {
			if (distance.x > 0) {
				enemy->controlRight();
			}
			else {
				enemy->controlLeft();
			}
		}
		else {
			if (distance.y > 0) {
				enemy->controlUp();
			}
			else {
				enemy->controlDown();
			}
		}
		if (enemy->getMapGame()->tileCoordForPosition(location1) == enemy->getMapGame()->tileCoordForPosition(enemy->getFirstDestination()))
			enemy->setDestination(enemy->getSecondDestination());
		else if (enemy->getMapGame()->tileCoordForPosition(location1) == enemy->getMapGame()->tileCoordForPosition(enemy->getSecondDestination()))
			enemy->setDestination(enemy->getFirstDestination());
		enemy->setDeltaTime(0);
	}
	else if (enemy->getActualScene() == FIGHT) {
		enemy->lookingAround();
		if (enemy->getTotalTime() >= 10.0f || (enemy->getLife() <= 1.0f && enemy->getTarget()->getLife() >= 2)) {
			enemy->setState(DEFENDING);
		}
		if (enemy->getState() == DEFENDING) {
			auto meta = Point(6, 6);
			if (enemy->getTarget() != NULL) {
				auto diff2 = enemy->getTarget()->getPosition() - enemy->getPosition();
				if (((abs(diff2.x) <= 30 || abs(diff2.y) <= 30))) {
				enemy->setState(ATTACKING);
				enemy->startAttacking();
				enemy->setDeltaTime(0);
				return;
				}
				else {
				enemy->setState(MOVING);
				auto road2 = meta - enemy->getPosition();
				if (abs(road2.x) > abs(road2.y)) {
					if (road2.x > 0) {
						enemy->controlRight();
					}
					else {
						enemy->controlLeft();
					}
				}
				else {
					if (road2.y > 0) {
						enemy->controlUp();
					}
					else {
						enemy->controlDown();
					}
				}
				enemy->setDeltaTime(0);
				return;
			}
		}
	}
		auto diff = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (abs(diff.x) < 150 || abs(diff.x) < 150) {
			enemy->setState(ATTACKING);
			enemy->startAttacking();
			enemy->setDeltaTime(0);
			return;
		}
		enemy->setState(MOVING);
		auto dist = enemy->getTarget()->getPosition() - enemy->getPosition();
		if (enemy->decision == 3) {
			enemy->controlDown();
			enemy->decision--;
			enemy->setDeltaTime(0);
			return;
		}
		if (enemy->decision == 2) {
			enemy->controlLeft();
			enemy->decision--;
			enemy->setDeltaTime(0);
			return;
		}
		if (enemy->decision == 1) {
			enemy->controlUp();
			enemy->decision--;
			enemy->setDeltaTime(0);
			return;
		}
		if (enemy->decision == 0) {
			enemy->controlRight();
			enemy->decision = 3;
			enemy->setDeltaTime(0);
			return;
		}
	}

}