#include <SFML/Graphics.hpp>
#include "include/Gui.h"
#include "include/Game.h"

// #include "Character.h" // TEMPORAL UNTIL  MOVE LEVEL LOADS TO LEVEL CLASS

bool GUI::Update()
{
	spCursor.setPosition(Game::s_game->input.mouse_x, Game::s_game->input.mouse_y);
	return true;
}

void GUI::DrawCursor()
{
	Game::s_game->renderer.draw(spCursor);
}

void GUI::LoadCursor()
{
	spCursor.setTexture(Game::s_game->gfx.getGfx("DefaultCursor"));
}

void GUI::UpdateLife(float p)
{
	float pixelsgone = 145 * (1-p);
	Lifeball->setPosition(88, 589 + pixelsgone);
	Lifeball->setTextureRect(sf::IntRect(0, pixelsgone, 154, 145-pixelsgone));
}




Button* GUI::AddElement(
	sf::Texture& tx,
	float x,
	float y,
	sf::IntRect subrect,
	unsigned int id,
	unsigned int alpha
) {

	buttons.push_back(new Button(id, tx, x, y, subrect, alpha));

	// Add trigger
	sf::IntRect rect(x, y, subrect.width, subrect.height);
	Game::s_game->input.AddMouseAction(buttons.back(), Input::LeftReleased, &rect);

	return buttons.back();
}

void GUI::Unload()
{

	// Delete drawables
	std::vector<Button*>::iterator it;
	for (it = buttons.begin(); it != buttons.end(); it++)
		delete *it;

	// Delete buttons
	buttons.clear();


}

void GUI::Load(GUI::States _state)
{

	if (state != _state)
	{
		Unload();

		state = _state;

		switch (state)
			{

			case GUI::Intro:
			{
				  AddElement(Game::s_game->gfx.getGfx("BackgroundIntro"), 0, 0, sf::IntRect(0, 0, 1024, 768), 1);
			}
			break;

			case GUI::Menu:
			{

			}
			break;


			case GUI::Level:
			{

					AddElement(Game::s_game->gfx.getGfx("FondoGUI"), 15, 768 - 520, sf::IntRect(0, 0, 1024, 520), 0, 155);

					AddElement(Game::s_game->gfx.getGfx("BotonGUI"), 380, 726, sf::IntRect(0, 0, 44, 44), 0, 155);
					AddElement(Game::s_game->gfx.getGfx("BotonGUI"), 380 + 46, 726, sf::IntRect(0, 0, 44, 44), 0, 155);
					AddElement(Game::s_game->gfx.getGfx("BotonGUI"), 380 + 45 * 2, 726, sf::IntRect(0, 0, 44, 44), 0, 155);
					AddElement(Game::s_game->gfx.getGfx("BotonGUI"), 380 + 45 * 3, 726, sf::IntRect(0, 0, 44, 44), 0, 155);
					AddElement(Game::s_game->gfx.getGfx("BotonGUI"), 380 + 45 * 4, 726, sf::IntRect(0, 0, 44, 44), 0, 155);
					AddElement(Game::s_game->gfx.getGfx("BotonGUI"), 380 + 45 * 5, 726, sf::IntRect(0, 0, 44, 44), 0, 155);

					Lifeball = AddElement(Game::s_game->gfx.getGfx("Bola"), 88, 589, sf::IntRect(0, 0, 154, 145), 0, 155);

					AddElement(Game::s_game->gfx.getGfx("Marcobola"), 81, 578, sf::IntRect(0, 0, 168, 168), 0, 155);
			}
				break;
			default:

				;
		}
	}

}

void GUI::HandleLClick(unsigned int id)
{
	switch (id)
	{
	case 1:
		{
			  Load(GUI::Level);
			  Game::s_game->level->Load();
			  Game::s_game->gsGameState = Game::gsLevel;
		}
		break;
	default:
		break;
	}

}
