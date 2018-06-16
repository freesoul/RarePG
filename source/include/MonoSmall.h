#ifndef _H_MONOSMALL_
#define _H_MONOSMALL_

#include "AnimatedSprite.h"
#include "Disappear.h"
#include "Shadow.h"
#include "Debug.h"
#include "Drawable3D.h"
#include "Collider.h"
#include "Enemy.h"

class Character;

class MonoSmall : public Enemy, public AnimatedSprite, public Disappear {
public:
	enum State { Alive, Dying, Dead };
	MonoSmall(float _m_hp=MONOSMALL_HP);
	virtual ~MonoSmall(){
#ifdef DBG
		std::printf("Destroyed Mono Small\n");
#endif
	};

	bool Update();

	void Collision();
	float GetDamage();

	void Die();

private:
	State state;
	bool guided;
	float speed;
	float hp, max_hp;

};


#endif
