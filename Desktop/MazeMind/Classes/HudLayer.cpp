#include "HudLayer.h"
#include "ui/CocosGUI.h"
#include "MapManager.h"
#include "GameManager.h"

USING_NS_CC;

//Constructor

HudLayer::HudLayer(){
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	button = ui::Button::create("initNormal.png", "initSelected.png");
	button->setTitleText("Reload");
	button->setTitleFontSize(16.0f);
	button->setTitleFontSize(button->getTitleFontSize() / scaleFactor);
	button->setTitleColor(Color3B::BLACK);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("Button pressed");
			break;
		case ui::Widget::TouchEventType::ENDED:
			GameManager::getInstance()->restartGame();
			break;
		default:
			break;
		}
	});

	button->setPosition(Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height));
	button->setAnchorPoint(Vec2(1, 1));
	this->addChild(button, 1);

	closeButton = ui::Button::create("closeNormal.png", "closeSelected.png");
	closeButton->setTitleFontSize(17.0f);
	closeButton->setTitleColor(Color3B::BLACK);
	closeButton->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("Button pressed");
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->end();
			break;
		default:
			break;
		}
	});

	closeButton->setPosition(Vec2(origin.x + visibleSize.width, origin.y));
	closeButton->setAnchorPoint(Point(1, 0));
	this->addChild(closeButton, 1);

	score = Label::createWithTTF("SCORE: ", "fonts/Marker Felt.ttf", 32);

	// position the label on the center of the screen
	score->setPosition(Point(origin.x, origin.y + visibleSize.height));
	score->setAnchorPoint(Point(0, 1));
	score->setTextColor(Color4B::BLUE);
	score->setScale(score->getScale() / scaleFactor);
	// add the label as a child to this layer
	this->addChild(score, 1);

	this->scorePoints = 0;

	__String *tempScore = __String::createWithFormat("%d", scorePoints);
	points = Label::createWithTTF(tempScore->getCString(), "fonts/Marker Felt.ttf", 32);
	points->setPosition(Point(origin.x + (score->getContentSize().width / scaleFactor), origin.y + visibleSize.height));
	points->setAnchorPoint(Point(0, 1));
	points->setTextColor(Color4B::BLUE);
	points->setScale(points->getScale() / scaleFactor);
	this->addChild(points, 1);
	this->scheduleUpdate();
}

//Destructor

HudLayer::~HudLayer() {

}

//Method which schedules the Layer every frame

void HudLayer::update(float dt) {

	__String *tempScore = __String::createWithFormat("%d", scorePoints);
	points->setString(tempScore->getCString());
}


//Getter & Setter

void HudLayer::setScore(int scorePoints) {
	this->scorePoints = scorePoints;
}

int HudLayer::getScore() {
	return this->scorePoints;
}
