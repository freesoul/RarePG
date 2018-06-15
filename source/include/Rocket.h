#ifndef _ROCKET_H_
#define _ROCKET_H_

#include "Collider.h"
#include "Sprite.h"
#include "Object.h"
#include "Drawable2D.h"

class Rocket : public Collider, public Sprite {
public:

	Rocket(Collider::Type _type);
	bool Update();

private:
	Collider* LookupTarget();
	void UpdateTarget(sf::Vector3f target);
	void AproximateAcceleration(sf::Vector3f dest, sf::Vector3f pos);
	void Explode();

	Collider* follow;

	sf::Vector3f targetCoords;

	sf::Vector3f acceleration;
	sf::Vector3f speed;
};
#endif
