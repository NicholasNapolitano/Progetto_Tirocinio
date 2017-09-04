#ifndef PRODUCERS_SCENE_H_
#define PRODUCERS_SCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class ProducersLayer : public cocos2d::LayerColor
{
public:
	ProducersLayer();
	virtual ~ProducersLayer();
	bool init();
	CREATE_FUNC(ProducersLayer);

	void ProducersDone();
	void entrance();
	void exit();

	CC_SYNTHESIZE_READONLY(cocos2d::LabelTTF*, _label, Label);

private:
	Sprite* producer;
	Sprite* agency;
	Sprite* engine;

};

class ProducersScene : public cocos2d::Scene
{
public:
	ProducersScene();
	~ProducersScene();
	bool init();
	CREATE_FUNC(ProducersScene);

	CC_SYNTHESIZE_READONLY(ProducersLayer*, _layer, Layer);

};

#endif //PRODUCERS_SCENE_H_