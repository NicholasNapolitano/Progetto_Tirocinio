#ifndef __HUD_LAYER__H__
#define __HUD_LAYER__H__

#pragma once
#include "cocos2d.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class MapManager;

class HudLayer : public cocos2d::Layer
{

public:
	HudLayer(void);

	~HudLayer(void);


private:
	cocos2d::ui::Button *button;
	cocos2d::ui::Button *closeButton;
	Label* pauseLabel;
	Label* score;
};

#endif //__HUD_LAYER_H__