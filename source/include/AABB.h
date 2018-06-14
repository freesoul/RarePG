#ifndef _AABB_H_
#define _AABB_H_

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>


struct BoundingBox
{
	sf::FloatRect localBounds;
	sf::Transform transform;
};


namespace AABB{


struct rectangle {
	sf::Vector2f vertex[4];
};

	bool collision(BoundingBox& s1, BoundingBox& s2);
	void  project(sf::Vector2f& axis, rectangle* _rectangle, float &min, float &max);
	void normalize(sf::Vector2f& vector);
	float dot(sf::Vector2f& vector1, sf::Vector2f& vector2);
	float distance(float minA, float maxA, float minB, float maxB) ;
};


#endif