#ifndef __HIGHSCORE_SCENE_H__
#define __HIGHSCORE_SCENE_H__

#include "cocos2d.h"

class GameManager;

class HighScoreScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene(unsigned int tempScore);

	virtual bool init();
	void back(Ref *pSender);
	
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	GameManager* core;
	cocos2d::Sprite* background;

	// implement the "static create()" method manually
	CREATE_FUNC(HighScoreScene);
};

#endif // __HIGHSCORE_SCENE_H__