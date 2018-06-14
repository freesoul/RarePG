#ifndef _SHADOW_H_
#define _SHADOW_H_

#include "Constants.h"
#include "EllipseShape.h"
#include "Game.h"
#include "ObjectManager.h"
#include "Object.h"

class Shadow : public EllipseShape{
public:
	Shadow(D3D* _owner) : owner(_owner), customSize(false) {
		on = true;
		Game::s_game->objects.AddShadow(this);

		setRadius(sf::Vector2f(25,25));
		setOrigin(sf::Vector2f(10, 7.5f));
		setFillColor(sf::Color(0,0,0,140));
	};

	void SetShadowDimensions(float w, float h){
		setRadius(sf::Vector2f(w,h));
		setOrigin(sf::Vector2f(w/2,h/2));
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
			sf::Vector3f owner_pos3d = owner->GetWorldPosition();
			sf::Vector3f pos = owner_pos3d;
			pos.y = MAX_Y;

			float width = owner->GetGlobalBounds().width;
			float height = owner->GetGlobalBounds().height;


			if (!customSize) {
				// Size
				setRadius(sf::Vector2f(width / 4, height / 8));
				//float scale = 1 - 0.35 * ((MAX_Y - pos.z) - pos.y) / (MAX_Y - pos.z);
				//setScale(sf::Vector2f(scale, scale));
				setOrigin(width / 2, height * 0.5f);
			}

			// Position;
			setPosition(WORLD_X(pos.x, pos.z), WORLD_Y(pos.y, (pos.z - height / 2)));


		}
		return true;
	}

private:
	bool customSize;
	D3D* owner;
	bool on;
};


#endif
