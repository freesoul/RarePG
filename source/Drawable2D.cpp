#include "include/Drawable2D.h"
#include "include/Game.h"

D2D::D2D(bool _bGui) : bGui(_bGui)
{
		Game::s_game->objects.AddD2D(this, bGui);
}

D2D::~D2D()
{
	Game::s_game->objects.RemoveD2D(this, bGui);

}
