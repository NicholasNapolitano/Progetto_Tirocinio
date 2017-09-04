#ifndef __ITEM_H__
#define __ITEM_H__

#include "cocos2d.h"
#include "Enums.h"

USING_NS_CC;

class Player;

class Item : public cocos2d::Sprite
{
public:
	static Item* create(const std::string& filename);
	void update(float dt) override;
	void setType(Thing thing);
	Thing getType();
	Player* getPlayer();
	void setPlayer(Player* player);


private:

	Thing type;
	Player* player;

};


#endif // __ITEM_H__