#include "GameManager.h"
#include "SoundManager.h"
#include "MapManager.h"
#include "Player.h"
#include "StartMenu.h"
#include "GameOverScene.h"
#include <typeinfo>

USING_NS_CC;

GameManager* GameManager::instance = 0;

GameManager::GameManager() {
}

GameManager* GameManager::getInstance()
{
	if (instance == 0)
		instance = new GameManager;
	return instance;
}

void GameManager::startGame() {
	auto scene = StartMenu::createScene();
	Director::getInstance()->runWithScene(scene);
	SoundManager::getInstance()->startMenuMusic();
}

void GameManager::playGame() {
	auto scene = MapManager::createScene();
	Director::getInstance()->pushScene(scene);
	SoundManager::getInstance()->startGameMusic();
}

void GameManager::pauseGame() {
	Director::getInstance()->pause();
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->stopEffects();
}

void GameManager::resumeGame() {
	Director::getInstance()->resume();
	SoundManager::getInstance()->resumeEffects();
	SoundManager::getInstance()->resumeMusic();
}

void GameManager::winGame() {
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Win =D");
	Director::getInstance()->replaceScene(gameOverScene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startWinSound();
}

void GameManager::loseGame() {
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Lose :(");
	Director::getInstance()->replaceScene(gameOverScene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startLoseSound();
}

void GameManager::endGame() {
	Director::getInstance()->end();
}

void GameManager::restartGame() {
	auto scene = StartMenu::createScene();
	Director::getInstance()->replaceScene(scene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startMenuMusic();
}

bool GameManager::inPause() {
	return Director::getInstance()->isPaused();
}

