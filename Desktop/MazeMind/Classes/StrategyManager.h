#ifndef __STRATEGY_MANAGER_H__
#define __STRATEGY_MANAGER_H__

#include "cocos2d.h"

class Player;
class Enemy;

class StrategyManager 
{
public:	
	
	static StrategyManager* getInstance();

	void defensiveAsset(Player* player);
	void defeatEnemy(Player* player);
	void distanceAttack(Player* player);
	void retreat(Player* player);
	void be_Patient(Player* player);
	void stun_Enemy(Player* player);
	void sentryBehaviour(Enemy* enemy);
	void kamikazeBehaviour(Enemy* enemy);
	void towerBehaviour(Enemy* enemy);
	void scoutBehaviour(Enemy* enemy);

protected:

	StrategyManager();

private:
	static StrategyManager* instance;



};

#endif //__STRATEGY_MANAGER_H__