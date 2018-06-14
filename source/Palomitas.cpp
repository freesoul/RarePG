#include "include/Palomitas.h"
#include "include/Game.h"

Palomita::Palomita() : AnimatedSprite(Game::s_game->gfx.txPalomitas)
{
	x_speed = 150 + std::rand() % 100;

	SetPosition(-400 + std::rand() % 300, 25 + std::rand() % 150);
	SetScale(sf::Vector2f(0.2, 0.2));
	SetTexture(Game::s_game->gfx.txPalomitas);
	AddFrame(1, sf::IntRect(0, 0, 388, 341));
	AddFrame(1, sf::IntRect(0, 341, 388, 341));
	AddFrame(1, sf::IntRect(0, 341*2, 388, 341));
	RunSequence(1);
}

bool Palomita::DeltaUpdate(float elapsed)
{
	Move(elapsed * x_speed, 0);

	if (GetPosition().x > 1100)
		return false;

	return true;
}
