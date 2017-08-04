#include "GameManager.h"
#include "SoundManager.h"
#include "MapManager.h"
#include "CombatScene.h"
#include "Player.h"
#include "StartMenu.h"
#include "StrategyMenu.h"
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

void GameManager::selectStrategy() {
	auto scene = StrategyMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

void GameManager::playGame(Player* player) {
	Scene* scene = MapManager::createScene();
	MapManager* gameScene = (MapManager*)scene->getChildByName("MapManager");
	gameScene->getPlayer()->setStrategy(player->getStrategy());
	gameScene->getPlayer()->setActualWeapon(player->getActualWeapon());
	Director::getInstance()->pushScene(scene);
	SoundManager::getInstance()->startGameMusic();
}

void GameManager::resumeExploration() {
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startGameMusic();
	Director::getInstance()->popScene();
	resumeGame();
}

void GameManager::startBattle(Enemy* enemy, Player* player) {
	Scene* scene = CombatScene::createScene();
	CombatScene* gameScene = (CombatScene*)scene->getChildByName("CombatScene");
	gameScene->getPlayer()->setStrategy(player->getStrategy());
	gameScene->getPlayer()->setActualWeapon(player->getActualWeapon());
	gameScene->getEnemy()->setActualWeapon(enemy->getActualWeapon());
	Director::getInstance()->pushScene(scene);
	SoundManager::getInstance()->startBattleMusic();
}

void GameManager::pauseGame() {
	Director::getInstance()->pause();
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->stopEffects();
}

void GameManager::resumeGame() {
	SoundManager::getInstance()->resumeEffects();
	SoundManager::getInstance()->resumeMusic();
}

void GameManager::winGame() {
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Win =D");
	Director::getInstance()->replaceScene(gameOverScene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startVictorySound();
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

