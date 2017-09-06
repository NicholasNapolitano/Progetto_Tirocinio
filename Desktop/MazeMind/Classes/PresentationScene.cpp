#include "PresentationScene.h"
#include "GameManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool PresentationScene::init()
{
	if (Scene::init())
	{
		this->_layer = PresentationLayer::create();
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

PresentationScene::PresentationScene() {
}

//Destructor

PresentationScene::~PresentationScene()
{
	if (_layer)
	{
		_layer->release();
		_layer = NULL;
	}
}

//Enable the tap 
//Push the StartMenu scene

bool PresentationLayer::onTouchBegan(Touch *touch, Event *event)
{
	GameManager::getInstance()->startGame();
	return true;
}

// on "init" you need to initialize your instance

bool PresentationLayer::init()
{
	if (LayerColor::initWithColor(Color4B::BLACK))
	{
		Size winSize = Director::getInstance()->getWinSize();
		Size visibleSize = Director::getInstance()->getVisibleSize();
		Vec2 origin = Director::getInstance()->getVisibleOrigin();
		this->_label = LabelTTF::create("", "Artial", 32);
		_label->retain();
		_label->setColor(Color3B::BLACK);
		_label->setPosition(Point(winSize.width / 2, winSize.height / 2));
		this->addChild(_label);

		// Register Touch Event
		auto dispatcher = Director::getInstance()->getEventDispatcher();
		auto listener = EventListenerTouchOneByOne::create();

		listener->onTouchBegan = CC_CALLBACK_2(PresentationLayer::onTouchBegan, this);

		dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

		this->runAction(Sequence::create(
			DelayTime::create(0.1f),
			CallFunc::create(this,
				callfunc_selector(PresentationLayer::startPart1)),
			DelayTime::create(10.0f),
			CallFunc::create(this,
				callfunc_selector(PresentationLayer::startPart2)),
			DelayTime::create(10.0f),
			CallFunc::create(this,
				callfunc_selector(PresentationLayer::startPart3)),
			DelayTime::create(10.0f),
			CallFunc::create(this,
				callfunc_selector(PresentationLayer::finish)),
			DelayTime::create(1.5f),
			CallFunc::create(this,
				callfunc_selector(PresentationLayer::PresentationDone)),
			NULL));

		return true;
	}
	else
	{
		return false;
	}
}

//Method that makes Part1 appear

void PresentationLayer::startPart1() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	part1 = Sprite::create("Part1.png");
	part1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(part1, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes Part2 appear

void PresentationLayer::startPart2() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->runAction(FadeOut::create(1.0f));
	this->removeChild(part1);
	part2 = Sprite::create("Part2.png");
	part2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(part2, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes Part3 appear

void PresentationLayer::startPart3() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->runAction(FadeOut::create(1.0f));
	this->removeChild(part2);
	part3 = Sprite::create("Part3.png");
	part3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(part3, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes Part3 disappear

void PresentationLayer::finish() {

	part3->runAction(FadeOut::create(1.5f));
}

//Method which asks GameManager to push the StartMenu scene

void PresentationLayer::PresentationDone()
{
	GameManager::getInstance()->startGame();
}

//Constructor

PresentationLayer::PresentationLayer() {
}

//Destructor

PresentationLayer::~PresentationLayer()
{
	if (_label)
	{
		_label->release();
		_label = NULL;
	}
}