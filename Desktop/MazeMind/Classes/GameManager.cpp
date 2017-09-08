#include "GameManager.h"
#include "SoundManager.h"
#include "MapManager.h"
#include "CombatScene.h"
#include "Player.h"
#include "StartMenu.h"
#include "StrategyMenu.h"
#include "GameOverScene.h"
#include "HudLayer.h"
#include "HighScoreScene.h"
#include "SettingsScene.h"
#include "PresentationScene.h"
#include <typeinfo>

USING_NS_CC;

//Singleton instance of the class

GameManager* GameManager::instance = 0;

//Constructor

GameManager::GameManager() {
}

//Return the instance of the class

GameManager* GameManager::getInstance()
{
	if (instance == 0)
		instance = new GameManager;
	return instance;
}

//Go to the menu

void GameManager::startGame() {
	auto scene = StartMenu::createScene();
	Director::getInstance()->pushScene(scene);
	SoundManager::getInstance()->startMenuMusic();
}

//Go to the Stategymenu

void GameManager::selectStrategy() {
	auto scene = StrategyMenu::createScene();
	Director::getInstance()->pushScene(TransitionFade::create(1.0f, scene));
}

//Go to the Labyrinth

void GameManager::playGame(Player* player) {
	Scene* scene = MapManager::createScene();
	MapManager* gameScene = (MapManager*)scene->getChildByName("MapManager");
	gameScene->getPlayer()->setStrategy(player->getStrategy());
	gameScene->getPlayer()->setActualWeapon(player->getActualWeapon());
	gameScene->getPlayer()->setActualProtection(player->getActualProtection());
	gameScene->getPlayer()->setCrawlingStrategy(player->getCrawlingStrategy());
	Director::getInstance()->pushScene(scene);
	SoundManager::getInstance()->startGameMusic();
}

//Return to the Labyrinth after a battle

void GameManager::resumeExploration(Player* player) {
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startGameMusic();
	player->getMapGame()->getHud()->setScore(player->getMapFight()->getHud()->getScore());
	Director::getInstance()->popScene();
	player->getMapGame()->getPlayer()->setLife(player->getLife());
	resumeGame();
}

//Go to the CombatScene to start a battle

void GameManager::startBattle(Enemy* enemy, Player* player) {
	Scene* scene = CombatScene::createScene();
	CombatScene* gameScene = (CombatScene*)scene->getChildByName("CombatScene");
	gameScene->getPlayer()->setMapGame(player->getMapGame());
	gameScene->getHud()->setScore(player->getMapGame()->getHud()->getScore());
	gameScene->getPlayer()->setStrategy(player->getStrategy());
	gameScene->getPlayer()->setActualWeapon(player->getActualWeapon());
	gameScene->getPlayer()->setActualProtection(player->getActualProtection());
	gameScene->getPlayer()->setMapGame(player->getMapGame());
	gameScene->setEnemy(enemy->getType());
	gameScene->getEnemy()->setActualWeapon(enemy->getActualWeapon());
	gameScene->getEnemy()->setActualProtection(enemy->getActualProtection());
	Director::getInstance()->pushScene(scene);
	SoundManager::getInstance()->startBattleMusic();
}

//Pause the Game

void GameManager::pauseGame() {
	Director::getInstance()->pause();
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->stopEffects();
}

//Resume the Game

void GameManager::resumeGame() {
	SoundManager::getInstance()->resumeEffects();
	SoundManager::getInstance()->resumeMusic();
	Director::getInstance()->resume();
}

//Go to GameOverScene (Victory)

void GameManager::winGame() {
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Win =D");
	Director::getInstance()->replaceScene(gameOverScene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startVictorySound();
}

//Go to GameOverScene (Defeat)

void GameManager::loseGame() {
	GameOverScene *gameOverScene = GameOverScene::create();
	gameOverScene->getLayer()->getLabel()->setString("You Lose :(");
	Director::getInstance()->replaceScene(gameOverScene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startLoseSound();
}

//Close the Game

void GameManager::endGame() {
	Director::getInstance()->end();
}

//Return to the Menu

void GameManager::restartGame() {
	auto scene = StartMenu::createScene();
	Director::getInstance()->replaceScene(scene);
	SoundManager::getInstance()->stopMusic();
	SoundManager::getInstance()->startMenuMusic();
}

//It Controls if the Game is in pause

bool GameManager::inPause() {
	return Director::getInstance()->isPaused();
}

//Go to HighScoreScene

void GameManager::viewHighScore() {
	auto scene = HighScoreScene::createScene(0);
	Director::getInstance()->pushScene(TransitionFlipX::create(1.0f, scene));
}

//Go To SettingsScene

void GameManager::changeSettings() {
	auto scene = SettingsScene::createScene();
	Director::getInstance()->pushScene(TransitionFlipY::create(1.0f, scene));
}

//Add extra score to the player according to some hidden achievements

void GameManager::setExtraScore(Player* player) {

	Protection protect = player->getActualProtection();

	//Achevement: BRAVE
	if (protect == ANYTHING) {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 150);
	}
		    
	Weapon weapon = player->getActualWeapon();

	//Achievement: CRAZY
	if (weapon == NO_ONE) {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 300);
	}

	int life = player->getLife();
	player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 50 * life);

	Crawling strategy = player->getCrawlingStrategy();
	
	//Achievement: CURIOUS
	if (strategy == NORMAL) {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 500);
	}

	//Achievemnt: PACIFIST
	int platelets = player->getPlatelets();
	if (platelets == 0) {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 200);
	}
	else {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 50 * platelets);
	}

	//Achievement: ORIGINAL
	int objects = player->getObjects();
	if (objects == 0) {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 200);
	}
	else {
		player->getMapGame()->getHud()->setScore(player->getMapGame()->getHud()->getScore() + 50 * objects);
	}


	return;
}

//Go To PresentationScene

void GameManager::startPresentation() {
	auto scene = PresentationScene::create();
	Director::getInstance()->pushScene(scene);
}
