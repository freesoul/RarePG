#include "include/ObjectManager.h"
#include "include/Game.h"
#include "include/Collider.h"
#include "include/AABB.h"
#include "include/Debug.h"
#include "include/Character.h"

void WorldCollider::UpdateBoundingBoxes()
{
	if (character)
		character->UpdateBoundingBox();

	std::vector<Collider*>::iterator it;

	for (it = enemies.begin(); it != enemies.end(); it++)
		(*it)->UpdateBoundingBox();

	for (it = enemyCasts.begin(); it != enemyCasts.end(); it++)
		(*it)->UpdateBoundingBox();

	for (it = bonuses.begin(); it != bonuses.end(); it++)
		(*it)->UpdateBoundingBox();

	for (it = playerCasts.begin(); it != playerCasts.end(); it++)
		(*it)->UpdateBoundingBox();
}

void WorldCollider::RemoveCollider(Collider* c)
{
	std::vector<Collider*>::iterator it;
	switch (c->type)
	{
	case Collider::Player:
		character = 0;
		break;
	case Collider::Bonus:
		for (it = bonuses.begin(); it != bonuses.end(); it++)
		if ((*it) == c)
		{
			bonuses.erase(it);
			return;
		}
		break;
	case Collider::Enemy:
		for (it = enemies.begin(); it != enemies.end(); it++)
		if ((*it) == c)
		{
			enemies.erase(it);
			return;
		}
		break;
	case Collider::EnemyCast:
		for (it = enemyCasts.begin(); it != enemyCasts.end(); it++)
		if ((*it) == c)
		{
			enemyCasts.erase(it);
			return;
		}
		break;
	case Collider::PlayerCast:
	default:
		for (it = playerCasts.begin(); it != playerCasts.end(); it++)
		if ((*it) == c)
		{
			playerCasts.erase(it);
			return;
		}
		break;
	}
}


void WorldCollider::AddCollider(Collider* c)
{
	switch (c->type)
	{
	case Collider::Player:
		character = c;
		break;
	case Collider::Bonus:
		bonuses.push_back(c);
		break;
	case Collider::Enemy:
		enemies.push_back(c);
		break;
	case Collider::EnemyCast:
		enemyCasts.push_back(c);
		break;
	case Collider::PlayerCast:
	default:
		playerCasts.push_back(c);
		break;
	}
}

bool WorldCollider::CollisionTest(BoundingBox &c1,  BoundingBox&c2)
{
	return AABB::collision(c1, c2);
}



void WorldCollider::HandleCollisions() {

	std::vector<Collider*>::iterator it;
	std::vector<Collider*>::iterator it2;

	// Enemy cast <----> Character
	for (it = enemyCasts.begin(); it != enemyCasts.end();)
	if (CollisionTest((*it)->boundingBox, character->boundingBox))
	{
		(*it)->DestroyByCollisionFlag();
		delete *it;
		it = enemyCasts.erase(it);
	}
	else ++it;

	// Bonus <----> Character
	for (it = bonuses.begin(); it != bonuses.end();)
	if (CollisionTest((*it)->boundingBox, character->boundingBox))
	{
		(*it)->Collision();
		(*it)->DestroyByCollisionFlag();
		delete *it;
		it = bonuses.erase(it);
	}
	else ++it;


	// Enemy <----> Character
	for (it = enemies.begin(); it != enemies.end(); it++)
	if (CollisionTest((*it)->boundingBox, character->boundingBox))
	{
		(*it)->Collision();
		character->Collision();
		//character->Hurt((*it)->GetDamage());
		//character->Hurt((*it)->GetDamagePerSecond() * Game::s_game->elapsed);
	}

	// Enemy <----> Character Cast
	for (it = enemies.begin(); it != enemies.end();)
	{
		for (it2 = playerCasts.begin(); it2 != playerCasts.end();)
		{
			//if (!(*it)->Dead()) //Why with this bullet keep being destroyed?
			if (CollisionTest((*it)->boundingBox, (*it2)->boundingBox))
			{
				// Hurt enemy
				(*it)->Hurt((*it2)->GetDamage());

				// Delete Ammo
				if ((*it2)->DestroyOnColide())
				{
					(*it2)->DestroyByCollisionFlag(); // So destructor does not remove from list
					delete *it2;
					it2 = playerCasts.erase(it2);
				}
				else it2++;

			} else it2++;
			//else it2++;
		}

		/// Destroy enemy if dead
		if ((*it)->Dead())
		{
			(*it)->DestroyByCollisionFlag();
			delete *it;
			it = enemies.erase(it);
		}	else it++;
	}


}

#ifdef DBG_HITBOXES
void WorldCollider::DebugHitboxes() {
	sf::RectangleShape shape;

	// Enemy casts
	std::vector<Collider*>::iterator it;
	for (it = enemyCasts.begin(); it != enemyCasts.end(); it++)
	{
		shape.setSize(sf::Vector2f((*it)->boundingBox.localBounds.width, (*it)->boundingBox.localBounds.height));
		Game::s_game->renderer.draw(shape, (*it)->boundingBox.transform);
	}
	//
	// // Enemies
	// for (it = enemies.begin(); it != enemies.end(); it++)
	// {
	// 	shape.setSize(sf::Vector2f((*it)->boundingBox.localBounds.width, (*it)->boundingBox.localBounds.height));
	// 	Game::s_game->renderer.draw(shape, (*it)->boundingBox.transform);
	// }
	//
	//
	//
	// // Character
	// shape.setSize(sf::Vector2f(Game::s_game->character->boundingBox.localBounds.width, Game::s_game->character->boundingBox.localBounds.height));
	// Game::s_game->renderer.draw(shape, Game::s_game->character->boundingBox.transform);
}
#endif
