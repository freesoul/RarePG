#ifndef _WEAPON_H_
#define _WEAPON_H_

#include "Object.h"
#include "Drawable3D.h"
#include "Actionable.h"

class Weapon : public Object, public D3D, public Actionable {
public:
	Weapon(bool _right = true);
	virtual ~Weapon();

	bool Update(); 

	// Derived class override
	virtual void OnUpdate() { };
	void OnMouseLeftDown() { };


	float weapon_mouse_rotation_radians;

protected:
	float weapon_mouse_x;
	float weapon_mouse_y;
	float weapon_mouse_rotation;


private:
	sf::Vector2f fWeaponPosRelative;
	bool right;

};
#endif