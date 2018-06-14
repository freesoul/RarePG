#include "Fruit.h"
#include "Game.h"
#include "Collider.h"
#include "Gfx.h"
#include <stdio.h>
#include "Constants.h"
#include "Shadow.h"

Fruit::Fruit() : Collider(Collider::Bonus), D3D(true) {

	setTexture(Game::s_game->gfx.txFruits);

	setTextureRect(sf::IntRect(50*(std::rand()%4), 50*(std::rand()%4), 50, 50));

	SetWorldPosition(std::rand() % (1024 - 50), -200, std::rand() % MAX_Z);

	setOrigin(25, 25);

	shadow->setFillColor(sf::Color(0, 0, 0 , 150));
	
}

bool Fruit::Update()
{
	if (GetWorldPosition().y < MAX_Y)
		MoveInWorld(0, 150 * Game::s_game->elapsed, 0);
	else {
		if (getDisappearStatus() == NotStarted)
		{
			return false;
		}
		else if (disappeared())
			return false;
	}

	return true;
}