#include "Drawable3D.h"
#include "Game.h"
#include "Shadow.h"

D3D::D3D(bool bShadow)
{
	initShadow(bShadow);
	Game::s_game->objects.AddD3D(this);
	is3d = true;
}

void D3D::initShadow(bool bShadow) {
	if (bShadow)
		shadow = new Shadow(this);
	else shadow = 0;

}

D3D::~D3D()
{
	if (shadow != 0)
		delete shadow;

	Game::s_game->objects.RemoveD3D(this);
}
