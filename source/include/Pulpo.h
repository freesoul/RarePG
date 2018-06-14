#ifndef _H_PULPO_
#define _H_PULPO_

#include "AnimatedSprite.h"
#include "Disappear.h"
#include "Shadow.h"
#include "Debug.h"
#include "Drawable3D.h"
#include "Collider.h"
#include "Enemy.h"

class Character;

class Pulpo : public Enemy, public AnimatedSprite, public Disappear {
public:
	enum State { Falling, Attacking, Walking, Dying } state;
	Pulpo(float _m_hp=100);
	virtual ~Pulpo(){
#ifdef DBG
		std::printf("Destroyed Pulpo\n");
#endif
	};

	bool Update();

	void Collision();
	float GetDamagePerSecond();

	void Die();

private:
	bool guided;
	float speed;
	float hp, max_hp;

};


#endif
