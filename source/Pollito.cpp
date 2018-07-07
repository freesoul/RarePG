#include "Pollito.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "Constants.h"
#include "Character.h"
#include "Game.h"


float Pollito::GetDamage() {
	return 20;
};


void Pollito::Collision()
{
	if (state == Walking)
	{
		Game::s_game->character->Hurt(25 * Game::s_game->elapsed);
	}
}

Pollito::Pollito(float _m_hp) :
			AnimatedSprite(Game::s_game->gfx.getGfx("Pollitos")),
			 Enemy(_m_hp),
			 state(Falling),
			 tLastJump(0)
{
	// initShadow();//true);

	//SetTexture(s_game->resourceManager.txPulpo);
	setOrigin(35, 32);

	AddFrame(ID_SEQUENCE_NORMAL, sf::IntRect(0, 0, 60, 41));
	AddFrame(ID_SEQUENCE_NORMAL, sf::IntRect(60, 0, 60, 41));
	AddFrame(ID_SEQUENCE_NORMAL, sf::IntRect(120, 0, 60, 41));

	// Set initial sequence and time to zero.
	RunSequence(ID_SEQUENCE_NORMAL);

	// Set position
	setWorldPosition(std::rand() % (1024 - 100) + 50, -200, std::rand() % PROFUNDITY_SIZE);

	m_hp = 25;
	c_hp = m_hp;
	guided = false;
	speed = 400;

}

void Pollito::Die()
{
	if (state == Falling || state == Walking){
		state = Dying;
		HideLifebar();
		shadow->ShadowOff();
		setObstacleOff();
		disappear();
	}
}

void Pollito::Jump() {
	sf::Vector3f my_pos = getWorldPosition();
	sf::Vector3f char_pos = Game::s_game->character->getWorldPosition();

	float x_direction = (my_pos.x > char_pos.x) ? -1.f : 1.f;
	float z_direction = (my_pos.z > char_pos.z) ? -1.f : 1.f;
	jump_speed.y = -150;
	jump_speed.x = 150 * x_direction;
	jump_speed.z = 50 * z_direction;
	state = Jumping;
}


bool Pollito::Update()
{
	Game* g = Game::inst();
	sf::Vector3f my_pos = getWorldPosition();
	sf::Vector3f char_pos = g->character->getWorldPosition();

	switch (state)
	{
	case Falling:
		{
			if (getWorldPosition().y < MAX_Y)
				moveInWorld(0, speed * Game::s_game->elapsed, 0);
			else {
				state = Walking;
				tLastJump = g->timer.getElapsedTime().asSeconds() + 1 + std::rand() % 4;
				shadow->ShadowOff();
			}
		} break;
	case Jumping:
	{
		jump_speed.y += g->elapsed * 200;
		moveInWorld(jump_speed.x*g->elapsed, jump_speed.y*g->elapsed, jump_speed.z*g->elapsed);

		if (getWorldPosition().y>=MAX_Y)
		{
			tLastJump = g->timer.getElapsedTime().asSeconds() + 1 + std::rand() % 4;
			state = Walking;
			shadow->ShadowOff();
		}
		break;
	}
	case Walking:
		{
					if (my_pos.x < char_pos.x)
						moveInWorld(MONO_WALK_SPEED*g->elapsed, 0, 0);
					else if (my_pos.x > char_pos.x)
						moveInWorld(-MONO_WALK_SPEED*g->elapsed, 0, 0);

					if (my_pos.z < (char_pos.z - 1))
						moveInWorld(0, 0, MONO_WALK_SPEED*g->elapsed);
					else if (my_pos.z >(char_pos.z + 1))
						moveInWorld(0, 0, -MONO_WALK_SPEED*g->elapsed);


					// Jump logic
					if (g->timer.getElapsedTime().asSeconds() > tLastJump)
					{
						Jump();
						shadow->ShadowOn();
					}
		}
		break;
	case Dying: {
			if (disappeared())
			state = sDead;

		} break;
	case sDead: {
		   return false;
		}break;

	}



	//lifebar->update();
	return true;
}
