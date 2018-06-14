#ifndef _SPINE_DRAWABLE_
#define _SPINE_DRAWABLE_


#include <SFML/Graphics.hpp>
#include <spine/spine-sfml.h>
#include "Drawable2D.h"
#include "Constants.h"
#include "Game.h"
#include "DUO.h"

using namespace spine;

class SpineDrawable : public DUO,  public SkeletonDrawable {
public:
	// Basic class methods

	SpineDrawable() : SkeletonDrawable() {
			Game::s_game->objects.AddDeltaUpdateObject(this);
		};

	void SpineLoad(const char* _atlas, const char* _json, float x, float y, const char* ref_bone, float scale = 1, bool bShadow = false);


	~SpineDrawable() {
		Game::s_game->objects.RemoveDeltaUpdateObject(this);
		delete globalBounds;
	};

	// Spine wrapping methods

	bool DeltaUpdate(float delta) override {
		update(delta);
		SkeletonBounds_update(globalBounds, skeleton, true);
		return true;
	};

	void setSkin(char* name);
	void setState(char* name);
	Skeleton* getSkeleton() { return skeleton; };

	// Transformation methods

	void SetRotation(float r) {
		referenceBone->rotation = r + 90;  // SFML rotation is -90
	};
	float GetRotation() { return referenceBone->rotation - 90;  };

	sf::FloatRect GetLocalBounds() {
		return sf::FloatRect(
			0,
			0,
			globalBounds->maxX - globalBounds->minX,
			globalBounds->maxY - globalBounds->minY
			);
	};
	sf::FloatRect GetGlobalBounds() {
		return sf::FloatRect(
			globalBounds->minX,
			globalBounds->minY,
			globalBounds->maxX - globalBounds->minX,
			globalBounds->maxY - globalBounds->minY
			);
	};

	void SetOrigin(float x, float y) {  };
	sf::Vector2f GetOrigin() { return sf::Vector2f(0,0); };

	void SetScale(sf::Vector2f scale);
	sf::Vector2f GetScale() { return sf::Vector2f(0, 0); };

	void Move(float x, float y) {
		skeleton->x += x;
		skeleton->y += y;
	};

	void SetPosition(float x, float y) {
		skeleton->x = x;
		skeleton->y = y;
	};

	sf::Transform GetTransform()
	{
		// Building transform from nothing -> Change this.
		sf::Transformable transform;
		transform.setPosition(GetPosition());
		transform.setRotation(GetRotation());
		transform.setOrigin(GetLocalBounds().width / 2, GetLocalBounds().height / 2);
		return transform.getTransform();
	}

	sf::Vector2f GetPosition() { return sf::Vector2f(skeleton->x, skeleton->y); };

	virtual void SetColor(const sf::Color& color) {  };


protected:
	char satlas[250];
	char sjson[250];

	// Spine variables
	SkeletonBounds* globalBounds;
	Bone* referenceBone;
	/*
	SkeletonDrawable* skeletonDrawable;
	Skeleton* skeleton;*/

};

#endif
