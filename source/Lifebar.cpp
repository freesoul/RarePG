#include "include/Lifebar.h"
#include "include/Enemy.h"
#include "include/Constants.h"
#include "include/Game.h"
#include "include/Gfx.h"

Lifebar::Lifebar(Enemy* e, float _width) : width(_width) {
	holder = e;
	setTexture(Game::s_game->gfx.txLifebar);
	setOrigin(width/2, 0);
	setTextureRect(sf::IntRect(0, 0, width, 14));
}


bool Lifebar::Update()
{
	sf::FloatRect gb = holder->getGlobalBounds();
	setPosition(gb.left + holder->getLocalBounds().width/2 , gb.top -15);
	return true;
}

void Lifebar::UpdateLifeBar()
{
	sf::FloatRect gb = holder->getGlobalBounds();
	float c_width = (holder->GetCurrentHP() / holder->GetMaxHP()) * width;
	setTextureRect(sf::IntRect(0, 0, c_width, 10));

}
