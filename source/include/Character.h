#ifndef _H_CHARACTER_
#define _H_CHARACTER_

#include "Collider.h"
#include "SpineDrawable.h"
#include "Object.h"
#include "Shadow.h"


class Weapon;


class Character : public Collider, public SpineDrawable {

//class Character : public Collider, public SpineDrawable, virtual public D3D, public Object {
public:
	enum State { Moving, Standing, Dying, Stunned, Dead } state;
	enum CharacterType { Guy, Girl };
	enum WeaponType { wHandgun, wDoubleHandgun, wLaser, wDoubleLaser } tWeapon;

	bool Update();

	Character(CharacterType type);

	void SetWeapon(WeaponType _weapon);

	void Heal(unsigned int amount);
	void Heal(float p);
	void Hurt(float dmg);
	void Die();
	bool IsDead() { return state==Dead ? true : false; };
	void Stun(float time);

	float hp_regen;
	float max_hp;
	float current_hp;
	float armor;

	Weapon* weapon;

private:

	float releaseStunTime;

};

#endif
