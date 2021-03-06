#ifndef _BULLET_H
#define _BULLET_H_

#include "Sprite.h"
#include "Drawable2D.h"
#include "Object.h"
#include "Collider.h"

class Weapon;

class Bullet : public Collider, public Sprite {
public:
	Bullet(Weapon* caster);
	bool Update();
	~Bullet(){};
	float GetDamage() { return 25; };
	bool DestroyOnCollide() { return true; };

private:
	float x_speed, y_speed, z;
};
#endif
