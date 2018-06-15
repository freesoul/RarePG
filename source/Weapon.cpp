#include "include/Weapon.h"
#include "include/Input.h"
#include "include/Game.h"
#include "include/Character.h"
#include "include/Actionable.h"

Weapon::Weapon(bool _right) : right(_right), weapon_mouse_rotation(0),
weapon_mouse_rotation_radians(0){
	SetMouseAction(Input::LeftIsDown);

	if (right)
	{
		fWeaponPosRelative.x = 20;
		fWeaponPosRelative.y = -2;
	}
	else {
		fWeaponPosRelative.x = -15;
		fWeaponPosRelative.y = 3;

	}
}

bool Weapon::Update() {

	Character* character = Game::s_game->character;

	//  Weapon position
	sf::Vector3f pos = character->getWorldPosition();
	pos.x += fWeaponPosRelative.x;
	pos.y += fWeaponPosRelative.y;
	pos.z -= 1;

	setRotation(weapon_mouse_rotation);

	setWorldPosition(pos.x, pos.y, pos.z);

	// Weapon rotation
	weapon_mouse_x = Game::s_game->input.mouse_x - getPosition().x;
	weapon_mouse_y = getPosition().y - Game::s_game->input.mouse_y;
	weapon_mouse_rotation_radians = std::atan2(weapon_mouse_x, weapon_mouse_y);
	weapon_mouse_rotation = weapon_mouse_rotation_radians * (360 / (2 * 3.1419));

	float scale = character->getScale().x;

	if (weapon_mouse_x < 0)
		setScale(sf::Vector2f(-scale, scale));
	else setScale(sf::Vector2f(scale, scale));


	// Custom actions
	OnUpdate();
	return true;
}

Weapon::~Weapon()
{
	UnsetMouseAction(Input::LeftIsDown);
}
