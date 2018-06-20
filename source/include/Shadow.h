#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "Constants.h"
#include "EllipseShape.h"
#include "Game.h"
#include "ObjectManager.h"
#include "Object.h"

class Shadow : public sf::Drawable {
public:
	Shadow(D3D* _owner) : owner(_owner), customSize(false) {
		on = true;

		ellipseShape = EllipseShape();

		Game::s_game->objects.AddShadow(this);

		ellipseShape.setRadius(sf::Vector2f(25,25));
		ellipseShape.setOrigin(sf::Vector2f(10, 7.5f));
		setFillColor(sf::Color(0,0,0,100));
	};

	void setFillColor(sf::Color color){
		ellipseShape.setFillColor(color);
		line[0].color  = color;
		line[1].color = color;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(ellipseShape);
		target.draw(line, 2, sf::Lines);
	}

	void SetShadowDimensions(float w, float h){
		ellipseShape.setRadius(sf::Vector2f(w,h));
		ellipseShape.setOrigin(sf::Vector2f(w/2,h/2));
		customSize = true;
	}


	bool ShadowIsOn() { return on; };

	void ShadowOff()
	{
		if (on)
		{
			on ^= 1;
			Game::s_game->objects.RemoveShadow(this);
		}
	}

	void ShadowOn()
	{
		if (!on)
		{
			on ^= 1;
			Game::s_game->objects.AddShadow(this);
		}
	}

	~Shadow() { // virtual
		if (on)
			Game::s_game->objects.RemoveShadow(this);
	};

	bool Update() {
		if (on)
		{
			sf::Vector3f owner_pos3d = owner->getWorldPosition();
			sf::Vector3f pos = owner_pos3d;
			pos.y = MAX_Y;

			float width = owner->getGlobalBounds().width;
			float height = owner->getGlobalBounds().height;


			if (!customSize) {
				// Size
				// ellipseShape.setRadius(sf::Vector2f(width / 4, height / 8));
				// //float scale = 1 - 0.35 * ((MAX_Y - pos.z) - pos.y) / (MAX_Y - pos.z);
				// //setScale(sf::Vector2f(scale, scale));
				// ellipseShape.setOrigin(width / 2, height * 0.5f);
				ellipseShape.setRadius(sf::Vector2f(width / 4, height / 8));
				//float scale = 1 - 0.35 * ((MAX_Y - pos.z) - pos.y) / (MAX_Y - pos.z);
				//setScale(sf::Vector2f(scale, scale));
				ellipseShape.setOrigin(width / 4, height / 8);
			}

			// Position;
			//ellipseShape.setPosition(SCREEN_X(pos.x, pos.z), SCREEN_Y(pos.y, (pos.z - height / 2)));
			ellipseShape.setPosition(SCREEN_X(pos.x, pos.z), SCREEN_Y(pos.y, pos.z));

			line[0].position = owner->getPosition();
			line[1].position = ellipseShape.getPosition();


		}
		return true;
	}


private:
	EllipseShape ellipseShape;
	sf::Vertex line[2];
	bool customSize;
	D3D* owner;
	bool on;
};


#endif
