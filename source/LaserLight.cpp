#include "include/LaserLight.h"
#include "include/Character.h"
#include "include/Weapon.h"
#include "include/Collider.h"
#include "include/Game.h"
#include "include/Gfx.h"
#include <math.h>
#include "include/Laser.h"


float LaserLight::GetDamage(){
	return Game::s_game->elapsed * 25;
}


LaserLight::LaserLight(Weapon* _caster) :
	AnimatedSprite(Game::s_game->gfx.txLaserLight, false, 0.1f),
	Collider(Collider::PlayerCast),
	caster(_caster),
	Disappear(0.4f)
{
	setCustomOrigin();

	AddFrame(0x01, sf::IntRect(0, 669, 20, 710 - 669), 10, 710 - 669);
	AddFrame(0x01, sf::IntRect(20, 531, 20, 710 - 531), 10, 710 - 531);
	AddFrame(0x01, sf::IntRect(40, 362, 20, 710-362), 10, 710 - 362);
	AddFrame(0x01, sf::IntRect(60, 199, 20, 710-199), 10, 710-199);
	AddFrame(0x01, sf::IntRect(80, 0, 20, 710), 10, 710);

	setPosition(500, 600);

	RunSequence(0x01, false);


}

LaserLight::~LaserLight() {
	((Laser*)caster)->laserLight = NULL;
}

bool LaserLight::Update() {

	sf::Vector3f cpos;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		cpos = caster->getWorldPosition();
		setWorldPosition(cpos.x, cpos.y, cpos.z);

		setRotation(caster->getRotation());
	}
	else {
		if (getDisappearStatus() == DisappearStatus::NotStarted)
			disappear();
	}

	return true;
}
