#include "MonoSmall.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "Constants.h"
#include "Character.h"
#include "Game.h"


float MonoSmall::GetDamage() {
	return MONOSMALL_DAMAGE;
};


void MonoSmall::Collision()
{
	float z_distance = Game::inst()->character->getWorldPosition().z - getWorldPosition().z;

	if (state == Alive && std::abs(z_distance) < 25)
	{
		Game::s_game->character->Hurt(MONOSMALL_DAMAGE);
		//Die();
	}
}

MonoSmall::MonoSmall(float _m_hp) : AnimatedSprite(Game::s_game->gfx.txMonoSmall), Enemy(_m_hp), state(Alive)
{
	//SetTexture(s_game->resourceManager.txPulpo);
	setOrigin(25, 35);

	AddFrame(ID_SEQUENCE_NORMAL, sf::IntRect(0, 0, 50, 77));
	AddFrame(ID_SEQUENCE_NORMAL, sf::IntRect(50, 0, 50, 77));
	AddFrame(ID_SEQUENCE_NORMAL, sf::IntRect(110, 0, 50, 77));

	// Set initial sequence and time to zero.
	RunSequence(ID_SEQUENCE_NORMAL);

	// Set position
	setWorldPosition(std::rand() % (1024 - 100) + 50, -200, std::rand() % PROFUNDITY_SIZE);

	max_hp = 25;
	hp = max_hp;
	guided = false;
	speed = 100;

}

void MonoSmall::Die()
{
	if (state == Alive){
		state = Dying;
		HideLifebar();
		disappear();
	}
}


bool MonoSmall::Update()
{
	Game* g = Game::inst();

	switch (state)
	{
	case Alive:
		{
			if (getWorldPosition().y < MAX_Y)
				moveInWorld(0, 150 * Game::s_game->elapsed, 0);
			else {
				Die();
			}
		} break;
	case Dying: {
			if (disappeared())
			state = Dead;
	
		} break;
	case Dead: {
		   return false;
		}break;

	}



	//lifebar->update();
	return true;
}