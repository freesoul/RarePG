#ifndef _H_POLLITO_
#define _H_POLLITO_

#include "AnimatedSprite.h"
#include "Disappear.h"
#include "Shadow.h"
#include "Debug.h"
#include "Drawable3D.h"
#include "Collider.h"
#include "Enemy.h"

#include "Obstacle.h" // Remove this from here. "Pollito" should not be an obstacle.

class Character;

class Pollito : public Enemy, public AnimatedSprite, public Disappear, public Obstacle {
public:
	enum State { Falling, Walking, Jumping, Dying, sDead };
	Pollito(float _m_hp=25);
	virtual ~Pollito(){
#ifdef DBG
		std::printf("Destroyed Mono Small\n");
#endif
	};

	bool Update();

	void Collision();
	float GetDamage();

	void Jump(); // Pollito action

	bool Dead() { return state == sDead; };

	void Die();

private:
	State state;
	sf::Vector3f jump_speed;
	float tLastJump;
	bool guided;
	float speed;
};


#endif
