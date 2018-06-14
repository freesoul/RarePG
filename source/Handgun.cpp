#include "include/Handgun.h"
#include "include/Game.h"
#include "include/Character.h"
#include "include/Bullet.h"


Handgun::Handgun() : shotLast(0) {
	setTexture(Game::s_game->gfx.txHandgunLeft);
	setOrigin(2, 27);
	shotDelay = BASE_HANDGUN_DELAY;
	SetMouseAction(Input::MouseActionType::LeftIsDown);
};

void Handgun::OnUpdate()
{



}

void Handgun::OnMouseLeftDown()
{
	float elapsed = Game::s_game->timer.getElapsedTime().asSeconds();

	if (elapsed >= (shotLast + shotDelay))
	{
		new Bullet(this);
		shotLast = elapsed;
	}

}
