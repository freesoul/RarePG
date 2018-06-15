#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Object.h"

#include <deque>
#include <vector>


struct Wave {
	std::string monster_class;
	int number;
};

struct LevelEvent {
	enum LevelEventType { Wait, WaitForAllDead, Wave, Boss } levelEvent;
	unsigned int info;
};

class Level : public Object {

public:
	enum Difficulty { Easy, Medium, Hard, GoodLuck } difficulty;

	Level() {};
	void Load(int level=1);
	bool Update();
	unsigned int GetLevelNumber() { return levelNumber;  }
	void DrawBackground();


private:
	unsigned int levelNumber;
	sf::Sprite background;
	void SetBackground(sf::Texture& t) { background.setTexture(t); };

	std::string levelName;

	/* LEVEL EVENTS */
	sf::Clock levelElapsed;
	float nextAmbientEffect;
	float wait;

	std::deque<LevelEvent> eventQueue;
	std::deque<Wave> waves;

	void AddWave(Wave wave);
	void AddWait(float time);
	void AddWaitForAllDead();
	// void AddBoss();

	void DoWave();

};

#endif
