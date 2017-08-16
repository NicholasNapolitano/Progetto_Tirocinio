#include "StrategyMenu.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "Enums.h"
#include "ui/CocosGUI.h"
#include "Player.h"

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

	this->core = GameManager::getInstance();
	visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	scrollView = ui::ScrollView::create();
	scrollView->setClippingEnabled(true);
	scrollView->setTouchEnabled(true);
	scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->getInnerContainer()->setLayoutType(ui::Layout::Type::VERTICAL);
	scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height * 2));
	scrollView->setPosition(Vec2(0, 0));
	scrollView->retain();
	this->addChild(scrollView);


	this->player = Player::create("Player.png");
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
	scrollView->addChild(strategySelected);
	weaponSelected = Sprite::create("Selected.png");
	scrollView->addChild(weaponSelected);
	protectionSelected = Sprite::create("Selected.png");
	scrollView->addChild(protectionSelected);

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


	auto menu_item_1 = MenuItemFont::create("--> EnterTheGame <-- ", CC_CALLBACK_1(StrategyMenu::enterTheGame, this));
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

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 9.5));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 8.05));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 7.7));
	menu_item_4->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 6.2));
	menu_item_5->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 7.75));
	menu_item_6->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 7.45));
	menu_item_7->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 7.15));
	menu_item_8->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 6.80));
	menu_item_9->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 6.75));
	menu_item_10->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 6.35));
	menu_item_11->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 3.50));
	menu_item_12->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 2.50));
	menu_item_13->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 1.50));
	menu_item_14->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 6.40));
	menu_item_15->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 5.90));
	menu_item_16->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 0.50));

	menu_item_1->setColor(Color3B::RED);


	auto label = Label::createWithTTF("Choose Your Strategy", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 7.0));
	label->setTextColor(Color4B::BLUE);
	// add the label as a child to this layer
	scrollView->addChild(label, 1);

	auto label1 = Label::createWithTTF("Choose Your Weapon", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 8.32));
	label1->setTextColor(Color4B::YELLOW);
	// add the label as a child to this layer
	scrollView->addChild(label1, 1);

	auto label2 = Label::createWithTTF("Choose Your Protection", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 4.32));
	label2->setTextColor(Color4B::GREEN);
	// add the label as a child to this layer
	scrollView->addChild(label2, 1);

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, menu_item_5, menu_item_6, menu_item_7, menu_item_8, menu_item_9, menu_item_10, menu_item_11, menu_item_12, menu_item_13, menu_item_14, menu_item_15, menu_item_16, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	scrollView->addChild(menu);


	return true;

}

void StrategyMenu::enterTheGame(Ref *pSender)
{
	log("EnterTheGame");
	core->playGame(this->player);
	return;

}

void StrategyMenu::gun(Ref *pSender)
{
	log("Gun");
	this->player->setActualWeapon(GUN);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 5) * 8.05));
	return;
}

void StrategyMenu::rifle(Ref *pSender)
{
	log("Rifle");
	player->setActualWeapon(RIFLE);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 5) * 7.75));
	return;
}

void StrategyMenu::sniper(Ref *pSender)
{
	log("Sniper");
	player->setActualWeapon(SNIPER);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 5) * 7.45));
	return;
}

void StrategyMenu::grenade(Ref *pSender)
{
	log("Grenade");
	player->setActualWeapon(GRENADE);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 5) * 7.15));
	return;
}

void StrategyMenu::knife(Ref *pSender)
{
	log("Knife");
	player->setActualWeapon(KNIFE);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width/ 8, (visibleSize.height / 5) * 6.75));
	return;
}

void StrategyMenu::radiation(Ref *pSender)
{
	log("Radiation");
	player->setActualWeapon(RADIATION);
	weaponSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 8, (visibleSize.height / 5) * 6.40));
	return;
}

void StrategyMenu::defeatEnemy(Ref *pSender)
{
	log("Defeat_Enemy");
	player->setStrategy(DEFEAT_ENEMY);
	strategySelected->setPosition(Point(visibleSize.width /2 + visibleSize.width / 4, (visibleSize.height / 7) * 7.7));
	return;
}

void StrategyMenu::distanceAttack(Ref *pSender)
{
	log("Distance_Attack");
	player->setStrategy(DISTANCE_ATTACK);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 6) * 6.2));
	return;
}

void StrategyMenu::retreat(Ref *pSender)
{
	log("Retreat");
	player->setStrategy(RETREAT);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 7) * 6.80));
	return;
}

void StrategyMenu::bePatient(Ref *pSender)
{
	log("Be_Patient");
	player->setStrategy(BE_PATIENT);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 7) * 6.35));
	return;
}

void StrategyMenu::stunEnemy(Ref *pSender)
{
	log("Stun_Enemy");
	player->setStrategy(STUN_ENEMY);
	strategySelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 4, (visibleSize.height / 7) * 5.90));
	return;
}

void StrategyMenu::shield(Ref *pSender)
{
	log("SHIELD");
	player->setActualProtection(SHIELD);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 7) * 3.50));
	return;
}

void StrategyMenu::armor(Ref *pSender)
{
	log("ARMOR");
	player->setActualProtection(ARMOR);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 7) * 2.50));
	return;
}

void StrategyMenu::mask(Ref *pSender)
{
	log("MASK");
	player->setActualProtection(MASK);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 7) * 1.50));
	return;
}

void StrategyMenu::armguard(Ref *pSender)
{
	log("Armguard");
	player->setActualProtection(ARMGUARD);
	protectionSelected->setPosition(Point(visibleSize.width / 2 + visibleSize.width / 13, (visibleSize.height / 7) * 0.50));
	return;
}

Player* StrategyMenu::getPlayer() {
	return this->player;
}

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


void StrategyMenu::setMapManager(MapManager* manager) {
	this->manager = manager;
}