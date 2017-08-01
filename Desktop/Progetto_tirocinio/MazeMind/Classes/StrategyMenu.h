#ifndef __STRATEGY_MENU_H__
#define __STRATEGY_MENU_H__

#include "cocos2d.h"

class GameManager;
class MapManager;
class Player;

class StrategyMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void setMapManager(MapManager* manager);
	void enterTheGame(Ref *pSender);
	void gun(Ref *pSender);
	void rifle(Ref *pSender);
	void sniper(Ref *pSender);
	void granade(Ref *pSender);
	void defeatEnemy(Ref *pSender);
	void distanceAttack(Ref *pSender);
	Player* getPlayer();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	GameManager* core;
	Player* player;
	MapManager* manager;

	// implement the "static create()" method manually
	CREATE_FUNC(StrategyMenu);
};

#endif // __STRATEGY_MENU_H__