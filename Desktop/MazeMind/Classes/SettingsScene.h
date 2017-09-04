#ifndef __SETTINGS_SENE_H__
#define __SETTINGS_SENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameManager;

class SettingsScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void back(Ref *pSender);
	void sliderEvent1(Ref *pSender, cocos2d::ui::Slider::EventType type);
	void sliderEvent2(Ref *pSender, cocos2d::ui::Slider::EventType type);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	GameManager* core;
	cocos2d::Label* musicVolume;
	cocos2d::Label* effectsVolume;
	float music;
	float effects;
	cocos2d::UserDefault* def;
	cocos2d::Sprite* background;

	// implement the "static create()" method manually
	CREATE_FUNC(SettingsScene);
};

#endif // __SETTINGS_SENE_H__