

#ifndef _WCOLLIDER_H_
#define _WCOLLIDER_H_

#include "Debug.h"

#include <vector>

#include "Collider.h"
#include "AABB.h"

class Game;




class WorldCollider
{
public:
	WorldCollider() {};

	// Manager
	void UpdateBoundingBoxes();
	void HandleCollisions();

	// Add/remove from manager
	void AddCollider(Collider* collider);
	void RemoveCollider(Collider* collider);

	bool EnemiesDead() {
		return enemyCasts.empty() && enemies.empty();
	}

	bool ClearLevel() {
		enemyCasts.clear();
		enemies.clear();
		bonuses.clear();
		playerCasts.clear();
	}

#ifdef DBG_HITBOXES
	void DebugHitboxes();
#endif

private:
	// Colliders
	Collider* character;
	std::vector<Collider*> enemyCasts;
	std::vector<Collider*> playerCasts;
	std::vector<Collider*> bonuses;
	std::vector<Collider*> enemies;

	bool CollisionTest(BoundingBox &c1, BoundingBox &c2);
};


#endif
