#include "include/Bullet.h"
#include "include/Character.h"
#include "include/Weapon.h"
#include "include/Collider.h"
#include "include/Game.h"
#include "include/Gfx.h"
#include <math.h>

Bullet::Bullet(Weapon* caster) : Collider(Collider::PlayerCast)
{
	setTexture(Game::s_game->gfx.txBullet);
	sf::Vector3f owner_pos = caster->getWorldPosition();
	setWorldPosition(owner_pos.x, owner_pos.y, owner_pos.z - 1); // For painting order.
	x_speed = BULLET_SPEED * std::sin(caster->weapon_mouse_rotation_radians);
	y_speed = -BULLET_SPEED * std::cos(caster->weapon_mouse_rotation_radians);
	setRotation(caster->getRotation());
}

bool Bullet::Update() {
	moveInWorld(x_speed*Game::s_game->elapsed,
		y_speed*Game::s_game->elapsed,
		0);

	if (!sf::FloatRect(-100, -100, 1224, 968).intersects(getGlobalBounds()))
		return false;

	return true;
}
