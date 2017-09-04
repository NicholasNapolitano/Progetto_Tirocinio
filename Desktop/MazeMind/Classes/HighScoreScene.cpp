#include "HighScoreScene.h"
#include "GameManager.h"

USING_NS_CC;

//Global variable used as a entrance parameter to create the scene

unsigned int score;

Scene* HighScoreScene::createScene(unsigned int tempScore)
{   
	score = tempScore;

	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HighScoreScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HighScoreScene::init()
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
		CC_CALLBACK_1(HighScoreScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto menu_item_1 = MenuItemFont::create("Menu", CC_CALLBACK_1(HighScoreScene::back, this));


	menu_item_1->setPosition(Point(origin.x + menu_item_1->getContentSize().width, origin.y + visibleSize.height - menu_item_1->getContentSize().height));

	auto menu = Menu::create(menu_item_1, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, 1);
    
	//Object used to save Game states

	UserDefault *def = UserDefault::getInstance();

	auto highScore = def->getIntegerForKey("HIGHSCORE");

	if (score > highScore) {
		
		highScore = score;

		def->setIntegerForKey("HIGHSCORE", highScore);
	}

	def->flush();


	String* tempHighScore = __String::createWithFormat("%d", highScore);
	auto highScoreLabel = LabelTTF::create(tempHighScore->getCString(), "fonts/Marker Felt.ttf", 32);
	highScoreLabel->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	highScoreLabel->setColor(Color3B::YELLOW);
	this->addChild(highScoreLabel);

	return true;

}

//Return to the Menu

void HighScoreScene::back(Ref *pSender)
{
	log("Back");
	Director::getInstance()->popScene();
}

//End the game

void HighScoreScene::menuCloseCallback(Ref* pSender)
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