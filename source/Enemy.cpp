#include "include/Enemy.h"
#include "include/Lifebar.h"
#include "include/Shadow.h"

void Enemy::Hurt(float dmg) {
	if (dmg >= c_hp)
	{
		Die();
		c_hp = 0;
	}
	else c_hp -= dmg;

	OnHurt();

	if (lifebar!=0)
		lifebar->UpdateLifeBar();
};


Enemy::Enemy(float _m_hp, bool lb) : Collider(Collider::Enemy), m_hp(_m_hp), c_hp(_m_hp), damage(0), damage_per_second(0) {
	lifebar = new Lifebar(this);
	initShadow();
	shadow->setFillColor(sf::Color(255,0,0,100));
};

void Enemy::HideLifebar()
{
	if (lifebar!=0)
		delete lifebar;
	lifebar = 0;

}

Enemy::~Enemy()
{
	//lifebar->bDestroyedOnUpdate = false; // ?????
	if(lifebar!=0)
		delete lifebar;
};
