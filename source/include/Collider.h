#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "ObjectManager.h"
#include "Drawable3D.h"
#include "Object.h"
#include "AABB.h"


class Game;


class Collider : virtual public D3D, public Object {
public:

	BoundingBox boundingBox; // The default one

	std::vector<BoundingBox> boundingBoxes; // If allocated custom boundingBoxes
																					// Not used by the moment

	enum Type { Enemy=1, EnemyCast, Bonus, Player, PlayerCast };

	Collider(
		Collider::Type _type,
		/*bool bShadow=false,*/
		float _fixX = 0,
		float _fixY = 0,
		float _fixW = 0.1,
		float _fixH = 0.1f
	);

	virtual ~Collider();

	virtual void Collision() {};

	virtual float GetDamage() { return 0; };
	virtual float GetDamagePerSecond() { return 0.0f; };
	virtual void Hurt(float dmg) { return; };
	virtual float GetCurrentHP() { return 1; };
	virtual bool Dead() { return false; };

	virtual bool DestroyOnColide() { return false; };

	void DestroyByCollisionFlag() { destroyedByCollision = true;  };

	void UpdateBoundingBox();

	Type type;

protected:
	// Fix BB relative to holder.
	sf::Transform fixTransform;

private:
	bool destroyedByCollision;

};


#endif
