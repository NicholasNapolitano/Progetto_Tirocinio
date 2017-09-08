#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "cocos2d.h"

class GameManager;

class StartMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void play(Ref *pSender);
	void highscore(Ref *pSender);
	void settings(Ref *pSender);
	void update(float dt) override;

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	GameManager* core;
	cocos2d::Sprite* background;
	float deltaTime;

	// implement the "static create()" method manually
	CREATE_FUNC(StartMenu);
};

#endif // __START_MENU_H__