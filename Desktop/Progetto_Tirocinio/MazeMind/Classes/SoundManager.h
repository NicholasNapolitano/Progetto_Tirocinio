#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class SoundManager {

public:
    
	static SoundManager* getInstance();

	void startMenuMusic();
	void startGameMusic();
	void startLoseSound();
	void startWinSound();
	void startShotSound();
	void startDeathScream();
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