#include "SimpleAudioEngine.h"
#include "SoundManager.h"

#include "cocos2d.h"

USING_NS_CC;

SoundManager* SoundManager::instance = 0;

SoundManager::SoundManager() {
}

SoundManager* SoundManager::getInstance()
{
	if (instance == 0)
		instance = new SoundManager;
	return instance;
}

void SoundManager::startMenuMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("Menu.mp3");
	audio->playBackgroundMusic("Menu.mp3");
}


void SoundManager::startGameMusic() 
{

	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("Crash3.mp3");
	audio->playBackgroundMusic("Crash3.mp3");
}

void SoundManager::startDeathScream() 
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Death.mp3");
}

void SoundManager::startShotSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("GunShot.mp3");
}

void SoundManager::startWinSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Win.mp3");
}

void SoundManager::startLoseSound() 
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Lose.mp3");
}

void SoundManager::stopMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopBackgroundMusic();
}


void SoundManager::stopEffects()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->stopAllEffects();
}

void SoundManager::resumeEffects()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->resumeAllEffects();
}

void SoundManager::resumeMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->resumeBackgroundMusic();
}