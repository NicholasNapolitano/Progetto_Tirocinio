#include "StartMenu.h"
#include "MapManager.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"

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
	this->deltaTime = 0;
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	this->core = GameManager::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
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

	auto menu_item_1 = MenuItemFont::create("Play", CC_CALLBACK_1(StartMenu::play, this));
	auto menu_item_2 = MenuItemFont::create("Highscore", CC_CALLBACK_1(StartMenu::highscore, this));
	auto menu_item_3 = MenuItemFont::create("Settings", CC_CALLBACK_1(StartMenu::settings, this));


	menu_item_1->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5));
	menu_item_1->setColor(Color3B::ORANGE);
	menu_item_1->setFontSizeObj(menu_item_1->getFontSizeObj() / scaleFactor);
	menu_item_2->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.9));
	menu_item_2->setColor(Color3B::YELLOW);
	menu_item_2->setFontSizeObj(menu_item_2->getFontSizeObj() / scaleFactor);
	menu_item_3->setPosition(Point(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2.5));
	menu_item_3->setColor(Color3B::GREEN);
	menu_item_3->setFontSizeObj(menu_item_3->getFontSizeObj() / scaleFactor);
	auto label0 = Label::createWithTTF("MAZE MIND", "fonts/Marker Felt.ttf", 40);

	// position the label on the center of the screen
	label0->setScale(label0->getScale() / scaleFactor);
	label0->setPosition(Point(origin.x + visibleSize.width / 2, visibleSize.height - label0->getContentSize().height * 1.5));
	label0->setTextColor(Color4B::RED);
	// add the label as a child to this layer
	this->addChild(label0, 1);

	auto menu = Menu::create(menu_item_1, menu_item_2, menu_item_3, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, 1);

	this->scheduleUpdate();

	return true;

}

//Method to schedule StartMenu every frame

void StartMenu::update(float dt) {

	deltaTime += dt;
	if (deltaTime >= 70.0f) {
		core->startPresentation();
	}
    
	return;
}


//Method which asks GameManager to push StrategyMenu scene

void StartMenu::play(Ref *pSender)
{
	log("Play");
	core->selectStrategy();
}

//Method which asks GameManager to push HighScoreScene scene

void StartMenu::highscore(Ref *pSender)
{
	log("Highscores");
	core->viewHighScore();
}

//Method which asks GameManager to push SettingsScene scene

void StartMenu::settings(Ref *pSender)
{
	log("Settings");
	core->changeSettings();
}

//Method which ends the game

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
