#include "HudLayer.h"
#include "ui/CocosGUI.h"
#include "MapManager.h"
#include "GameManager.h"

USING_NS_CC;

HudLayer::HudLayer(){

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	button = ui::Button::create("initNormal.png", "initSelected.png");
	button->setTitleText("Reload");
	button->setTitleFontSize(16.0f);
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
	// add the label as a child to this layer
	this->addChild(score, 1);
}

HudLayer::~HudLayer() {

}
