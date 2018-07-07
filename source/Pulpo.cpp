#include "Pulpo.h"
#include "Collider.h"
#include "AnimatedSprite.h"
#include "Constants.h"
#include "Character.h"
#include "Game.h"


float Pulpo::GetDamagePerSecond() {
	return PULPO_DPS;
};


void Pulpo::Collision()
{

	if (state == Walking || state == Falling)
	{
		if (shadow->ShadowIsOn())
			shadow->ShadowOff();

		state = Attacking;

		RunSequence(ID_SEQUENCE_PULPO_CATCHINGHEAD, false);
		frameTime = PULPO_STUNTIME / GetFrameNumber(); // Calculate time animating the hurt

		sf::Vector3f newpos = Game::s_game->character->getWorldPosition();
		newpos.y -= 43;
		newpos.z -= 1;
		setWorldPosition(newpos.x, newpos.y, newpos.z);

		Game::s_game->character->Stun(PULPO_STUNTIME);

	}
}

Pulpo::Pulpo(float _m_hp) : AnimatedSprite(Game::s_game->gfx.getGfx("Pulpo")), Enemy(_m_hp)
{
	//SetTexture(s_game->resourceManager.txPulpo);
	setOrigin(50, 40);

	AddFrame(ID_SEQUENCE_PULPO_NORMAL, sf::IntRect(0, 0, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_NORMAL, sf::IntRect(100, 0, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_NORMAL, sf::IntRect(200, 0, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_NORMAL, sf::IntRect(300, 0, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_NORMAL, sf::IntRect(400, 0, 100, 80));

	AddFrame(ID_SEQUENCE_PULPO_CATCHINGHEAD, sf::IntRect(0, 80, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_CATCHINGHEAD, sf::IntRect(100, 80, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_CATCHINGHEAD, sf::IntRect(200, 80, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_CATCHINGHEAD, sf::IntRect(300, 80, 100, 80));
	AddFrame(ID_SEQUENCE_PULPO_CATCHINGHEAD, sf::IntRect(400, 80, 100, 80));

	// Set initial sequence and time to zero.
	RunSequence(ID_SEQUENCE_PULPO_NORMAL);

	// Set position
	setWorldPosition(std::rand() % (1024 - 100) + 50, -200, std::rand() % PROFUNDITY_SIZE);

	max_hp = 25;
	hp = max_hp;
	guided = false;
	speed = 100;

	state = Falling;

}

void Pulpo::Die()
{
	if (state != Dying && state != sDead) {
		HideLifebar(); // anyway hes dead (?)
		shadow->ShadowOff();
		disappear();
		setObstacleOff();
		state = Dying;
	}
}


bool Pulpo::Update()
{
	Game* g = Game::inst();

	switch (state)
	{
	case Falling:
		if (getWorldPosition().y < MAX_Y)
			moveInWorld(0, Game::inst()->elapsed*PULPO_Y_SPEED, 0);
		else
		{
			state = Walking;
			shadow->ShadowOff();
		}
		break;

	case Walking:
	{
					sf::Vector3f pos = getWorldPosition();
					sf::Vector3f c_pos = g->character->getWorldPosition();

					float x_speed = PULPO_WALK_SPEED;
					float y_speed = PULPO_WALK_SPEED;
					float z_speed = PULPO_WALK_SPEED;

					// X

					if (std::abs(pos.x - c_pos.x) < 5)
						x_speed = 0;
					else if(pos.x > c_pos.x)
						x_speed *= -1;


					// Y
					if (std::abs(pos.y-c_pos.y)<5)
						y_speed = 0;
					else if (pos.y > c_pos.y)
						y_speed *= -1;


					// Z
					if (std::abs(pos.z - c_pos.z)<5)
						z_speed = 0;
					else if (pos.z > c_pos.z)
						z_speed *= -1;

					moveInWorld(x_speed*Game::s_game->elapsed,
								y_speed*Game::s_game->elapsed,
								z_speed*Game::s_game->elapsed);
	}

		break;

	case Attacking:
	{
					  if (AnimationPaused())
					  {
						  Die();
					  }
	}
		break;

	case Dying:
	{
				  if (disappeared())
						state = sDead;
	} break;

	case sDead:
		return false;

	default:
		break;
	}

	//lifebar->update();
	return true;
}
