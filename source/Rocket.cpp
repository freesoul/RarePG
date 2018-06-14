#include "include/Rocket.h"
#include "include/Game.h"
#include "include/Constants.h"
#include "include/Character.h"
#include "include/Collider.h"

#include <cmath>

Rocket::Rocket(Collider::Type _type) : Collider(_type) {

	Game* g = Game::inst();

	setTexture(g->gfx.txMisiles);

	x_speed = 0;
	y_speed = 0;
	x_acceleration = 0;
	y_acceleration = 0;
	follow = 0;

	if (type == Collider::PlayerCast)
	{
		setTextureRect(sf::IntRect(20, 0, 20, 40));
		setPosition(g->character->getPosition().x, g->character->getPosition().y);
	} else {
		setTextureRect(sf::IntRect(0, 0, 20, 40));
		setPosition(std::rand() % 1024 + 10, -50 - std::rand() % 150);
	}
	setOrigin(10, 40);

}


void Rocket::AproximateAcceleration(float px, float py, float dx, float dy)
{

	float t = 1;
	float module = ROCKET_ACCELERATION;
	float cModule;

	do {
		x_acceleration = 2 * (dx - px - x_speed*t) / (t*t);
		y_acceleration = 2 * (dy - py - y_speed*t) / (t*t);

		cModule = std::sqrt(x_acceleration*x_acceleration + y_acceleration*y_acceleration);
		t *= sqrt(sqrt(cModule / module));// Temporal, this may fail.
	} while (std::abs(module - cModule) > 0.01f);


}

Collider* Rocket::LookupTarget()
{
	Game* g = Game::inst();

	// To create.

	return (Collider*)g->character;
}

void Rocket::UpdateTarget(float x, float y) {

	bool near = false;
	if (std::abs(getPosition().x - x) < 3
		|| std::abs(getPosition().y - y) < 3)
		near = true;

	AproximateAcceleration(getPosition().x, getPosition().y, x, y);

	x_acceleration *= Game::inst()->elapsed;
	y_acceleration *= Game::inst()->elapsed;

	float rotation = TODEGREES(atan2f(y_acceleration, x_acceleration)) - 90;

	if(!near)
		setRotation(rotation);

}


bool Rocket::Update()
{
	Game* g = Game::inst();

		if (type == Collider::EnemyCast)
		{
			//if (IsOnRangeTo(g->character, ROCKET_RANGE_RADIUS))
			//{
				if (!follow)
					follow = g->character;
				// else
				// 	follow = 0;
			//}
		}
		else
		{
			follow = LookupTarget();
		}

	if (follow)
		UpdateTarget(follow->getPosition().x, follow->getPosition().y);

	x_speed += x_acceleration;

	if (x_speed > ROCKET_MAX_SPEED)
		x_speed = ROCKET_MAX_SPEED;
	else if (x_speed < -ROCKET_MAX_SPEED)
		x_speed = -ROCKET_MAX_SPEED;

	y_speed += y_acceleration;

	if (y_speed > ROCKET_MAX_SPEED)
		y_speed = ROCKET_MAX_SPEED;
	else if (y_speed < -ROCKET_MAX_SPEED)
		y_speed = -ROCKET_MAX_SPEED;

	// Move the sprite
	move(x_speed * g->elapsed, y_speed * g->elapsed);

	return true;
}
