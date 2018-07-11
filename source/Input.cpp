#include <SFML/Window.hpp>

#include "include/Game.h"
#include "include/Input.h"

// #include "Character.h"
// #include "Weapon.h"
// #include <queue>
#include "include/Actionable.h"

Input::Input() {
	ClearBuffer();
}



void Input::ClearBuffer()
{
	buffer.clear();
}



void Input::ProcessInputEvent(sf::Event &msg)
{
	switch(msg.type)
	{

	// Mouse related
	case sf::Event::KeyPressed:
	{
	/*  if (Game::inst()->gsGameState == Game::gsLevel)
	  {
		  switch (msg.text.unicode)
		  {
		  case sf::Keyboard::Num1:
			  Game::inst()->weapon->SelectWeapon(Weapon::tHandgun, true);
			  bMouseLeftIsDown = false;  // tmp case to delete laser
			  break;
		  case sf::Keyboard::Num2:
			  Game::inst()->weapon->SelectWeapon(Weapon::tLaser, true);
			  break;
		  }
	  }*/
	}

	case sf::Event::MouseButtonPressed:
	{

	}break;

	case sf::Event::MouseButtonReleased:
	{
	   std::vector<MouseAction>::iterator it;
	   if (msg.mouseButton.button == sf::Mouse::Left)
	   {

		   for (it = mouseLeftReleaseActions.begin(); it != mouseLeftReleaseActions.end(); it++)
		   if (it->box == 0)
		   {
			   it->actionable->OnMouseLeftReleased();
			   break;

		   }
		   else   if (MouseInside(*it->box)) {
			   it->actionable->OnMouseLeftReleased();
			   break;
		   }
	   }
	}break;

	// Text input related
	case sf::Event::TextEntered:
		{
			if(msg.text.unicode == '\b')
			{
				if(!buffer.isEmpty())

					buffer = sf::String(buffer.toAnsiString().substr(0, buffer.getSize()-1));
				else
					buffer.insert(buffer.getSize(), msg.text.unicode);
			}

		}break;

	case sf::Event::Closed:
		Game::s_game->gsGameState = Game::gsClosing;
		break;
	default:
		break;
	}


}

bool Input::MouseInside(sf::IntRect rect)
{
	return (mouse_x > rect.left &&
		mouse_x < (rect.left + rect.width) &&
		mouse_y > rect.top &&
		mouse_y < (rect.top + rect.height));
}


void Input::HandleInput()
{
	//// STATES.

	// Mouse Down actions
	std::vector<MouseAction>::iterator it;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		for (it = mouseLeftDownActions.begin(); it != mouseLeftDownActions.end(); it++)
			if (it->box == 0)
				it->actionable->OnMouseLeftDown();

	// Mouse position
	sf::Vector2i coords(sf::Mouse::getPosition(Game::inst()->window).x,
	sf::Mouse::getPosition(Game::inst()->window).y);

	sf::Vector2f newcoords = Game::inst()->window.mapPixelToCoords(coords);

	mouse_x = newcoords.x;
	mouse_y = newcoords.y;

	//// EVENTS.
}



void Input::AddMouseAction(
	Actionable* actionable,
	MouseActionType type,
	sf::IntRect* box
) {

	MouseAction m(actionable);

	if (box != 0)
		m.box = new sf::IntRect(box->left, box->top, box->width, box->height);

	switch (type)
	{
	case LeftReleased:
		mouseLeftReleaseActions.push_back(m);
		break;
	case LeftIsDown:
		mouseLeftDownActions.push_back(m);
		break;
	default:
		break;
	};
}


void Input::RemoveMouseAction(Actionable* actionable, MouseActionType type)
{

	std::vector<MouseAction>::iterator it;

	std::vector<MouseAction>* v=0;

	switch (type)
	{
		case LeftReleased:
			v = &mouseLeftReleaseActions;
			break;
		case LeftIsDown:
			v = &mouseLeftDownActions;
			break;
		default:
			break;
	};

	for (it = (*v).begin(); it != (*v).end(); it++)
	if (it->actionable == actionable)
	{
		(*v).erase(it);
		return;
	}


}
