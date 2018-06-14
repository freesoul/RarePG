
#ifndef _D2D_H_
#define _D2D_H_

#include <SFML/Graphics.hpp>

class D2D : virtual public sf::Drawable, virtual public sf::Transformable {
public:
	D2D(bool _bGui = false);
	virtual ~D2D();

	virtual sf::FloatRect getLocalBounds() const = 0;
	virtual sf::FloatRect getGlobalBounds() const = 0;
	// virtual void setOrigin(float x, float y) = 0;
	// virtual sf::Vector2f GetOrigin() = 0;
	// virtual void setScale(sf::Vector2f scale) = 0;
	// virtual sf::Vector2f GetScale() = 0;
	// virtual void Move(float x, float y) = 0;
	// virtual void setPosition(float x, float y) = 0;
	// virtual sf::Vector2f getPosition() = 0;
	// virtual void SetRotation(float r) = 0;
	// virtual float GetRotation() = 0;
	virtual void setColor(const sf::Color& color) = 0;
	// virtual sf::Transform GetTransform() = 0;
	//
	// virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

private:
	bool bGui;
};

#endif
