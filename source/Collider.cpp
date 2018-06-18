#include "include/Game.h"
#include "include/Collider.h"


Collider::Collider(Type _type, float _fixX, float _fixY, float _fixW , float _fixH) :
		type(_type) {
	Game::s_game->colliders.AddCollider(this); // Depending on type.
	destroyedByCollision = false;

	sf::Transformable ft;
	ft.setOrigin(_fixX, _fixY);
	ft.scale(1 - _fixW, 1 - _fixH);

	fixTransform = ft.getTransform();

	// UpdateBoundingBox(); // <---- ERROR: Still virtual while creating object
};


Collider::~Collider()
{
	if (!destroyedByCollision)
		Game::s_game->colliders.RemoveCollider(this);
};


void Collider::UpdateBoundingBox(){
	boundingBox.localBounds = getLocalBounds(); // Move from here. WARNING: IN CONSTRUCTOR YOU CAN'T CALL VIRTUAL FX
	boundingBox.transform = getTransform()*fixTransform;
};
