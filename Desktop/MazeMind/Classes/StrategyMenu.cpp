#include "StrategyMenu.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "Enums.h"
#include "ui/CocosGUI.h"
#include "Player.h"
#include "SoundManager.h"

USING_NS_CC;

Scene* StrategyMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StrategyMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StrategyMenu::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	this->core = GameManager::getInstance();
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Screen real dimensions
	auto vWidth = visibleSize.width;
	auto vHeight = visibleSize.height;

	// Original image
	auto backOrig = Sprite::create("Background.png");
	auto oWidth = backOrig->getContentSize().width;
	auto oHeight = backOrig->getContentSize().height;
	backOrig->setFlippedY(true);
	backOrig->setScale(vWidth / oWidth, vHeight / oHeight); // backOrig scaled to screen size
	backOrig->setPosition(vWidth / 2, vHeight / 2);

	// Create new texture with background in the exact size of the screen
	auto renderTexture = RenderTexture::create(vWidth, vHeight, Texture2D::PixelFormat::RGBA8888);
	renderTexture->begin();
	backOrig->visit();
	renderTexture->end();

	// Create new Sprite without scale, which perfoms much better
	background = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	background->setPosition(vWidth / 2, vHeight / 2);
	addChild(background);

	scrollView = ui::ScrollView::create();
	scrollView->setClippingEnabled(true);
	scrollView->setTouchEnabled(true);
	scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->getInnerContainer()->setLayoutType(ui::Layout::Type::VERTICAL);
	scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height * 3));
	scrollView->setPosition(Vec2(0, 0));
	scrollView->retain();
	this->addChild(scrollView);


	this->player = Player::create("Player.png");
	this->addChild(player);
	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(StrategyMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	strategySelected = Sprite::create("Selected.png");
	scrollView->addChild(strategySelected, 1);
	weaponSelected = Sprite::create("Selected.png");
	scrollView->addChild(weaponSelected, 1);
	protectionSelected = Sprite::create("Selected.png");
	scrollView->addChild(protectionSelected, 1);
	crawlingSelected = Sprite::create("Selected.png");
	scrollView->addChild(crawlingSelected, 1);

	Sprite* _gun_ = Sprite::create("Gun.png");
	Sprite* _rifle_ = Sprite::create("Rifle.png");
	Sprite* _sniper_ = Sprite::create("Sniper.png");
	Sprite* _grenade_ = Sprite::create("GrenadeSprite.png");
	Sprite* _knife_ = Sprite::create("KnifeSprite.png");
	Sprite* _radiation_ = Sprite::create("RadiationSprite.png");
	Sprite* _shield_ = Sprite::create("Shield.png");
	Sprite* _armor_ = Sprite::create("Armor.png");
	Sprite* _mask_ = Sprite::create("Mask.png");
	Sprite* _armguard_ = Sprite::create("Armguard.png");


	auto menu_item_1 = MenuItemFont::create("--> EnjoyTheGame <-- ", CC_CALLBACK_1(StrategyMenu::enjoyTheGame, this));
	auto menu_item_2 = MenuItemSprite::create(_gun_, _gun_, CC_CALLBACK_1(StrategyMenu::gun, this));
	auto menu_item_3 = MenuItemFont::create("Defeat_Enemy", CC_CALLBACK_1(StrategyMenu::defeatEnemy, this));
	auto menu_item_4 = MenuItemFont::create("Distance_Attack", CC_CALLBACK_1(StrategyMenu::distanceAttack, this));
	auto menu_item_5 = MenuItemSprite::create(_rifle_, _rifle_, CC_CALLBACK_1(StrategyMenu::rifle, this));
	auto menu_item_6 = MenuItemSprite::create(_sniper_, _sniper_, CC_CALLBACK_1(StrategyMenu::sniper, this));
	auto menu_item_7 = MenuItemSprite::create(_grenade_, _grenade_, CC_CALLBACK_1(StrategyMenu::grenade, this));
	auto menu_item_8 = MenuItemFont::create("Retreat", CC_CALLBACK_1(StrategyMenu::retreat, this));
	auto menu_item_9 = MenuItemSprite::create(_knife_, _knife_, CC_CALLBACK_1(StrategyMenu::knife, this));
	auto menu_item_10 = MenuItemFont::create("Be_Patient", CC_CALLBACK_1(StrategyMenu::bePatient, this));
	auto menu_item_11 = MenuItemSprite::create(_shield_, _shield_, CC_CALLBACK_1(StrategyMenu::shield, this));
	auto menu_item_12 = MenuItemSprite::create(_armor_, _armor_, CC_CALLBACK_1(StrategyMenu::armor, this));
	auto menu_item_13 = MenuItemSprite::create(_mask_, _mask_, CC_CALLBACK_1(StrategyMenu::mask, this));
	auto menu_item_14 = MenuItemSprite::create(_radiation_, _radiation_, CC_CALLBACK_1(StrategyMenu::radiation, this));
	auto menu_item_15 = MenuItemFont::create("Stun_Enemy", CC_CALLBACK_1(StrategyMenu::stunEnemy, this));
	auto menu_item_16 = MenuItemSprite::create(_armguard_, _armguard_, CC_CALLBACK_1(StrategyMenu::armguard, this));
	auto menu_item_17 = MenuItemFont::create("Normal", CC_CALLBACK_1(StrategyMenu::normal, this));
	auto menu_item_18 = MenuItemFont::create("Go_To_The_Goal", CC_CALLBACK_1(StrategyMenu::goToTheGoal, this));
	auto menu_item_19 = MenuItemFont::create("Menu", CC_CALLBACK_1(StrategyMenu::menu, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.05) * 3));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.30) * 3));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.65) * 3));
	menu_item_4->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.75) * 3));
	menu_item_5->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.35) * 3));
	menu_item_6->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.40) * 3));
	menu_item_7->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.45) * 3));
	menu_item_8->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.85) * 3));
	menu_item_9->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.50) * 3));
	menu_item_10->setPosition(Point(visibleSize.width / 2, (visibleSize.height/ 1.95) * 3));
	menu_item_11->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2.30) * 3));
	menu_item_12->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2.60) * 3));
	menu_item_13->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2.90) * 3));
	menu_item_14->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.55) * 3));
	menu_item_15->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2.05) * 3));
	menu_item_16->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 3.40) * 3));
	menu_item_17->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.15) * 3));
	menu_item_18->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.20) * 3));
	menu_item_19->setPosition(Point(origin.x, origin.y + visibleSize.height * 3));
	menu_item_19->setAnchorPoint(Point(0, 1));

	menu_item_1->setColor(Color3B::RED);

	menu_item_1->setFontSizeObj(menu_item_1->getFontSizeObj() / scaleFactor);
	menu_item_3->setFontSizeObj(menu_item_3->getFontSizeObj() / scaleFactor);
	menu_item_4->setFontSizeObj(menu_item_4->getFontSizeObj() / scaleFactor);
	menu_item_8->setFontSizeObj(menu_item_8->getFontSizeObj() / scaleFactor);
	menu_item_10->setFontSizeObj(menu_item_10->getFontSizeObj() / scaleFactor);
	menu_item_15->setFontSizeObj(menu_item_15->getFontSizeObj() / scaleFactor);
	menu_item_17->setFontSizeObj(menu_item_17->getFontSizeObj() / scaleFactor);
	menu_item_18->setFontSizeObj(menu_item_18->getFontSizeObj() / scaleFactor);
	menu_item_19->setFontSizeObj(menu_item_19->getFontSizeObj() / scaleFactor);

	auto label = Label::createWithTTF("Choose Your Strategy", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.60) * 3));
	label->setTextColor(Color4B::ORANGE);
	label->setScale(label->getScale() / scaleFactor);
	// add the label as a child to this layer
	scrollView->addChild(label, 1);

	auto label1 = Label::createWithTTF("Choose Your Weapon", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.25) * 3));
	label1->setTextColor(Color4B::YELLOW);
	label1->setScale(label1->getScale() / scaleFactor);
	// add the label as a child to this layer
	scrollView->addChild(label1, 1);

	auto label2 = Label::createWithTTF("Choose Your Protection", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 2.15) * 3));
	label2->setTextColor(Color4B::GREEN);
	label2->setScale(label2->getScale() / scaleFactor);
	// add the label as a child to this layer
	scrollView->addChild(label2, 1);

	auto label3 = Label::createWithTTF("Choose Your Exploration", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 1.10) * 3));
	label3->setTextColor(Color4B::MAGENTA);
	label3->setScale(label3->getScale() / scaleFactor);
	// add the label as a child to this layer
	scrollView->addChild(label3, 1);

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, menu_item_5, menu_item_6, menu_item_7, menu_item_8, menu_item_9, menu_item_10, menu_item_11, menu_item_12, menu_item_13, menu_item_14, menu_item_15, menu_item_16, menu_item_17, menu_item_18, menu_item_19, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	scrollView->addChild(menu, 1);


	return true;

}

