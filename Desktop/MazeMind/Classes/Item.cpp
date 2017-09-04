#include "Item.h"
#include "Enemy.h"
#include <typeinfo>
#include "MapManager.h"
#include "Enums.h"
#include "Player.h"
#include "SoundManager.h"


//Method which create an item based on a image file stored in the "Resources" Directory of the project

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

//Method which schedules the Item's behaviour every Frame

void Item::update(float dt) {
    
	if (this->getBoundingBox().intersectsRect(player->getBoundingBox())) {
		this->runAction(FadeOut::create(1.0f));
		SoundManager::getInstance()->startDropItemSound();
		player->gotcha(this);
		this->getParent()->removeChild(this);
	}

}

//Getters & Setters

void Item::setPlayer(Player* player) {
	this->player = player;
}

Player* Item::getPlayer() {
	return this->player;
}

Thing Item::getType() {
	return this->type;
}

void Item::setType(Thing type) {
	this->type = type;
}
