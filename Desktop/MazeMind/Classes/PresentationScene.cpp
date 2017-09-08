#include "PresentationScene.h"
#include "GameManager.h"
#include "SoundManager.h"

USING_NS_CC;

// on "init" you need to initialize your instance
bool PresentationScene::init()
{
	if (Scene::init())
	{
		SoundManager::getInstance()->startPresentationMusic();
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
			DelayTime::create(15.0f),
			CallFunc::create(this,
				callfunc_selector(PresentationLayer::startPart3)),
			DelayTime::create(12.0f),
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

	// Original image
	auto backOrig = Sprite::create("BackPart1.png");
	auto oWidth = backOrig->getContentSize().width;
	auto oHeight = backOrig->getContentSize().height;
	backOrig->setFlippedY(true);
	backOrig->setScale(visibleSize.width / oWidth, visibleSize.height / oHeight); // backOrig scaled to screen size
	backOrig->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// Create new texture with background in the exact size of the screen
	auto renderTexture = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
	renderTexture->begin();
	backOrig->visit();
	renderTexture->end();

	// Create new Sprite without scale, which perfoms much better
	background = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background);

	part1 = Sprite::create("Part1.png");
	part1->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(part1, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes Part2 appear

void PresentationLayer::startPart2() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->removeChild(background);
	this->removeChild(part1);

	// Original image
	auto backOrig1 = Sprite::create("BackPart2.png");
	auto oWidth1 = backOrig1->getContentSize().width;
	auto oHeight1 = backOrig1->getContentSize().height;
	backOrig1->setFlippedY(true);
	backOrig1->setScale(visibleSize.width / oWidth1, visibleSize.height / oHeight1); // backOrig scaled to screen size
	backOrig1->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// Create new texture with background in the exact size of the screen
	auto renderTexture1 = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
	renderTexture1->begin();
	backOrig1->visit();
	renderTexture1->end();

	// Create new Sprite without scale, which perfoms much better
	background = Sprite::createWithTexture(renderTexture1->getSprite()->getTexture());
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background);

	part2 = Sprite::create("Part2.png");
	part2->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(part2, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes Part3 appear

void PresentationLayer::startPart3() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	this->removeChild(background);
	this->removeChild(part2);

	// Original image
	auto backOrig2 = Sprite::create("BackPart3.png");
	auto oWidth2 = backOrig2->getContentSize().width;
	auto oHeight2 = backOrig2->getContentSize().height;
	backOrig2->setFlippedY(true);
	backOrig2->setScale(visibleSize.width / oWidth2, visibleSize.height / oHeight2); // backOrig scaled to screen size
	backOrig2->setPosition(visibleSize.width / 2, visibleSize.height / 2);

	// Create new texture with background in the exact size of the screen
	auto renderTexture2 = RenderTexture::create(visibleSize.width, visibleSize.height, Texture2D::PixelFormat::RGBA8888);
	renderTexture2->begin();
	backOrig2->visit();
	renderTexture2->end();

	// Create new Sprite without scale, which perfoms much better
	background = Sprite::createWithTexture(renderTexture2->getSprite()->getTexture());
	background->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(background);

	part3 = Sprite::create("Part3.png");
	part3->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));
	this->addChild(part3, 5);
	this->runAction(FadeIn::create(1.0f));
}

//Method that makes Part3 disappear

void PresentationLayer::finish() {

	background->runAction(FadeOut::create(1.5f));
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