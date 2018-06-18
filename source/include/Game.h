#ifndef _GAME_
#define _GAME_

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include "Gfx.h"
#include "Audio.h"
#include "Input.h"
#include "ObjectManager.h"
#include "WorldCollider.h"
#include "Gui.h"
#include "Level.h"

class Character;

class Game {
public:

	void HandleEvents();

	bool Load();
	void Run();


	enum Gamestate { gsIntro, gsMenu, gsBuy, gsLevel, gsResult, gsClosing, gsClosed };
	Gamestate gsGameState;

	sf::Clock timer;
	float elapsed;

	// Singleton
	static Game* inst() {
		if(!s_game)
			s_game = new Game;
		return s_game;
	}

  sf::RenderTexture renderer;
	sf::RenderWindow window;

	//
	// sf::Sprite* sCursor;
	// sf::FloatRect globalBounds;
	//
	// Singleton
	static Game* s_game;
	//
	//
	ObjManager objects;
	WorldCollider colliders;
	Input input;
	Gfx gfx;
	Audio audio;
	Level* level;
	GUI* gui; // Ptr due to size.
	//
	Character* character;





private:

	Game() { };

};



#endif
