#include "include/ObjectManager.h"
#include "include/Game.h"

#include "include/Object.h"
#include "SpineDrawable.h"
#include "AnimatedSprite.h"
#include "Shadow.h"
#include "WorldCollider.h"
#include "DUO.h"
#include "Drawable2D.h"
#include "Drawable3D.h"

// D2D
void ObjManager::RemoveD2D(D2D* drw, bool bGui)
{
	std::vector<D2D*>::iterator it;
	if (!bGui)
	{

		for (it = drws.begin(); it != drws.end(); it++)
		if ((*it) == drw)
		{
			drws.erase(it);
			return;
		}
	}
 else
 {
	 for (it = gui_drws.begin(); it != gui_drws.end(); it++)
	 if ((*it) == drw)
	 {
		 gui_drws.erase(it);
		 return;
	 }
 }
}

void ObjManager::AddD2D(D2D* drw, bool bGui)
{
	if (!bGui)
		drws.push_back(drw);
	else
		gui_drws.push_back(drw);
}

// D3D
void ObjManager::RemoveD3D(D3D* drw)
{
	std::vector<D3D*>::iterator it;
	for (it = drws3d.begin(); it != drws3d.end(); it++)
	if ((*it) == drw)
	{
		drws3d.erase(it);
		return;
	}
}

void ObjManager::AddD3D(D3D* drw)
{
	drws3d.push_back(drw);
}

// Animated Sprites
void ObjManager::RemoveAnimatedSprite(AnimatedSprite* sprite)
{
	std::vector<AnimatedSprite*>::iterator it;
	for (it = aSprites.begin(); it != aSprites.end(); it++)
	if ((*it) == sprite)
	{
		aSprites.erase(it);
		return;
	}
}

void ObjManager::AddAnimatedSprite(AnimatedSprite* sprite)
{
	aSprites.push_back(sprite);
}


// Shadows
void ObjManager::RemoveShadow(Shadow* shadow)
{
	std::vector<Shadow*>::iterator it;
	for (it = shadows.begin(); it != shadows.end(); it++)
	if ((*it) == shadow)
	{
		shadows.erase(it);
		return;
	}
}

void ObjManager::AddShadow(Shadow* shadow)
{
	shadows.push_back(shadow);
}

// DeltaUpdateObjects
void ObjManager::RemoveDeltaUpdateObject(DUO* duo)
{
	std::vector<DUO*>::iterator it;
	for (it = duos.begin(); it != duos.end(); it++)
	if ((*it) == duo)
	{
		duos.erase(it);
		return;
	}
}

void ObjManager::AddDeltaUpdateObject(DUO* duo)
{
	duos.push_back(duo);
}



// Logic Objects
void ObjManager::RemoveObject(Object* obj)
{
	std::vector<Object*>::iterator it;
	for (it = objects.begin(); it != objects.end(); it++)
	if ((*it) == obj)
	{
		objects.erase(it);
		return;
	}
}

void ObjManager::AddObject(Object* obj)
{
	objects.push_back(obj);
}



// Manager methods
void ObjManager::DrawScene() {

	// // Draw shadows
	std::vector<Shadow*>::iterator it4;
	for (it4 = shadows.begin(); it4 != shadows.end(); it4++)
		Game::s_game->renderer.draw(**it4);

	// Draw others

	std::vector<D2D*>::iterator it2;
	for (it2 = drws.begin(); it2 != drws.end(); it2++)
		Game::s_game->renderer.draw(**it2);



	std::sort(drws3d.begin(), drws3d.end(), z_test);
	std::vector<D3D*>::iterator it3;
	for (it3 = drws3d.begin(); it3 != drws3d.end(); it3++)
		Game::s_game->renderer.draw(**it3);


	// Draw gui
	for (it2 = gui_drws.begin(); it2 != gui_drws.end(); it2++)
		Game::s_game->renderer.draw(**it2);

}

void ObjManager::UpdateScene()
{
	// Update animations
	std::vector<DUO*>::iterator it5;
	for (it5 = duos.begin(); it5 != duos.end(); )
	if ((*it5)->DeltaUpdate(Game::s_game->elapsed)) it5++;
	else
	{
		(*it5)->bDestroyedOnDeltaUpdate = true;
		delete *it5;
		it5 = duos.erase(it5);
	}

	std::vector<AnimatedSprite*>::iterator it2;
	for (it2 = aSprites.begin(); it2 != aSprites.end(); it2++)
		(*it2)->UpdateSprite(Game::s_game->timer.getElapsedTime().asSeconds());

	// Update object logic
	std::vector<Object*>::iterator it3;
	for (it3 = objects.begin(); it3 != objects.end();)
	{
		if (!(*it3)->Update())
		{
			(*it3)->bDestroyedOnUpdate = true;
			delete (*it3);
			it3 = objects.erase(it3);
		}
		else it3++;
	}

	// Update shadows
	std::vector<Shadow*>::iterator it4;
	for (it4 = shadows.begin(); it4 != shadows.end(); it4++)
		(*it4)->Update();

	// Update hitboxes
	Game::s_game->colliders.UpdateBoundingBoxes();

	// Handle collisions
	Game::s_game->colliders.HandleCollisions();
}


bool ObjManager::z_test(D3D* o1, D3D* o2)
{
	return o1->GetWorldPosition().z > o2->GetWorldPosition().z;

}
