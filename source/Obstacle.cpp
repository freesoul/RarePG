
#include "include/Obstacle.h"
#include "include/Game.h"
#include <cmath>

// #include <iostream> // dbg

Obstacle::Obstacle(int _radius) : radius(_radius), enabled(true) {
	Game::s_game->level->AddObstacle(this);
};


Obstacle::~Obstacle() {
	if(enabled)
		Game::s_game->level->RemoveObstacle(this);
};


void Obstacle::setObstacleOn() {
	if(!enabled) {
		Game::s_game->level->AddObstacle(this);
		enabled=true;
	}
}

void Obstacle::setObstacleOff() {
	if(enabled){
		Game::s_game->level->RemoveObstacle(this);
		enabled=false;
	}
}


bool Obstacle::is_vertically_solapant(D3D* who) {
	float pos_a = who->getWorldPosition().y;
	float pos_b = getWorldPosition().y;
	float height_a = who->getLocalBounds().height;
	float height_b = getLocalBounds().height;
	float upper_a = pos_a + height_a;
	float upper_b = pos_b + height_b;
	return (
		(upper_b <= upper_a && upper_b >= pos_a) ||
		(upper_a <= upper_b && upper_a >= pos_b)
	);
}


bool Obstacle::separate_from(D3D* who, Entity who_to_move) {

	if(!is_vertically_solapant(who))
		return false;

	bool separated=false;

	// float SEPARATION_TIME = 0.01;

	float SEPARATION_PREVENTION = 1; // Pixels to prevent from monsters pushing us

	sf::Vector3f obstacle_pos = getWorldPosition();
	sf::Vector3f obstaculized_pos = who->getWorldPosition();

	sf::Vector2f distance_vector = sf::Vector2f(
				obstaculized_pos.x-obstacle_pos.x,
				obstaculized_pos.z-obstacle_pos.z
			);

	float distance_magnitude = distance_vector.x*distance_vector.x;
				distance_magnitude += distance_vector.y*distance_vector.y; // y=z

	distance_magnitude = sqrt(distance_magnitude);

	float move_amount;
	sf::Vector2f move_vector;

	if(distance_magnitude <= radius)
	{
		separated = true;
		// std::cout << "Obstacleeeeeh\n";
		move_amount = radius - distance_magnitude + SEPARATION_PREVENTION;
		move_vector = (distance_vector / distance_magnitude) * move_amount;
		// move_vector = (distance_vector / (distance_magnitude*SEPARATION_TIME)) * move_amount;
		// move_vector *= Game::s_game->elapsed;

		switch(who_to_move) {
			case OBSTACLE:
			{
				move_vector = -move_vector;
				this->moveInWorld(move_vector.x, 0, move_vector.y); // y = z
			}
			break;

			case OBSTACULIZED:
			{
				who->moveInWorld(move_vector.x, 0, move_vector.y); // y = z
			}
			break;

			case BOTH:
			{
				// Though note if that the obstacle keeps moving towards you...
				// ¡he pushes you anyways!
				move_vector = move_vector / 2.f;
				who->moveInWorld(move_vector.x, 0, move_vector.y); // y = z
				move_vector = -move_vector;
				this->moveInWorld(move_vector.x, 0, move_vector.y); // y = z
			}
			break;

		}
	}

	return separated;
}



bool Obstacle::is_obstacle(D3D* to_who) {

	if(!is_vertically_solapant(to_who))
		return false;

	sf::Vector3f this_pos = getWorldPosition();
	sf::Vector3f other_pos = to_who->getWorldPosition();

	sf::Vector3f distance_vector = other_pos - this_pos;

	float distance_magnitude = distance_vector.x*distance_vector.x;
				distance_magnitude += distance_vector.y*distance_vector.z;

	// Test for y-axis

	// ...

	// Make a method in Obstacle class to throw the D3D "who" out of obstacle range.


	distance_magnitude = sqrt(distance_magnitude);

	return distance_magnitude <= radius;

}
