#include <SFML/Graphics.hpp>
#include "include/Game.h"
#include "include/Level.h"


// #include "Pulpo.h"
// #include "Rocket.h"
// #include "Palomitas.h"
// #include "Fruit.h"
// #include "Yoda.h"
// #include "MonoSmall.h"
// #include "Mono.h"
// #include "star.h"
// #include "Pollito.h"
//
// #include "Character.h"

void Level::Load()
{
	// Spawn character
	// Game::s_game->character = new Character(Character::Girl);

	// Set level ambient
	SetBackground(Game::s_game->gfx.txBackground1);
	// Game::s_game->audio.muFarm.play();

	// Design Level
	AddWait(3);
	AddWave();
	AddWaitForAllDead();
	AddWave();


	// Start timer
	levelElapsed.restart();
	wait = 0;

}

bool Level::Update() {

	// CHARACTER DEAD


	// ...


	// LEVEL LOGIC SUCESION
	if (!eventQueue.empty())
		switch (eventQueue.front().levelEvent)
		{
			case LevelEvent::Wait:
			{
				if (wait == 0)
				{
					wait = levelElapsed.getElapsedTime().asSeconds() + eventQueue.front().info;
				}
				else if (levelElapsed.getElapsedTime().asSeconds() > wait)
				{
					wait = 0;
					eventQueue.pop_front();
				}

			} break;

			case LevelEvent::WaitForAllDead:
			{
	 			 // if (Game::s_game->colliders.EnemiesDead())
					// eventQueue.pop_front();
			} break;

			case LevelEvent::Wave:
			{
				 eventQueue.pop_front();
				DoWave();
			}	break;

			default:
				break;
		}
	else {
		// LEVEL FINISHED


		return true;
	}

	// Normal update
	return true;
}

void Level::DrawBackground() {
	Game::s_game->renderer.draw(background);
}


void Level::DoWave()
{
	// new Pollito();
	/*
	if(waves.empty())
	return;

	std::vector<int>* wave;
	std::vector<int>::iterator it;

	Object* obj;

	wave = waves.at(waves.back());

	for(it=wave->begin(); it!=wave->end(); it++)
	{
	switch(*it)
	{
	case ID_PULPO:
	{
	new Pulpo(100,100);
	}
	break;
	}

	}

	waves.pop_back();
	*/
}


void Level::AddWait(float time)
{
	LevelEvent tmp;
	tmp.levelEvent = LevelEvent::Wait;
	tmp.info = time;
	eventQueue.push_back(tmp);
}

void Level::AddWave() {
	LevelEvent tmp;
	tmp.levelEvent = LevelEvent::Wave;
	eventQueue.push_back(tmp);
}

void Level::AddWaitForAllDead() {
	LevelEvent tmp;
	tmp.levelEvent = LevelEvent::WaitForAllDead;
	eventQueue.push_back(tmp);
}

void Level::AddBoss() {
	LevelEvent tmp;
	tmp.levelEvent = LevelEvent::Boss;
	eventQueue.push_back(tmp);
}
