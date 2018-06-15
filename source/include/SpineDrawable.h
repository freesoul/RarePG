#ifndef _SPINE_DRAWABLE_
#define _SPINE_DRAWABLE_


#include <SFML/Graphics.hpp>
#include <spine/spine-sfml.h>
#include "Drawable2D.h"
#include "Constants.h"
#include "Game.h"
#include "DUO.h"

#include <iostream> // dbg


using namespace spine;

class SpineDrawable : public DUO, public SkeletonDrawable {
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


	void apply_transform(){
		sf::Vector2f position = getPosition();
		sf::Vector2f scale = getScale();
		sf::Vector2f origin = getOrigin();
		float rotation = getRotation();

		skeleton->x = position.x;
		skeleton->y = position.y;

		skeleton->root->scaleX=scale.x;
		skeleton->root->scaleY=scale.y;
		skeleton->root->rotation = rotation;

		Skeleton_updateWorldTransform(skeleton); // alternatively, inject this
		// in SkeletonDrawable::update, just before Skeleton_update, by modifying
		// spine-sfml.h to add a virtual function, defined in this class.
	}


	// Spine wrapping methods

	bool DeltaUpdate(float delta) override {
		update(delta);
		apply_transform();
		SkeletonBounds_update(globalBounds, skeleton, true);
		return true;
	};

	void setSkin(char* name);
	void setState(char* name);
	Skeleton* getSkeleton() { return skeleton; };

	// Transformation methods

	// void setRotation(float r) {
	// 	referenceBone->rotation = r + 90;  // SFML rotation is -90
	// };
	// float getRotation() { return referenceBone->rotation - 90;  };

	sf::FloatRect getLocalBounds() const {
		return sf::FloatRect(
			0,
			0,
			globalBounds->maxX - globalBounds->minX,
			globalBounds->maxY - globalBounds->minY
			);
	};

	sf::FloatRect getGlobalBounds() const {
		return sf::FloatRect(
			globalBounds->minX,
			globalBounds->minY,
			globalBounds->maxX - globalBounds->minX,
			globalBounds->maxY - globalBounds->minY
			);
	};


	// void setOrigin(float x, float y) {  };
	// sf::Vector2f getOrigin() { return sf::Vector2f(0,0); };
	//
	// void setScale(sf::Vector2f scale);
	// sf::Vector2f getScale() { return sf::Vector2f(0, 0); };
	//
	// void move(float x, float y) {
	// 	skeleton->x += x;
	// 	skeleton->y += y;
	// };

	// void setPosition(float x, float y) {
	// 	skeleton->x = x;
	// 	skeleton->y = y;
	// };

	// sf::Transform GetTransform()
	// {
	// 	// Building transform from nothing -> Change this.
	// 	sf::Transformable transform;
	// 	transform.setPosition(getPosition());
	// 	transform.setRotation(getRotation());
	// 	transform.setOrigin(getLocalBounds().width / 2, getLocalBounds().height / 2);
	// 	return transform.getTransform();
	// }

	// sf::Vector2f getPosition() { return sf::Vector2f(skeleton->x, skeleton->y); };

	virtual void setColor(const sf::Color& color) {  };


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
