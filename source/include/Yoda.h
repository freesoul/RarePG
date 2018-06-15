#ifndef _YODA_H_
#define _YODA_H

#include "SpineDrawable.h"
#include "Enemy.h"
#include "Drawable3D.h"

class Yoda : public SpineDrawable, public Enemy {
public:

	enum State {Appearing, Walking, Attacking, Dying, RIP } state;

	Yoda(float _m_hp=100);
	~Yoda();

	bool Update();

	void Collision();
	void Die();
	bool Dead();
	void OnHurt() {
		if (state != RIP && state != Dying)
			if (c_hp <= 0)
				Die();
	};
};

#endif
