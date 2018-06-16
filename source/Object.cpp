#include "include/Object.h"
#include "include/Game.h"
// #include "include/debug.h"

Object::Object() : bDestroyedOnUpdate(false) {
	Game::s_game->objects.AddObject(this);
};

Object::~Object()
{
	if (!bDestroyedOnUpdate)
		Game::s_game->objects.RemoveObject(this);

#ifdef DBG
	std::printf("Destroyed object\n");
#endif
};
