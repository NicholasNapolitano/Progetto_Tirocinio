#include "GameManager.h"
#include "MapManager.h"
#include "Player.h"
#include "StartMenu.h"
#include <typeinfo>

USING_NS_CC;

GameManager::GameManager() {

}

GameManager::~GameManager() {

}

void GameManager::startGame() {
	auto scene = MapManager::createScene();
	Director::getInstance()->pushScene(scene);
}

GameManager* GameManager::getCore() {
}