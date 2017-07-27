#ifndef GAME_OVER_SCENE_H_
#define GAME_OVER_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class GameOverLayer : public cocos2d::LayerColor
{
public:
	GameOverLayer();
	virtual ~GameOverLayer();
	bool init();
	CREATE_FUNC(GameOverLayer);

	void gameOverDone();

	CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);

};

class GameOverScene : public cocos2d::Scene
{
public:
	GameOverScene();
	~GameOverScene();
	bool init();
	CREATE_FUNC(GameOverScene);

	CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);

};

#endif // GAME_OVER_SCENE_H_