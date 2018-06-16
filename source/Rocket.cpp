#include "include/Rocket.h"
#include "include/Game.h"
#include "include/Constants.h"
#include "include/Character.h"
#include "include/Collider.h"

#include <cmath>

Rocket::Rocket(Collider::Type _type) : Collider(_type) {

	Game* g = Game::inst();

	setTexture(g->gfx.txMisiles);

	speed = sf::Vector3f(0,0,0);
	acceleration = sf::Vector3f(0,0,0);

	follow = 0;

	if (type == Collider::PlayerCast)
	{
		sf::Vector3f character_position = g->character->getWorldPosition();
		setTextureRect(sf::IntRect(20, 0, 20, 40));
		setWorldPosition(
			character_position.x,
			character_position.y,
			character_position.z
		);
	} else {
		setTextureRect(sf::IntRect(0, 0, 20, 40));
		setWorldPosition(
			std::rand() % 1024 + 10,
			-50 - std::rand() % 150,
			std::rand() % MAX_Z
		);
	}
	setOrigin(10, 40);

}


void Rocket::AproximateAcceleration(sf::Vector3f to, sf::Vector3f from)
{

	float t = 1;
	float module = ROCKET_ACCELERATION;
	float cModule;

	do {
		acceleration.x = 2 * (to.x - from.x - speed.x*t) / (t*t);
		acceleration.y = 2 * (to.y - from.y - speed.y*t) / (t*t);
		acceleration.z = 2 * (to.z - from.z - speed.z*t) / (t*t);

		cModule = std::sqrt(acceleration.x*acceleration.x + acceleration.y*acceleration.y + acceleration.z*acceleration.z);
		t *= sqrt(sqrt(cModule / module));// Temporal, this may fail.
	} while (std::abs(module - cModule) > 0.01f);


}

Collider* Rocket::LookupTarget()
{
	Game* g = Game::inst();

	// To create.

	return (Collider*)g->character;
}

void Rocket::UpdateTarget(sf::Vector3f target) {

	sf::Vector3f rocket_pos = getWorldPosition();

	bool near = false;
	if (
		std::abs(rocket_pos.x - target.x) < 3 &&
		std::abs(rocket_pos.y - target.y) < 3 &&
		std::abs(rocket_pos.z - target.z)
	)
		near = true;

	AproximateAcceleration(
		target,
		getWorldPosition()
	);

	acceleration *= Game::inst()->elapsed;

	float ac_screen_x = SCREEN_X(acceleration.x, -speed.z);
	float ac_screen_y = SCREEN_Y(acceleration.y, -speed.z);

	float rotation = TODEGREES(atan2f(ac_screen_x, ac_screen_y)) - 90;

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
		UpdateTarget(follow->getWorldPosition());

	speed.x += acceleration.x;

	if (speed.x > ROCKET_MAX_SPEED)
		speed.x = ROCKET_MAX_SPEED;
	else if (speed.x < -ROCKET_MAX_SPEED)
		speed.x = -ROCKET_MAX_SPEED;

	speed.y += acceleration.y;

	if (speed.y > ROCKET_MAX_SPEED)
		speed.y = ROCKET_MAX_SPEED;
	else if (speed.y < -ROCKET_MAX_SPEED)
		speed.y = -ROCKET_MAX_SPEED;


	if (speed.z > ROCKET_MAX_SPEED)
		speed.z = ROCKET_MAX_SPEED;
	else if (speed.z < -ROCKET_MAX_SPEED)
		speed.z = -ROCKET_MAX_SPEED;

	speed.z += acceleration.z;

	// Move the sprite
	moveInWorld(
		speed.x * g->elapsed,
		speed.y * g->elapsed,
		speed.z * g->elapsed
	);
	// move(x_speed * g->elapsed, y_speed * g->elapsed);

	return true;
}
