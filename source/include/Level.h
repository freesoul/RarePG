#ifndef _LEVEL_H_
#define _LEVEL_H_

#include "Object.h"

#include <deque>
#include <vector>

typedef std::vector<int> Wave;

struct LevelEvent {
	enum LevelEventType { Wait, WaitForAllDead, Wave, Boss } levelEvent;
	unsigned int info;
};

class Level : public Object {

public:
	enum Difficulty { Easy, Medium, Hard, GoodLuck } difficulty;

	Level() {};
	void Load();
	bool Update();
	unsigned int GetLevelNumber() { return levelNumber;  }
	void DrawBackground();


private:
	unsigned int levelNumber;
	sf::Sprite background;
	void SetBackground(sf::Texture& t) { background.setTexture(t); };


	/* LEVEL EVENTS */
	sf::Clock levelElapsed;
	float wait;

	std::deque<LevelEvent> eventQueue;
	std::vector<Wave> waves;

	void AddWave();
	void AddWait(float time);
	void AddWaitForAllDead();
	void AddBoss();

	void DoWave();


};

#endif
