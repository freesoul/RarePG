
#ifndef _DRWBASE_H_
#define _DRWBASE_H_

#include <SFML/Graphics.hpp>

class DrawableBase : virtual public sf::Drawable {
public:
	virtual ~DrawableBase()
	{
	};


	virtual sf::FloatRect GetLocalBounds() = 0;
	virtual sf::FloatRect GetGlobalBounds() = 0;
	virtual void SetOrigin(float x, float y) = 0;
	virtual sf::Vector2f GetOrigin() = 0;
	virtual void SetScale(sf::Vector2f scale) = 0;
	virtual sf::Vector2f GetScale() = 0;
	virtual void Move(float x, float y) = 0;
	virtual void SetPosition(float x, float y) = 0;
	virtual sf::Vector2f GetPosition() = 0;
	virtual void SetRotation(float r) = 0;
	virtual float GetRotation() = 0;
	virtual void SetColor(const sf::Color& color) = 0;
	virtual sf::Transform GetTransform() = 0;

	// Virtual for D3D
	virtual void SetWorldPosition(float _x, float _y, float _z){};

	virtual sf::Vector3f GetWorldPosition(){
		return sf::Vector3f(0, 0, 0);
	};

	virtual void MoveInWorld(float _x, float _y, float _z){};

private:

};

#endif
