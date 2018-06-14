#include "Drawable3D.h"
#include "Game.h"
#include "Shadow.h"

D3D::D3D(bool bShadow)
{
	InitShadow(bShadow);
	Game::s_game->objects.AddD3D(this);
}

void D3D::InitShadow(bool bShadow) {
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
