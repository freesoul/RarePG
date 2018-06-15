#ifndef _H_PALOMITAS_
#define _H_PALOMITAS_

#include "Drawable2D.h"
#include "AnimatedSprite.h"
#include "DUO.h"

class Palomita : public AnimatedSprite, public DUO {
public:
	Palomita();
	void RandomizeDirection();
	bool DeltaUpdate(float elapsed);
	~Palomita(){};
private:
	float x_speed;
	static float direction;
};

#endif