//Method which asks GameManager to push MapManager scene

void StrategyMenu::enjoyTheGame(Ref *pSender)
{
	log("EnterTheGame");
	core->playGame(this->player);
	return;

}

//    ----- Exploration Strategies -----

void StrategyMenu::normal(Ref* pSender) {
	log("Normal");
	this->player->setCrawlingStrategy(NORMAL);
	this->player->setCrawlingStrategy(NORMAL);
	this->player->setCrawlingStrategy(NORMAL);
	crawlingSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 1.15) * 3));
	SoundManager::getInstance()->startNormalExplorationChosenSound();
	return;
}

void StrategyMenu::goToTheGoal(Ref* pSender) {
	log("Go_To_The_Goal");
	this->player->setCrawlingStrategy(GO_TO_GOAL);
	this->player->setCrawlingStrategy(GO_TO_GOAL);
	this->player->setCrawlingStrategy(GO_TO_GOAL);
	crawlingSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 1.20) * 3));
	SoundManager::getInstance()->startGoToTheGoalExplorationChosenSound();
	return;
}

//    ----- Weapons ----- 

void StrategyMenu::gun(Ref *pSender)
{
	log("Gun");
	this->player->setActualWeapon(GUN);
	this->player->setActualWeapon(GUN);
	this->player->setActualWeapon(GUN);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 1.30) * 3));
	SoundManager::getInstance()->startGunChosenSound();
	return;
}

