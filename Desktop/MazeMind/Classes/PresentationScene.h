#ifndef PRESENTATION_SCENE_H_
#define PRESENTATION_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class PresentationLayer : public cocos2d::LayerColor
{
public:
	PresentationLayer();
	virtual ~PresentationLayer();
	bool init();
	CREATE_FUNC(PresentationLayer);

	void PresentationDone();
	void startPart1();
	void startPart2();
	void startPart3();
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	void finish();

	CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);

private:
	Sprite* part1;
	Sprite* part2;
	Sprite* part3;

};

class PresentationScene : public cocos2d::Scene
{
public:
	PresentationScene();
	~PresentationScene();
	bool init();
	CREATE_FUNC(PresentationScene);

	CC_SYNTHESIZE_READONLY(PresentationLayer*, _layer, Layer);

};

#endif //PRESENTATION_SCENE_H_