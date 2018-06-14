#ifndef _LaserLight_H
#define _LaserLight_H_

#include "AnimatedSprite.h"
#include "Drawable2D.h"
#include "Object.h"
#include "Collider.h"
#include "Disappear.h"

class Weapon;

class LaserLight : public Object, public Collider, virtual public D3D, public AnimatedSprite, public Disappear {
public:
	LaserLight(Weapon* _caster);
	bool Update();
	~LaserLight();
	float GetDamage() { return 25; };
	bool DestroyOnColide() { return false; };

private:
	Weapon* caster;

};
#endif