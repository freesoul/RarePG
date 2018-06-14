#ifndef _HANDGUN_H_
#define _HANDGUN_H_

#include "Weapon.h"
#include "Constants.h"
#include "Sprite.h"
#include "Drawable2D.h"
#include "Object.h"

class Handgun : public Weapon, public Sprite {
public:
	Handgun();
	void OnMouseLeftDown();
	void OnUpdate();
	~Handgun(){};

private:
	float shotDelay;
	float shotLast;

};
#endif
