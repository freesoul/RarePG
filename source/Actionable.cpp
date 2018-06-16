#include "include/Actionable.h"
#include "include/Game.h"
#include "include/Input.h"

Actionable::Actionable() {

};

void Actionable::SetMouseAction(Input::MouseActionType type, sf::IntRect* box)
{
	Game::s_game->input.AddMouseAction(this, type, box);
};
void Actionable::UnsetMouseAction(Input::MouseActionType type){
	Game::s_game->input.RemoveMouseAction(this, type);
};
Actionable::~Actionable() {

};
