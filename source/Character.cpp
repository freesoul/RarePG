#include "include/Character.h"
#include "include/Game.h"
#include "include/Constants.h"
#include "include/SpineDrawable.h"
#include "include/Collider.h"
#include "include/Handgun.h"
#include "include/Laser.h"

void Character::Heal(unsigned int amount)
{
	current_hp += amount;
	if (current_hp > max_hp)
		current_hp = current_hp;

	//Game::inst()->interface->SetLifeBallPercent(current_hp / max_hp);
}


void Character::Heal(float p)
{
	float amount = max_hp * p;
	current_hp += amount;
	if (current_hp > max_hp)
		current_hp = current_hp;

	//Game::inst()->interface->SetLifeBallPercent(current_hp / max_hp);
}


void Character::Stun(float time)
{
	AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "stand", true);
	releaseStunTime = Game::inst()->timer.getElapsedTime().asSeconds() + time;
	state = Stunned;
}


void Character::Hurt(float dmg)
{
	if (state != Dead && state != Dying) {
		current_hp -= dmg * (1 / (1 + armor));
		if (current_hp <= 0)
		{
			current_hp = 0;
			Die();
		}
		Game::s_game->gui->UpdateLife(current_hp/max_hp);
	}
};


void Character::Die()
{
	state = Dying;
	AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "die", false);
	SkeletonDrawable::state->tracks[0]->stopAtEnd = true;
	Skeleton_updateWorldTransform(skeleton);
}


Character::Character(CharacterType type) :
	Collider(Collider::Type::Player, false, 16, 42)
{

	SpineLoad("data/Character.atlas", "data/Character.json", 512, 713, "tronco");

	setWorldPosition(SCREEN_WIDTH/2, MAX_Y, 0);

	//objectType = ID_CHARACTER;
	state = Standing;


	switch (type)
	{
	case Girl:
		Skeleton_setSkinByName(SkeletonDrawable::skeleton, "girl");
		break;
	case CharacterType::Guy:
	default:
		Skeleton_setSkinByName(SkeletonDrawable::skeleton, "guy");
		break;
	}

	AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "stand", true);

	Skeleton_updateWorldTransform(skeleton);

	AnimationStateData_setMixByName(SkeletonDrawable::state->data, "stand", "walk", 0.4f);
	AnimationStateData_setMixByName(SkeletonDrawable::state->data, "walk", "stand", 0.4f);

	AnimationStateData_setMixByName(SkeletonDrawable::state->data, "stand", "die", 0.4f);
	AnimationStateData_setMixByName(SkeletonDrawable::state->data, "walk", "die", 0.4f);

	max_hp = 100;
	current_hp = 100;
	armor = 0.25f;

//	tWeapon = wHandgun;
//	weapon = new Handgun();
	tWeapon = wLaser;
	weapon = new Laser();

}

void Character::SetWeapon(WeaponType _weapon)
{
	switch (_weapon)
	{
	case WeaponType::wLaser:
		if (tWeapon != _weapon)
			delete weapon;
		weapon = new Laser();
		break;
	case WeaponType::wHandgun:
	default:
		if (tWeapon != _weapon)
			delete weapon;
		weapon = new Handgun();
		break;

	}


}

bool Character::Update()
{
	Game* g = Game::inst();

	bool nowMoving=false;

	//// Status

	switch (state)
	{
	case Dead:
		break;
	case Dying:
	{
				  if (spAnimationState_getCurrent(SkeletonDrawable::state, 0)->finished)
				  {
					  state = Dead;
				  }
	}
		break;

	case Stunned:
	{
					if (Game::inst()->timer.getElapsedTime().asSeconds() >= releaseStunTime)
					{
						state = Standing;
					}

	}
		break;

	case Standing:
	case Moving:
	default:
	{
			   // set weapon rotation
		//	   g->weapon->leftWeaponHolder->bone->rotation = -g->input.weapon_mouse_rotation;
		//	   g->weapon->rightWeaponHolder->bone->rotation = -g->input.weapon_mouse_rotation;

			   // Check for movement
			   float x_move, z_move;
			   x_move = 0;
			   z_move = 0;

			   // X Axis
			   if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
				   x_move -= g->elapsed*CHAR_SPEED_BASE_X;

			   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
				   x_move += g->elapsed*CHAR_SPEED_BASE_X;

			   // Z Axis
			   if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					if (getWorldPosition().z < MAX_Z)
						z_move += g->elapsed*CHAR_SPEED_BASE_Z;

					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
				   if (getWorldPosition().z > 0)
					   z_move -= g->elapsed*CHAR_SPEED_BASE_Z;

			   if (z_move != 0 || x_move != 0)
				   nowMoving = true;

			   // Split speed if moving in two axis.
			   if (x_move != 0 && z_move != 0)
			   {
				   x_move = x_move * 0.75f;
				   z_move = z_move / 2;
			   }

			   // Move
			   moveInWorld(x_move, 0, z_move);

			   //
			   if (getWorldPosition().x < 0)
				   setWorldPosition(1023, getWorldPosition().y, getWorldPosition().z);

			   if (getWorldPosition().x > 1024)
				   setWorldPosition(1, getWorldPosition().y, getWorldPosition().z);

			   // Change animation walk <-> stand
			   if (state == Standing && nowMoving)
				   AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "walk", true);
			   if (state == Moving && !nowMoving)
				   AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "stand", true);

			   if (nowMoving)
				   state = Moving;
			   else
				   state = Standing;
	}
		break;

	}


	// /// Sounds
	// if (nowMoving)
	// {
	// 	if (Game::s_game->audio.soundWalk.getStatus() != sf::Sound::Playing)
	// 		Game::s_game->audio.soundWalk.play();
	// }
	// else if (!nowMoving)
	// {
	// 	Game::s_game->audio.soundWalk.stop();
	// }


	return true;

}
