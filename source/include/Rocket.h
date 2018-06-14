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
	void UpdateTarget(float x, float y);
	void AproximateAcceleration(float px, float py, float dx, float dy);
	void Explode();

	Collider* follow;

	sf::Vector2f targetCoords;

	float x_acceleration, y_acceleration;
	float x_speed, y_speed;
};
#endif
