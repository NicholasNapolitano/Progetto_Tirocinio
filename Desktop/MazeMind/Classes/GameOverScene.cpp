#include "GameOverScene.h"
#include "GameManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
	if (Scene::init())
	{
		this->_layer = GameOverLayer::create();
		this->_layer->retain();
		this->addChild(_layer);

		return true;
	}
	else
	{
		return false;
	}
}

//Constructor

GameOverScene::GameOverScene() {

}

//Destructor

GameOverScene::~GameOverScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

// on "init" you need to initialize your instance
bool GameOverLayer::init()
{
	if (LayerColor::initWithColor(Color4B::WHITE))
	{
		float scaleFactor = Director::getInstance()->getContentScaleFactor();
		Size winSize = Director::getInstance()->getWinSize();
		this->_label = LabelTTF::create("", "Artial", 32);
		_label->retain();
		_label->setColor(Color3B::BLACK);
		_label->setPosition(Point(winSize.width / 2, winSize.height / 2));
		_label->setScale(_label->getScale() / scaleFactor);
		this->addChild(_label);

		this->runAction(Sequence::create(
			DelayTime::create(5),
			CallFunc::create(this,
				callfunc_selector(GameOverLayer::gameOverDone)),
			NULL));

		return true;
	}
	else
	{
		return false;
	}
}

//Invoke the GameManager's method to return to the Menu

void GameOverLayer::gameOverDone()
{
	GameManager::getInstance()->restartGame();
}

//Constructor

GameOverLayer::GameOverLayer() {

}

//Destructor

GameOverLayer::~GameOverLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}