
#ifndef _INPUT_H_
#define _INPUT_H_


#include <SFML/Window.hpp>

class Actionable;

class Input {
public:

	enum MouseActionType { LeftIsDown, LeftReleased, RightReleased };

	struct MouseAction
	{
	public:
		MouseAction(Actionable* a) : box(0), actionable(a) {};
		Actionable* actionable;
		sf::IntRect* box;
		/*friend bool operator==(const MouseAction& left, const MouseAction& right)
		{
			return left.actionable == right.actionable &&
				left.box == right.box;
		};*/
	};


	// States
	float mouse_x;
	float mouse_y;

	// String buffer
	sf::String buffer;


	// Methods
	Input();

	void AddMouseAction(Actionable* actionable, MouseActionType type, sf::IntRect* box);
	void RemoveMouseAction(Actionable* actionable, MouseActionType type);

	void HandleInput();
	void ProcessInputEvent(sf::Event &msg);

	void ClearBuffer();			// Call it manually

private:
	std::vector<MouseAction> mouseLeftDownActions;
	std::vector<MouseAction> mouseLeftReleaseActions;

	bool MouseInside(sf::IntRect rect);

};

#endif
