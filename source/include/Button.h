// TODO: class button with pressed down sprite.

#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Sprite.h"
#include "Actionable.h"
#include "Drawable2D.h"

/////////////// BUTTON CLASS.

class Button : public Actionable, public Sprite {
public:
	Button(unsigned int _ID, sf::Texture& tx, float x, float y, sf::IntRect subrect, unsigned int alpha) : ID(_ID), D2D(true) {
		// setOrigin(0,0);
		setTexture(tx);
		setTextureRect(subrect);
		setPosition(x, y);
		setColor(sf::Color(255, 255, 255, alpha));
	};
	~Button();
	void OnMouseLeftReleased();
private:
	unsigned int ID;
};


#endif
