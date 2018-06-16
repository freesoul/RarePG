

#ifndef _OBJ_MANAGER_
#define _OBJ_MANAGER_

#include <vector>
#include <SFML/Graphics.hpp>

class Game;

class AnimatedSprite;
class Sprite;
class Object;
class Collider;
class Shadow;
class DUO;
class D3D;
class D2D;

class ObjManager
{
public:
	ObjManager() {};

	// Manager
	void UpdateScene();
	void DrawScene();

	// Add/remove from manager

	void AddAnimatedSprite(AnimatedSprite* aSprite);	// This works atm with Timer instead of Elapsed.
	void RemoveAnimatedSprite(AnimatedSprite* aSprite);

	void AddD2D(D2D* drw, bool bGui);
	void RemoveD2D(D2D* drw, bool bGui);

	void AddD3D(D3D* drw);
	void RemoveD3D(D3D* drw);

	void AddShadow(Shadow* shadow);
	void RemoveShadow(Shadow* shadow);

	void AddDeltaUpdateObject(DUO* duo);
	void RemoveDeltaUpdateObject(DUO* duo);

	void AddObject(Object* object);
	void RemoveObject(Object* object);

private:
	// Game objects (update)
	std::vector<Object*> objects;

	// Delta Update Objects (Update)
	std::vector<DUO*> duos;

	std::vector<AnimatedSprite*> aSprites;
	//
	// // Only to draw
	// // Z test for drawing.
	std::vector<Shadow*> shadows;
	std::vector<D3D*> drws3d;
	std::vector<D2D*> drws;
	std::vector<D2D*> gui_drws;
	static bool z_test(D3D* o1, D3D* o2);

};


#endif