void StrategyMenu::rifle(Ref *pSender)
{
	log("Rifle");
	player->setActualWeapon(RIFLE);
	player->setActualWeapon(RIFLE);
	player->setActualWeapon(RIFLE);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 1.35) * 3));
	SoundManager::getInstance()->startRifleChosenSound();
	return;
}

void StrategyMenu::sniper(Ref *pSender)
{
	log("Sniper");
	player->setActualWeapon(SNIPER);
	player->setActualWeapon(SNIPER);
	player->setActualWeapon(SNIPER);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 1.40) * 3));
	SoundManager::getInstance()->startSniperChosenSound();
	return;
}

void StrategyMenu::grenade(Ref *pSender)
{
	log("Grenade");
	player->setActualWeapon(GRENADE);
	player->setActualWeapon(GRENADE);
	player->setActualWeapon(GRENADE);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 1.45) * 3));
	SoundManager::getInstance()->startGrenadeChosenSound();
	return;
}

void StrategyMenu::knife(Ref *pSender)
{
	log("Knife");
	player->setActualWeapon(KNIFE);
	player->setActualWeapon(KNIFE);
	player->setActualWeapon(KNIFE);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width/ 8, (visibleSize.height / 1.50) * 3));
	SoundManager::getInstance()->startKnifeChosenSound();
	return;
}

