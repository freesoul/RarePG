
#ifndef _SPRITE_H_
#define _SPRITE_H_

#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/Rect.hpp>

class Texture;

#include "Drawable2D.h"
#include <SFML/Graphics.hpp>


// Actually Sprite == D2D == sf::Drawable, sf::Transformable.

class Sprite : virtual public D2D {
public:

	Sprite();
	~Sprite()
	{
	};

		// // Old PascalCase methods
		// sf::FloatRect getLocalBounds() { return getLocalBounds(); };
		// sf::FloatRect getGlobalBounds() { return getGlobalBounds(); };
		//
		// void setOrigin(float x, float y) { setOrigin(x, y); };
		// sf::Vector2f GetOrigin() { return getOrigin(); };
		//
		// void setScale(sf::Vector2f scale) { setScale(scale); };
		// sf::Vector2f GetScale() { return getScale(); };
		//
		// void Move(float x, float y) { move(x, y); };
		//
		// void setPosition(float x, float y) { setPosition(sf::Vector2f(x, y)); };
		// sf::Vector2f getPosition() { return getPosition(); };
		//
		// void SetRotation(float r) { setRotation(r);  };
		// float GetRotation() { return getRotation(); };
		//
		// virtual void setColor(const sf::Color& color) { setColor(color); };
		//
		// sf::Transform GetTransform()
		// {
		// 	return getTransform();
		// }

	////// SFML LOWER LEVEL FUNCTIONS

		Sprite(const sf::Texture& texture);

		Sprite(const sf::Texture& texture, const sf::IntRect& rectangle);

		void setTexture(const sf::Texture& texture, bool resetRect = false);


		void setTextureRect(const sf::IntRect& rectangle);

		void setColor(const sf::Color& color);

		const sf::Texture* getTexture() const;

		const sf::IntRect& getTextureRect() const;

		const sf::Color& getColor() const;


		sf::FloatRect getLocalBounds() const;

		sf::FloatRect getGlobalBounds() const;

private:

	////////////////////////////////////////////////////////////
	/// \brief Draw the sprite to a render target
	///
	/// \param target Render target to draw to
	/// \param states Current render states
	///
	////////////////////////////////////////////////////////////
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	////////////////////////////////////////////////////////////
	/// \brief Update the vertices' positions
	///
	////////////////////////////////////////////////////////////
	void updatePositions();

	////////////////////////////////////////////////////////////
	/// \brief Update the vertices' texture coordinates
	///
	////////////////////////////////////////////////////////////
	void updateTexCoords();

	////////////////////////////////////////////////////////////
	// Member data
	////////////////////////////////////////////////////////////
	sf::Vertex         m_vertices[4]; ///< Vertices defining the sprite's geometry
	const sf::Texture* m_texture;     ///< Texture of the sprite
	sf::IntRect       m_textureRect; ///< Rectangle defining the area of the source texture to display

};

#endif
