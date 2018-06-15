#include "include/Yoda.h"
#include "include/Constants.h"
#include "include/Lifebar.h"
#include "include/Game.h"
#include "include/Character.h"
#include "include/SpineDrawable.h"
#include "include/AABB.h"


#include <iostream>

void Yoda::Die()
{
	if (state != Dying)
	{
		AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "Esconderse", false);
		state = Dying;
	}
}

bool Yoda::Dead()
{
	return state==RIP;
}

void Yoda::Collision()
{

	// allow only to be hurted when they are walking or Attacking
	// (for some reason, state==Dying || state==RIP is buggy)
	if (state!=Walking && state!=Attacking) return;

	sf::Vector3f distance_vector = getWorldPosition();
	distance_vector -= Game::inst()->character->getWorldPosition();

	float distance = sqrt(distance_vector.x*distance_vector.x+distance_vector.y*distance_vector.y+distance_vector.z*distance_vector.z);

	if (state==Walking && distance < 80)
	{
			spTrackEntry* attackTrack = AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "rotateattack", false);
			state = Attacking;
	}
}

bool Yoda::Update()
{
	Game* g = Game::inst();
	sf::Vector3f my_pos = getWorldPosition();
	sf::Vector3f char_pos = g->character->getWorldPosition();



	switch (state)
	{

	case State::Appearing:
		if (AnimationState_getCurrent(SkeletonDrawable::state, 0)->finished)
		{
			AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "walk", true);
			state = Walking;
		}
		break;

	case Walking:
	{

					if (my_pos.x < char_pos.x)
					{
						skeleton->flipX = false;
						moveInWorld(MONO_WALK_SPEED*g->elapsed, 0, 0);
					}
					else if (my_pos.x > char_pos.x)
					{
						skeleton->flipX = true;
						moveInWorld(-MONO_WALK_SPEED*g->elapsed, 0, 0);
					}

					// if (my_pos.x < char_pos.x)
					// 	moveInWorld(MONO_WALK_SPEED*g->elapsed, 0, 0);
					// else if (my_pos.x > char_pos.x)
					// 	moveInWorld(-MONO_WALK_SPEED*g->elapsed, 0, 0);

					if (my_pos.z < (char_pos.z- 1))
						moveInWorld(0, 0, MONO_WALK_SPEED*g->elapsed);
					else if (my_pos.z >(char_pos.z + 1))
						moveInWorld(0, 0, -MONO_WALK_SPEED*g->elapsed);

	} break;

	case Attacking:
	{
					  if (spAnimationState_getCurrent(SkeletonDrawable::state, 0)->finished)
					  {
						  if (AABB::collision(boundingBox, g->character->boundingBox))
						  {
							  g->character->Hurt(20);
						  }
						  AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "walk", true);
						  state = Walking;
					  }

	} break;

	case Dying:
	{
				  if (spAnimationState_getCurrent(SkeletonDrawable::state, 0)->finished)
				  {
					  state = RIP;
				  }break;
	}
	default:
		break;
	};

		return true;


	//UpdateDrawable();
	//TransformHitBox();
	//lifebar->update();
}

/*void Yoda::TransformHitBox()
{
	SkeletonBounds_update(bounds, sdYoda->skeleton, true);

	float width = bounds->maxX - bounds->minX;
	float height = bounds->maxY - bounds->minY;
	hitbox.setTextureRect(sf::IntRect(0, 0, width, height));
	hitbox.setOrigin(width / 2, height / 2);
	hitbox.setPosition(bounds->minX + width / 2, bounds->minY + height / 2);
}*/

Yoda::~Yoda()
{
	//spSkeletonBounds_dispose(bounds);
	//delete sdYoda;
}

Yoda::Yoda(float _m_hp) : Enemy(_m_hp)
{

	SpineLoad("data/yoda.atlas", "data/yoda.json", 300, 300, "tronco", 0.25f);
	setWorldPosition(std::rand() % 924, MAX_Y, std::rand()%MAX_Z);

	//bounds = SkeletonBounds_create();
	//SkeletonBounds_update(bounds, sdYoda->skeleton, true);

	AnimationState_setAnimationByName(SkeletonDrawable::state, 0, "aparecer", false);

	AnimationStateData_setMixByName(SkeletonDrawable::state->data, "rotateattack", "walk", 0.2f);


	Skeleton_updateWorldTransform(skeleton);

	state = Appearing;


	//SetShadow(true);

	//lifebar = new Lifebar(max_hp, 80, -130, &sdYoda->skeleton->x, &sdYoda->skeleton->y);
}
