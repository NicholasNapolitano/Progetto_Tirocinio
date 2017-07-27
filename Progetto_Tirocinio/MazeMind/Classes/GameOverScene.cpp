#include "GameOverScene.h"
#include "StartMenu.h"

USING_NS_CC;

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

GameOverScene::GameOverScene() {

}

GameOverScene::~GameOverScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}


bool GameOverLayer::init()
{
	if (LayerColor::initWithColor(Color4B::WHITE))
	{
		Size winSize = Director::getInstance()->getWinSize();
		this->_label = LabelTTF::create("", "Artial", 32);
		_label->retain();
		_label->setColor(Color3B::BLACK);
		_label->setPosition(Point(winSize.width / 2, winSize.height / 2));
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

void GameOverLayer::gameOverDone()
{
	Director::getInstance()->replaceScene(StartMenu::createScene());
}

GameOverLayer::GameOverLayer() {

}

GameOverLayer::~GameOverLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}