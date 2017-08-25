#include "Item.h"
#include "Enemy.h"
#include <typeinfo>
#include "MapManager.h"
#include "Enums.h"
#include "Player.h"
#include "SoundManager.h"


Item* Item::create(const std::string& filename)
{
	Item *item = new (std::nothrow) Item();
	if (item && item->initWithFile(filename))
	{
		item->autorelease();
		//default state
		item->type = ANY_ONE;

		return item;
	}
	CC_SAFE_DELETE(item);
	return nullptr;
}

Thing Item::getType() {
	return this->type;
}

void Item::setType(Thing type) {
	this->type = type;
}

void Item::update(float dt) {
    
	if (this->getBoundingBox().intersectsRect(player->getBoundingBox())) {
		this->runAction(FadeOut::create(1.0f));
		player->gotcha(this);
		this->getParent()->removeChild(this);
	}

}