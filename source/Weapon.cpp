#include "include/Weapon.h"
#include "include/Input.h"
#include "include/Game.h"
#include "include/Character.h"
#include "include/Actionable.h"

Weapon::Weapon(bool _right) : right(_right), weapon_mouse_rotation(0),
weapon_mouse_rotation_radians(0){
	SetMouseAction(Input::MouseActionType::LeftIsDown);

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

	//  Weapon position
	sf::Vector3f pos = Game::s_game->character->GetWorldPosition();
	pos.x += fWeaponPosRelative.x;
	pos.y += fWeaponPosRelative.y;
	pos.z -= 1;

	SetRotation(weapon_mouse_rotation);

	SetWorldPosition(pos.x, pos.y, pos.z);

	// Weapon rotation
	weapon_mouse_x = Game::s_game->input.mouse_x - GetPosition().x;
	weapon_mouse_y = GetPosition().y - Game::s_game->input.mouse_y;
	weapon_mouse_rotation_radians = std::atan2(weapon_mouse_x, weapon_mouse_y);
	weapon_mouse_rotation = weapon_mouse_rotation_radians * (360 / (2 * 3.1419));

	if (weapon_mouse_x < 0)
		SetScale(sf::Vector2f(-1, 1));
	else SetScale(sf::Vector2f(1, 1));


	// Custom actions
	OnUpdate();
	return true;
}

Weapon::~Weapon()
{
	UnsetMouseAction(Input::MouseActionType::LeftIsDown);
}
