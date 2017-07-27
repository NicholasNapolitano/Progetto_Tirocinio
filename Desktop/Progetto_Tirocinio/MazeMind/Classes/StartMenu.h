#ifndef __START_MENU_H__
#define __START_MENU_H__

#include "cocos2d.h"

class GameManager;

class StartMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void Play(Ref *pSender);
	void Highscores(Ref *pSender);
	void Settings(Ref *pSender);

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	GameManager* core;

	// implement the "static create()" method manually
	CREATE_FUNC(StartMenu);
};

#endif // __MENU_SCENE_H__