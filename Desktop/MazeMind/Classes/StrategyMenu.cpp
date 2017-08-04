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
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto scrollView = ui::ScrollView::create();
	scrollView->setClippingEnabled(true);
	scrollView->setTouchEnabled(true);
	scrollView->setContentSize(Size(visibleSize.width, visibleSize.height));
	scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollView->getInnerContainer()->setLayoutType(ui::Layout::Type::VERTICAL);
	scrollView->setInnerContainerSize(Size(visibleSize.width, visibleSize.height * 2));
	scrollView->setPosition(Vec2(0, 0));
	scrollView->retain();
	this->addChild(scrollView);


	player = Player::create("Player.png");
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


	auto menu_item_1 = MenuItemFont::create("--> EnterTheGame <-- ", CC_CALLBACK_1(StrategyMenu::enterTheGame, this));
	auto menu_item_2 = MenuItemFont::create("Gun", CC_CALLBACK_1(StrategyMenu::gun, this));
	auto menu_item_3 = MenuItemFont::create("Defeat_Enemy", CC_CALLBACK_1(StrategyMenu::defeatEnemy, this));
	auto menu_item_4 = MenuItemFont::create("Distance_Attack", CC_CALLBACK_1(StrategyMenu::distanceAttack, this));
	auto menu_item_5 = MenuItemFont::create("Rifle", CC_CALLBACK_1(StrategyMenu::rifle, this));
	auto menu_item_6 = MenuItemFont::create("Sniper", CC_CALLBACK_1(StrategyMenu::sniper, this));
	auto menu_item_7 = MenuItemFont::create("Granade", CC_CALLBACK_1(StrategyMenu::granade, this));
	auto menu_item_8 = MenuItemFont::create("Retreat", CC_CALLBACK_1(StrategyMenu::retreat, this));
	auto menu_item_9 = MenuItemFont::create("Knife", CC_CALLBACK_1(StrategyMenu::knife, this));

	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4.7));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4.05));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 3));
	menu_item_4->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 2.0));
	menu_item_5->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3.75));
	menu_item_6->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3.45));
	menu_item_7->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3.15));
	menu_item_8->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 7) * 1.80));
	menu_item_9->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2.85));



	auto label = Label::createWithTTF("Choose Your Strategy", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 6) * 3.0));

	// add the label as a child to this layer
	scrollView->addChild(label, 1);

	auto label1 = Label::createWithTTF("Choose Your Weapon", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4.32));

	// add the label as a child to this layer
	scrollView->addChild(label1, 1);

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, menu_item_4, menu_item_5, menu_item_6, menu_item_7, menu_item_8, menu_item_9, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	scrollView->addChild(menu);


	return true;

}

void StrategyMenu::enterTheGame(Ref *pSender)
{
	log("EnterTheGame");
	core->playGame(player);
	return;

}

void StrategyMenu::gun(Ref *pSender)
{
	log("Gun");
	player->setActualWeapon(GUN);
    /*LabelTTF* label = LabelTTF::create("Weapon Chosen", "Artial", 32);
    label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::rifle(Ref *pSender)
{
	log("Rifle");
	player->setActualWeapon(RIFLE);
	/*LabelTTF* label = LabelTTF::create("Weapon Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::sniper(Ref *pSender)
{
	log("Sniper");
	player->setActualWeapon(SNIPER);
	/*LabelTTF* label = LabelTTF::create("Weapon Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::granade(Ref *pSender)
{
	log("Granade");
	player->setActualWeapon(GRANADE);
	/*LabelTTF* label = LabelTTF::create("Weapon Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::knife(Ref *pSender)
{
	log("Knife");
	player->setActualWeapon(KNIFE);
	/*LabelTTF* label = LabelTTF::create("Weapon Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::defeatEnemy(Ref *pSender)
{
	log("Defeat_Enemy");
	player->setStrategy(DEFEAT_ENEMY);
	/*LabelTTF* label = LabelTTF::create("Strategy Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::distanceAttack(Ref *pSender)
{
	log("Distance_Attack");
	player->setStrategy(DISTANCE_ATTACK);
	/*LabelTTF* label = LabelTTF::create("Strategy Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
	return;
}

void StrategyMenu::retreat(Ref *pSender)
{
	log("Retreat");
	player->setStrategy(RETREAT);
	/*LabelTTF* label = LabelTTF::create("Strategy Chosen", "Artial", 32);
	label->retain();
	label->setColor(Color3B::WHITE);
	label->setPosition(Point(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
	this->addChild(label, 2);
	label->runAction(DelayTime::create(2.0f));
	this->removeChild(label);*/
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