#ifndef _LASER_H_
#define _LASER_H_

#include "Weapon.h"
#include "Constants.h"
#include "Sprite.h"
#include "Drawable2D.h"
#include "Object.h"

class LaserLight;

class Laser : public Weapon, public D2D, public Sprite {
public:
	Laser();
	void OnMouseLeftDown();
	void OnUpdate();
	~Laser(){};
	LaserLight* laserLight;

private:



};
#endif