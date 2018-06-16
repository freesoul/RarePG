#ifndef _ACTIONABLE_H_
#define _ACTIONABLE_H_

#include <SFML/Graphics.hpp>

#include "Input.h"

class Actionable {
public:

	Actionable();
	virtual ~Actionable();

	void SetMouseAction(Input::MouseActionType type, sf::IntRect* box = 0);
	void UnsetMouseAction(Input::MouseActionType type);
	virtual void OnMouseLeftDown() {};
	virtual void OnMouseLeftReleased() {};

protected:

};


#endif
