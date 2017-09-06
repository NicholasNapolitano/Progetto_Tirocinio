#include "SettingsScene.h"
#include "GameManager.h"
#include "SimpleAudioEngine.h"
#include "SoundManager.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

Scene* SettingsScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SettingsScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool SettingsScene::init()
{
	//////////////////////////////
	// 1. super init first
	if (!Layer::init())
	{
		return false;
	}
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	this->core = GameManager::getInstance();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Screen real dimensions
	auto vWidth = visibleSize.width;
	auto vHeight = visibleSize.height;

	// Original image
	auto backOrig = Sprite::create("Background.png");
	auto oWidth = backOrig->getContentSize().width;
	auto oHeight = backOrig->getContentSize().height;
	backOrig->setFlippedY(true);
	backOrig->setScale(vWidth / oWidth, vHeight / oHeight); // backOrig scaled to screen size
	backOrig->setPosition(vWidth / 2, vHeight / 2);

	// Create new texture with background in the exact size of the screen
	auto renderTexture = RenderTexture::create(vWidth, vHeight, Texture2D::PixelFormat::RGBA8888);
	renderTexture->begin();
	backOrig->visit();
	renderTexture->end();

	// Create new Sprite without scale, which perfoms much better
	background = Sprite::createWithTexture(renderTexture->getSprite()->getTexture());
	background->setPosition(vWidth / 2, vHeight / 2);
	addChild(background);

	/////////////////////////////
	// 2. add a menu item with "X" image, which is clicked to quit the program
	//    you may modify it.

	// add a "close" icon to exit the progress. it's an autorelease object
	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SettingsScene::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));


	auto menu_item_1 = MenuItemFont::create("Menu", CC_CALLBACK_1(SettingsScene::back, this));


	menu_item_1->setPosition(Point(origin.x, origin.y + visibleSize.height));
	menu_item_1->setAnchorPoint(Point(0, 1));
	menu_item_1->setFontSizeObj(menu_item_1->getFontSizeObj() / scaleFactor);

	auto menu = Menu::create(menu_item_1, closeItem, NULL);
	menu->setPosition(Point(0, 0));
	this->addChild(menu, 1);

	def = UserDefault::getInstance();

	music = def->getFloatForKey("MUSIC_VOLUME", 1.0);
	effects = def->getFloatForKey("EFFECTS_VOLUME", 1.0);

	// Create the slider
	ui::Slider* volumeSlider = ui::Slider::create();
	volumeSlider->loadBarTexture("sliderTrack.png");
	volumeSlider->loadSlidBallTextures("sliderThumb.png");
	volumeSlider->loadProgressBarTexture("sliderProgress.png");
	volumeSlider->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 1.5f ));
	volumeSlider->setPercent(def->getIntegerForKey("SLIDER_MUSIC", 100));
	volumeSlider->addEventListener(CC_CALLBACK_2(SettingsScene::sliderEvent1, this));
	this->addChild(volumeSlider);

	// Create the slider
	ui::Slider* effectsSlider = ui::Slider::create();
	effectsSlider->loadBarTexture("sliderTrack.png");
	effectsSlider->loadSlidBallTextures("sliderThumb.png");
	effectsSlider->loadProgressBarTexture("sliderProgress.png");
	effectsSlider->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 3.0f));
	effectsSlider->setPercent(def->getIntegerForKey("SLIDER_EFFECTS", 100));
	effectsSlider->addEventListener(CC_CALLBACK_2(SettingsScene::sliderEvent2, this));
	this->addChild(effectsSlider);

	return true;

}

//Method which change percentage of the MusicVolume slider

void SettingsScene::sliderEvent1(Ref* pSender, ui::Slider::EventType type) 
{
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{   
		if (musicVolume != nullptr && musicVolume->getParent() != NULL) {
			this->removeChild(musicVolume);
		}
		ui::Slider* volumeSlider = dynamic_cast<ui::Slider*>(pSender);
		int percent = volumeSlider->getPercent();
		__String *tempVolume = __String::createWithFormat("Music Volume : %d", percent);
		musicVolume = Label::createWithTTF(tempVolume->getCString(), "fonts/Marker Felt.ttf", 32);
		musicVolume->setPosition((Vec2(visibleSize.width / 2.0f, visibleSize.height / 1.35f)));
		musicVolume->setScale(musicVolume->getScale() / scaleFactor);
		this->addChild(musicVolume);
		if (percent*0.01 != music) {
			music = percent*0.01;
			def->setFloatForKey("MUSIC_VOLUME", music);
		}
		def->setIntegerForKey("SLIDER_MUSIC", percent);
		def->flush();
		CocosDenshion::SimpleAudioEngine::getInstance()->setBackgroundMusicVolume(def->getFloatForKey("MUSIC_VOLUME"));
	}

}

//Method which change percentage of the EffectsVolume slider

void SettingsScene::sliderEvent2(Ref* pSender, ui::Slider::EventType type)
{
	float scaleFactor = Director::getInstance()->getContentScaleFactor();
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
	{
		if (effectsVolume != nullptr && effectsVolume->getParent() != NULL) {
			this->removeChild(effectsVolume);
		}
		ui::Slider* effectsSlider = dynamic_cast<ui::Slider*>(pSender);
		int percent2 = effectsSlider->getPercent();
		__String *tempeffects = __String::createWithFormat("Sound Effects Volume : %d", percent2);
		effectsVolume = Label::createWithTTF(tempeffects->getCString(), "fonts/Marker Felt.ttf", 32);
		effectsVolume->setPosition((Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.45f)));
		effectsVolume->setScale(effectsVolume->getScale() / scaleFactor);
		this->addChild(effectsVolume);
		if (percent2*0.01 != effects) {
			effects = percent2*0.01;
			def->setFloatForKey("EFFECTS_VOLUME", effects);
		}
		def->setIntegerForKey("SLIDER_EFFECTS", percent2);
		def->flush();
		CocosDenshion::SimpleAudioEngine::getInstance()->setEffectsVolume(def->getFloatForKey("EFFECTS_VOLUME"));
	}

}

//Method which pops this scene

void SettingsScene::back(Ref *pSender)
{
	log("MENU");
	Director::getInstance()->popScene();
}

//Method which ends the game

void SettingsScene::menuCloseCallback(Ref* pSender)
{
	//Close the cocos2d-x game scene and quit the application
	core->endGame();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif

	/*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

	//EventCustom customEndEvent("game_scene_close_event");
	//_eventDispatcher->dispatchEvent(&customEndEvent);


}