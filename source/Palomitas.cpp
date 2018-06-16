#include "include/Palomitas.h"
#include "include/Game.h"

float Palomita::direction = 0;


Palomita::Palomita() : AnimatedSprite(Game::s_game->gfx.txPalomitas)
{

	if(!direction)
		RandomizeDirection();

	x_speed = 150 + std::rand() % 100;
	x_speed *= direction;

	setPosition(-200 + ((1024+200)*((int)direction==-1)), 25 + std::rand() % 150);
	setScale(sf::Vector2f(0.2, 0.2));
	SetTexture(Game::s_game->gfx.txPalomitas);
	AddFrame(1, sf::IntRect(0, 0, 388, 341));
	AddFrame(1, sf::IntRect(0, 341, 388, 341));
	AddFrame(1, sf::IntRect(0, 341*2, 388, 341));
	RunSequence(1);
}

void Palomita::RandomizeDirection(){
	direction = -1 + 2*((int)std::rand()%2);
}

bool Palomita::DeltaUpdate(float elapsed)
{
	move(elapsed * x_speed, 0);

	sf::Vector2f pos = getPosition();

	if (pos.x > 1100 || pos.x < -200)
		return false;

	return true;
}
