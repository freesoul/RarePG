#pragma warning( warning_level : 0 )

#include "include/Game.h"

Game* Game::s_game = 0;

int main()
{
	if(Game::inst()->Load())
		Game::inst()->Run();

	return 0;
}
