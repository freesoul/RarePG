#include "include/Laser.h"
#include "include/Game.h"
#include "include/Character.h"
//#include "Bullet.h"
#include "include/LaserLight.h"


Laser::Laser() : laserLight(NULL)  {
	setTexture(Game::s_game->gfx.getGfx("LaserWeapon"));
	setOrigin(15, 15);
	SetMouseAction(Input::MouseActionType::LeftIsDown);
};

void Laser::OnUpdate()
{
	// if (laserLight != NULL)
	// {
	// 	if (laserLight->disappeared())
	// 		delete laserLight;
	// }
}

void Laser::OnMouseLeftDown()
{
	if (!laserLight)
		laserLight = new LaserLight(this);
}
