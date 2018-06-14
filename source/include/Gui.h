// TODO: class button with pressed down sprite.

#ifndef _GUI_H_
#define _GUI_H_

#include <SFML/Window.hpp>
#include "Button.h"
#include "Object.h"


/////////////// GUI CLASS.

class GUI : public Object {
public:

	enum States { Unloaded, Intro, Loading, Menu, Level, Buy } state;

	GUI()
	{
		state = Unloaded;
		Lifeball = 0;
		LoadCursor();
	};


	void Load(States _state);
	void Unload();

	void LoadCursor();
	void DrawCursor();

	// Within Update() occurs the button pressed checks.
	bool Update();
	void UpdateLife(float p);

	// Once a button is clicked, dispatches to handler
	void HandleLClick(unsigned int id);

private:

	// Tests wether a button has been clicked
	std::vector<Button*> buttons;

	Button* AddElement(
		sf::Texture& tx,
		float x,
		float y,
		sf::IntRect subrect,
		unsigned int id = 0,
		unsigned int alpha = 255
	);

	Button* Lifeball;

	sf::Sprite spCursor;
};

#endif
