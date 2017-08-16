#include "StartMenu.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* StartMenu::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = StartMenu::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool StartMenu::init()
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

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(StartMenu::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(StartMenu::Play, this));
	auto menu_item_2 = MenuItemFont::create("Highscores", CC_CALLBACK_1(StartMenu::Highscores, this));
	auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(StartMenu::Settings, this));


	menu_item_1->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 3.6));
	menu_item_2->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 2.6));
	menu_item_3->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 1.6));

	auto label0 = Label::createWithTTF("MAZE MIND", "fonts/Marker Felt.ttf", 32);

	// position the label on the center of the screen
	label0->setPosition(Point(visibleSize.width / 2, (visibleSize.height / 5) * 4.6));
	label0->setTextColor(Color4B::RED);
	// add the label as a child to this layer
	this->addChild(label0, 1);

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu);


	return true;

}

void StartMenu::Play(Ref *pSender)
{
	log("Play");
	core->selectStrategy();
}

void StartMenu::Highscores(Ref *pSender)
{
	log("Highscores");
	log("Sorry, not implemented yet!");
	/*auto scene = MapManager::createScene();
	Director::getInstance()->replaceScene(TransitionPageTurn::create(2, scene, false));*/
}

void StartMenu::Settings(Ref *pSender)
{
	log("Settings");
	log("Sorry, not implemented yet!");
}

void StartMenu::menuCloseCallback(Ref* pSender)
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