void StrategyMenu::radiation(Ref *pSender)
{
	log("Radiation");
	player->setActualWeapon(RADIATION);
	player->setActualWeapon(RADIATION);
	player->setActualWeapon(RADIATION);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 1.55) * 3));
	SoundManager::getInstance()->startRadiationChosenSound();
	return;
}

//    ----- Fight Strategies -----

void StrategyMenu::defeatEnemy(Ref *pSender)
{
	log("Defeat_Enemy");
	player->setStrategy(DEFEAT_ENEMY);
	player->setStrategy(DEFEAT_ENEMY);
	player->setStrategy(DEFEAT_ENEMY);
	strategySelected->setPosition(Point(visibleSize.width /2 + visibleSize.width / 4, (visibleSize.height / 1.65) * 3));
	SoundManager::getInstance()->startDefeatEnemyChosenSound();
	return;
}

void StrategyMenu::distanceAttack(Ref *pSender)
{
	log("Distance_Attack");
	player->setStrategy(DISTANCE_ATTACK);
	player->setStrategy(DISTANCE_ATTACK);
	player->setStrategy(DISTANCE_ATTACK);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 1.75) * 3));
	SoundManager::getInstance()->startDistanceAttackChosenSound();
	return;
}

void StrategyMenu::retreat(Ref *pSender)
{
	log("Retreat");
	player->setStrategy(RETREAT);
	player->setStrategy(RETREAT);
	player->setStrategy(RETREAT);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 1.85) * 3));
	SoundManager::getInstance()->startRetreatChosenSound();
	return;
}

void StrategyMenu::bePatient(Ref *pSender)
{
	log("Be_Patient");
	player->setStrategy(BE_PATIENT);
	player->setStrategy(BE_PATIENT);
	player->setStrategy(BE_PATIENT);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 1.95) * 3));
	SoundManager::getInstance()->startBePatientChosenSound();
	return;
}

void StrategyMenu::stunEnemy(Ref *pSender)
{
	log("Stun_Enemy");
	player->setStrategy(STUN_ENEMY);
	player->setStrategy(STUN_ENEMY);
	player->setStrategy(STUN_ENEMY);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 2.05) * 3));
	SoundManager::getInstance()->startStunEnemyChosenSound();
	return;
}

//    ----- Protections -----

void StrategyMenu::shield(Ref *pSender)
{
	log("SHIELD");
	player->setActualProtection(SHIELD);
	player->setActualProtection(SHIELD);
	player->setActualProtection(SHIELD);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 2.30) * 3));
	SoundManager::getInstance()->startShieldChosenSound();
	return;
}

void StrategyMenu::armor(Ref *pSender)
{
	log("ARMOR");
	player->setActualProtection(ARMOR);
	player->setActualProtection(ARMOR);
	player->setActualProtection(ARMOR);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 2.60) * 3));
	SoundManager::getInstance()->startArmorChosenSound();
	return;
}

void StrategyMenu::mask(Ref *pSender)
{
	log("MASK");
	player->setActualProtection(MASK);
	player->setActualProtection(MASK);
	player->setActualProtection(MASK);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 2.90) * 3));
	SoundManager::getInstance()->startMaskChosenSound();
	return;
}

void StrategyMenu::armguard(Ref *pSender)
{
	log("Armguard");
	player->setActualProtection(ARMGUARD);
	player->setActualProtection(ARMGUARD);
	player->setActualProtection(ARMGUARD);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 3.40) * 3));
	SoundManager::getInstance()->startArmguardChosenSound();
	return;
}

//Method which ends the game

void StrategyMenu::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	core->endGame();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}

//Return to the Menu

void StrategyMenu::menu(Ref *pSender)
{
	log("Back");
	Director::getInstance()->popScene();
}

//Getter & Setter

void StrategyMenu::setMapManager(MapManager* manager) {
	this->manager = manager;
}

Player* StrategyMenu::getPlayer() {
	return this->player;
}