#include "include/Object.h"
#include "include/Game.h"
// #include "include/debug.h"

#include <iostream>

Object::Object() : bDestroyedOnUpdate(false) {
	Game::s_game->objects.AddObject(this);
	// std::cout<<"object created\n";
};

Object::~Object()
{
	// std::cout<<"object deleted\n";
	if (!bDestroyedOnUpdate)
		Game::s_game->objects.RemoveObject(this);

#ifdef DBG
	std::printf("Destroyed object\n");
#endif
};
