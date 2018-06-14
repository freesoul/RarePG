#include "Lifebar.h"
#include "Enemy.h"
#include "Constants.h"
#include "Game.h"
#include "Gfx.h"

Lifebar::Lifebar(Enemy* e, float _width) : width(_width) {
	holder = e;
	setTexture(Game::s_game->gfx.txLifebar);
	SetOrigin(width/2, 0);
	setTextureRect(sf::IntRect(0, 0, width, 14));
}


bool Lifebar::Update()
{
	sf::FloatRect gb = holder->GetGlobalBounds();
	SetPosition(gb.left + holder->GetLocalBounds().width/2 , gb.top -15);
	return true;
}

void Lifebar::UpdateLifeBar()
{
	sf::FloatRect gb = holder->GetGlobalBounds();
	float c_width = (holder->GetCurrentHP() / holder->GetMaxHP()) * width;
	setTextureRect(sf::IntRect(0, 0, c_width, 10));

}