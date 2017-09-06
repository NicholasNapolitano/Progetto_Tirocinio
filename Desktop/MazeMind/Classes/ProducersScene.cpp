#include "ProducersScene.h"
#include "GameManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool ProducersScene::init()
{
	if (Scene::init())
	{
		this->_layer = ProducersLayer::create();
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

ProducersScene::ProducersScene() {

}

//Destructor

ProducersScene::~ProducersScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

// on "init" you need to initialize your instance

bool ProducersLayer::init()
{
	if (LayerColor::initWithColor(Color4B::WHITE))
	{
		Size winSize = Director::getInstance()->getWinSize();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		this->_label = LabelTTF::create("", "Artial", 32);
		_label->retain();
		_label->setColor(Color3B::BLACK);
		_label->setPosition(Point(winSize.width / 2, winSize.height / 2));
		this->addChild(_label);
		

		this->runAction(Sequence::create(
			DelayTime::create(0.1f),
			CallFunc::create(this,
				callfunc_selector(ProducersLayer::entrance)),
			DelayTime::create(3.0f),
			CallFunc::create(this,
				callfunc_selector(ProducersLayer::exit)),
			DelayTime::create(1.5f),
			CallFunc::create(this,
				callfunc_selector(ProducersLayer::ProducersDone)),
			NULL));

		return true;
	}
	else
	{
		return false;
	}
}

//Method that makes logos appear

void ProducersLayer::entrance() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	producer = Sprite::create("Barbocchiale.png");
	agency = Sprite::create("H2App.png");
	engine = Sprite::create("Cocos2DX.png");
	producer->setPosition(Vec2(origin.x + visibleSize.width / 3.2, origin.y + visibleSize.height / 3));
	this->addChild(producer, 5);
	agency->setPosition(Vec2(origin.x + visibleSize.width / 1.5, origin.y + visibleSize.height / 3));
	this->addChild(agency, 5);
	engine->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 1.5));
	this->addChild(engine, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes logos disappear

void ProducersLayer::exit() {
	
	producer->runAction(FadeOut::create(1.5f));
	agency->runAction(FadeOut::create(1.5f));
	engine->runAction(FadeOut::create(1.5f));
}

//Method which asks GameManager to push the StartMenu scene

void ProducersLayer::ProducersDone()
{
	GameManager::getInstance()->startPresentation();
}

//Constructor

ProducersLayer::ProducersLayer() {

}

//Destructor

ProducersLayer::~ProducersLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}