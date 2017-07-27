#include "HudLayer.h"
#include "ui/CocosGUI.h"
#include "MapManager.h"

USING_NS_CC;

HudLayer::HudLayer(){

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	button = ui::Button::create("initNormal.png", "initSelected.png");
	button->setTitleText("Reload");
	button->setTitleFontSize(17.0f);
	button->setTitleColor(Color3B::BLACK);
	button->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type) {
		switch (type)
		{
		case ui::Widget::TouchEventType::BEGAN:
			log("Button pressed");
			break;
		case ui::Widget::TouchEventType::ENDED:
			Director::getInstance()->replaceScene(MapManager::createScene());
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
}

HudLayer::~HudLayer() {

}
