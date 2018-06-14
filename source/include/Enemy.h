#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Collider.h"
#include "Object.h"
class Lifebar;

class Enemy : public Object, public Collider {
public:
	Enemy(float _m_hp, bool lb = 1);
	~Enemy();
	

	virtual bool Dead() { return GetCurrentHP() <= 0; };
	virtual float GetDamage() { return 0; };
	virtual float GetDamagePerSecond() { return 0; };
	virtual float GetMaxHP() { return m_hp; };
	virtual float GetCurrentHP() { return c_hp; };
	virtual void Hurt(float dmg);
	virtual void OnHurt() {};
	virtual void Die() {};

protected:
	Lifebar* lifebar;
	void HideLifebar();
	float m_hp, c_hp;

private:
	float damage;
	float damage_per_second;
};
#endif