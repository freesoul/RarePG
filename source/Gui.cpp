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
	if(id!=0 && id !=NULL)
	{
		sf::IntRect rect(x, y, subrect.width, subrect.height);
		Game::s_game->input.AddMouseAction(buttons.back(), Input::LeftReleased, &rect);
	}

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
				AddElement(Game::s_game->gfx.getGfx("BackgroundIntro"), 0, 0, sf::IntRect(0, 0, 1024, 768), BUTTON_ID_INTRO);
			}
			break;

			case GUI::Menu:
			{
				AddElement(Game::s_game->gfx.getGfx("BackgroundMenu"), 0, 0, sf::IntRect(0, 0, 1024, 768));
				AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 1024-200, 768-100, sf::IntRect(1, 1, 139, 40), BUTTON_ID_SALIR);
				AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 50, 768-100, sf::IntRect(1, 1+46*2, 143, 42), BUTTON_ID_JUGAR);

				AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 650, 350, sf::IntRect(1, 1+46*1, 143, 42), BUTTON_ID_PERSONAJE);
				//AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 0, 100*3, sf::IntRect(1, 1+46*3, 143, 42), BUTTON_ID_BORRAR);
				//AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 0, 100*4, sf::IntRect(1, 1+46*4, 143, 42), BUTTON_ID_ATRAS);
				//AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 0, 100*5, sf::IntRect(1, 1+46*5, 143, 42), BUTTON_ID_GUARDAR);
				//AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 0, 100*6, sf::IntRect(1, 1+46*6, 143, 42), BUTTON_ID_CANCELAR);
				AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 650, 250, sf::IntRect(1, 1+48*7, 143, 42), BUTTON_ID_NUEVO);
				AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 650, 450, sf::IntRect(1, 1+48*8, 143, 42), BUTTON_ID_OPCIONES);

				//AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 0, 500, sf::IntRect(0, 0, 1024, 768));
				//AddElement(Game::s_game->gfx.getGfx("MenuButtons"), 0, 700, sf::IntRect(0, 0, 1024, 768));

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


// Currently handles one item if there are multiple solapant.
void GUI::HandleLClick(unsigned int id)
{
	switch (id)
	{
	case BUTTON_ID_INTRO:
		{
			Load(GUI::Menu);
			Game::s_game->gsGameState = Game::gsMenu;
		}
		break;
	case BUTTON_ID_SALIR:
		{
			Unload();
			Game::s_game->gsGameState = Game::gsClosing;
		}
		break;
	case BUTTON_ID_JUGAR:
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
