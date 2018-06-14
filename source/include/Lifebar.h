#ifndef _LIFEBAR_H_
#define _LIFEBAR_H_

#include "Object.h"
#include "Drawable2D.h"
#include "Sprite.h"
#include "Constants.h"

class Enemy;

class Lifebar : public D2D, public Sprite, public Object {
public:
	Lifebar(Enemy* e, float width=BASE_LIFEBAR_WIDTH);
	~Lifebar(){};
	bool Update();
	void UpdateLifeBar();


private:
	Enemy* holder;
	float width;
};
#endif