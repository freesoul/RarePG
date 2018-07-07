//
#include "include/Constants.h"
#include "include/Game.h"
#include "include/Input.h"

// Debug
// #include "Spine/spine-sfml.h"
// #include "SpineDrawable.h" // testing
// #include "include/Sprite.h"
// #include "include/AnimatedSprite.h"

#include "include/Level.h"
#include "include/Character.h"
#include "include/Palomitas.h"
// #include "include/Debug.h"
#include "include/Fruit.h"

#include "include/Rocket.h"
#include "include/Pulpo.h"
#include "include/MonoSmall.h"
#include "include/Pollito.h"
#include "include/Yoda.h"


bool Game::Load() {

	std::srand(std::time(0));

	// renderer.create(sf::VideoMode(1024, 768), "Juego", sf::Style::Fullscreen);
	window.create(sf::VideoMode(VIEW_WIDTH, VIEW_HEIGHT), "Juego");

	// globalBounds = sf::FloatRect(WORLD_LEFT_BOUND, WORLD_UPPER_BOUND, WORLD_WIDTH, WORLD_HEIGHT);

	// renderer.setSize(sf::Vector2u(1100, 680));
	// renderer.setPosition(sf::Vector2i(100, 1));

	window.setView(sf::View(sf::FloatRect(0, 0, VIEW_WIDTH, VIEW_HEIGHT)));

	window.setMouseCursorVisible(false);

	renderer.create(
		VIEW_WIDTH,
		VIEW_HEIGHT
	);

	gfx.load();
	audio.Load(); // todo: convert to same case

	gui = new GUI;
	gui->Load(GUI::Intro);

	level = new Level;

	gsGameState = gsIntro;

	return true;
}

void Game::Run() {

	// Time loads
	const float SPF = 0.02;
	float nextTime=0;
	float currentTime = 0;
	elapsed = 0;

	gsGameState = gsIntro;


	while(gsGameState != gsClosed)
	{

		// Handle Game events and State input.
		HandleEvents();

		input.HandleInput();

		///// GAME STATE LOGIC
		switch(gsGameState) {
			case Game::gsIntro:
				/* SWITCH HANDLED BY INPUT */
				break;
			case Game::gsMenu:

			break;
			case Game::gsResult:

				break;

			case Game::gsLevel:
			{
				  level->Update();
			}
			break;

			case Game::gsClosing:
				gsGameState = gsClosed;
				break;
			default:
				break;
			}


		// UPDATE GAME LOGIC
		// Calculate current elapsed time
		currentTime = timer.getElapsedTime().asSeconds();
		if (currentTime>nextTime)
		{
			elapsed = SPF;
			nextTime = currentTime + SPF;

			objects.UpdateScene();

		}

		////// DRAW
		// window.clear();
		// renderer.clear(); // bg is drawn anyways.
		//
		level->DrawBackground(); // extract gui bg from here, and put this in switch
		objects.DrawScene();

		if(gsGameState==Game::gsLevel) //remove this
			level->applySceneShaders(); // put this in switch after level->DrawBackground

		gui->DrawCursor();
//
//
#ifdef DBG_HITBOXES
		colliders.DebugHitboxes();
#endif
		renderer.display();	// Renderer is separated from window, so we can
												// Postprocess it with shaders in a fixed "window" size
		window.draw(sf::Sprite(renderer.getTexture()));
		window.display();

	} /////// END GAME LOOP

	window.close();
}




void Game::HandleEvents()
{
	sf::Event msg;

	while (window.pollEvent(msg))
	{
		switch (msg.type)
		{

		case sf::Event::Closed:
			gsGameState = gsClosing;
			break;


		default:
			input.ProcessInputEvent(msg);
			break;
		}
	}
}
