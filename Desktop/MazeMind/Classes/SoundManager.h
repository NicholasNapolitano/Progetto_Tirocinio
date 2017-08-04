#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class SoundManager {

public:
    
	static SoundManager* getInstance();

	void startMenuMusic();
	void startGameMusic();
	void startBattleMusic();
	void startLoseSound();
	void startWinSound();
	void startVictorySound();
	void startGunSound();
	void startRifleSound();
	void startSniperSound();
	void startGranadeSound();
	void startGranadeOutSound();
	void startHurtScream();
	void stopMusic();
	void stopEffects();
	void resumeMusic();
	void resumeEffects();

protected:
	
	SoundManager();

private:
	static SoundManager* instance;

};

#endif // __SOUND_MANAGER_H__