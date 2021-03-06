#ifndef __STRATEGY_MENU_H__
#define __STRATEGY_MENU_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class GameManager;
class MapManager;
class Player;

class StrategyMenu : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();
	void menu(Ref *pSender);
	void setMapManager(MapManager* manager);
	void enjoyTheGame(Ref *pSender);
	void gun(Ref *pSender);
	void rifle(Ref *pSender);
	void sniper(Ref *pSender);
	void grenade(Ref *pSender);
	void knife(Ref *pSender);
	void radiation(Ref *pSender);
	void defeatEnemy(Ref *pSender);
	void distanceAttack(Ref *pSender);
	void retreat(Ref *pSender);
	void bePatient(Ref *pSender);
	void stunEnemy(Ref *pSender);
	void shield(Ref *pSender);
	void armor(Ref *pSender);
	void mask(Ref *pSender);
	void armguard(Ref *pSender);
	void normal(Ref *pSender);
	void goToTheGoal(Ref *pSender);
	Player* getPlayer();

	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

private:
	GameManager* core;
	Player* player;
	MapManager* manager;
	cocos2d::Sprite* strategySelected;
	cocos2d::Sprite* weaponSelected;
	cocos2d::Sprite* protectionSelected;
	cocos2d::Sprite* crawlingSelected;
	cocos2d::Size visibleSize;
	cocos2d::ui::ScrollView* scrollView;
	cocos2d::Sprite* background;

	// implement the "static create()" method manually
	CREATE_FUNC(StrategyMenu);
};

#endif // __STRATEGY_MENU_H__