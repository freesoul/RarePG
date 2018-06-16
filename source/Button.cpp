#include "include/Button.h"
#include "include/Game.h"
#include "include/Input.h"

void Button::OnMouseLeftReleased()
{
	Game::s_game->gui->HandleLClick(ID);
}

Button::~Button()
{
	Game::s_game->input.RemoveMouseAction(this, Input::LeftReleased);
}
