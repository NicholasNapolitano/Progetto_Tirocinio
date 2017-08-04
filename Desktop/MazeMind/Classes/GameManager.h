#ifndef __GAME_MANAGER_H__
#define __GAME_MANAGER_H__

class SoundManager;
class Player;
class Enemy;

class GameManager
{
public:

	static GameManager* getInstance();

	bool inPause();
	void startGame();
	void selectStrategy();
	void playGame(Player* player);
	void startBattle(Enemy* enemy, Player* player);
	void resumeExploration();
	void pauseGame();
	void resumeGame();
	void winGame();
	void loseGame();
	void endGame();
	void restartGame();


protected:
	
	GameManager();

private:
	static GameManager* instance;
};

#endif // __GAME_MANAGER_H__