#ifndef _H_PULPO_
#define _H_PULPO_

#include "AnimatedSprite.h"
#include "Disappear.h"
#include "Shadow.h"
#include "Debug.h"
#include "Drawable3D.h"
#include "Collider.h"
#include "Enemy.h"
#include "Obstacle.h"

class Character;

class Pulpo : public Enemy, public AnimatedSprite, public Disappear, public Obstacle {
public:
	enum State { Falling, Attacking, Walking, Dying, sDead } state;
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
	bool Dead() { return state == sDead; };

private:
	bool guided;
	float speed;
	float hp, max_hp;

};


#endif
