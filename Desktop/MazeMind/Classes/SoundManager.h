#ifndef __SOUND_MANAGER_H__
#define __SOUND_MANAGER_H__

#include "cocos2d.h"

USING_NS_CC;

class SoundManager {

public:
    
	static SoundManager* getInstance();

	void startPresentationMusic();
	void startMenuMusic();
	void startGameMusic();
	void startBattleMusic();
	void startLoseSound();
	void startWinSound();
	void startVictorySound();
	void startGunSound();
	void startRifleSound();
	void startKnifeSound();
	void startSniperSound();
	void startGrenadeSound();
	void startGasSound();
	void startGrenadeOutSound();
	void startHurtScream();
	void stopMusic();
	void stopEffects();
	void pauseMusic();
	void pauseEffects();
	void resumeMusic();
	void resumeEffects();
	void startGunChosenSound();
	void startRifleChosenSound();
	void startSniperChosenSound();
	void startGrenadeChosenSound();
	void startKnifeChosenSound();
	void startRadiationChosenSound();
	void startDefeatEnemyChosenSound();
	void startDistanceAttackChosenSound();
	void startRetreatChosenSound();
	void startBePatientChosenSound();
	void startStunEnemyChosenSound();
	void startShieldChosenSound();
	void startArmorChosenSound();
	void startMaskChosenSound();
	void startArmguardChosenSound();
	void startDropItemSound();
	void startNormalExplorationChosenSound();
	void startGoToTheGoalExplorationChosenSound();

protected:
	
	SoundManager();

private:
	static SoundManager* instance;

};

#endif // __SOUND_MANAGER_H__