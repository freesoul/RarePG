#ifndef _FRUIT_H_
#define _FRUIT_H_

#include "Collider.h"
#include "Sprite.h"
#include "Object.h"
#include "Drawable3D.h"
#include "Disappear.h"

class Fruit : public Collider, public Sprite, public Disappear {
public:

	Fruit();
	bool Update();

private:

};
#endif
