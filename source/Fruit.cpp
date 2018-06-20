#include "include/Fruit.h"
#include "include/Game.h"
#include "include/Collider.h"
#include "include/Gfx.h"
#include <stdio.h>
#include "include/Constants.h"
#include "include/Shadow.h"

Fruit::Fruit() : Collider(Collider::Bonus) { //, true

	initShadow();
	shadow->setFillColor(sf::Color(0,200,0,100));

	setTexture(Game::s_game->gfx.txFruits);

	setTextureRect(sf::IntRect(50*(std::rand()%4), 50*(std::rand()%4), 50, 50));

	setWorldPosition(std::rand() % (1024 - 50), -200, std::rand() % MAX_Z);

	setOrigin(25, 25);

	shadow->setFillColor(sf::Color(0, 0, 0 , 150));

}

bool Fruit::Update()
{
	if (getWorldPosition().y < MAX_Y)
		moveInWorld(0, 150 * Game::s_game->elapsed, 0);
	else switch(getDisappearStatus()){
		case NotStarted:
			disappear();
			break;
		case Disappeared:
			return false;
		default:
			;
	}
	return true;
}
