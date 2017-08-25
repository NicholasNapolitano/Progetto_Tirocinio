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
	audio->preloadBackgroundMusic("Exploration.mp3");
	audio->playBackgroundMusic("Exploration.mp3");
}

void SoundManager::startBattleMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("Battle.mp3");
	audio->playBackgroundMusic("Battle.mp3");
}

void SoundManager::startHurtScream()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Hurt.mp3");
}

void SoundManager::startGunSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Gun.mp3");
}

void SoundManager::startRifleSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Rifle.mp3");
}

void SoundManager::startSniperSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Sniper.mp3");
}

void SoundManager::startKnifeSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Knife.mp3");
}

void SoundManager::startGrenadeSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Grenade.mp3");
}

void SoundManager::startGasSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Gas.mp3");
}

void SoundManager::startGrenadeOutSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("GrenadeOut.mp3");
}

void SoundManager::startWinSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Win.mp3");
}

void SoundManager::startVictorySound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Victory.mp3");
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

void SoundManager::startGunChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("GunChosen.mp3");
}

void SoundManager::startRifleChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("RifleChosen.mp3");
}

void SoundManager::startSniperChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("SniperChosen.mp3");
}

void SoundManager::startGrenadeChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("GrenadeChosen.mp3");
}

void SoundManager::startKnifeChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("KnifeChosen.mp3");
}

void SoundManager::startRadiationChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("RadiationChosen.mp3");
}

void SoundManager::startDefeatEnemyChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("DefeatEnemy.mp3");
}

void SoundManager::startDistanceAttackChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("DistanceAttack.mp3");
}

void SoundManager::startRetreatChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Retreat.mp3");
}

void SoundManager::startBePatientChosenSound() 
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("BePatient.mp3");
}

void SoundManager::startStunEnemyChosenSound() 
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("StunEnemy.mp3");
}

void SoundManager::startShieldChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Shield.mp3");
}

void SoundManager::startArmorChosenSound() 
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Armor.mp3");
}

void SoundManager::startMaskChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Mask.mp3");
}

void SoundManager::startArmguardChosenSound()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playEffect("Armguard.mp3");
}