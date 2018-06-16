
#include <SFML/Graphics.hpp>
#include "SpineDrawable.h"


// void SpineDrawable::setScale(sf::Vector2f scale)
// {
// 	//SpineDrawable::D2D::Transformable::setScale(scale);
//
// 	Atlas* atlas = Atlas_createFromFile((const char*)satlas, 0);
// 	SkeletonJson* json = SkeletonJson_create(atlas);
// 	json->scale = scale.x;
// 	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, (const char*)sjson);
// 	SkeletonJson_dispose(json);
// }



void SpineDrawable::SpineLoad(const char* _atlas, const char* _json, float x, float y, const char* ref_bone, float scale, bool bShadow)
{

	strcpy(satlas, _atlas);
	strcpy(sjson, _json);

	Atlas* atlas = Atlas_createFromFile(_atlas, 0);
	SkeletonJson* json = SkeletonJson_create(atlas);
	json->scale = scale;
	SkeletonData* skeletonData = SkeletonJson_readSkeletonDataFile(json, _json);
	SkeletonJson_dispose(json);

	_SpineLoad(skeletonData, AnimationStateData_create(skeletonData));
	skeleton->flipX = false;
	skeleton->flipY = false;

	skeleton->x = 0; // change this
	skeleton->y = 0;

	// setWorldPosition(x, y, 0);

	referenceBone = Skeleton_findBone(skeleton, ref_bone);

	globalBounds = SkeletonBounds_create();
	SkeletonBounds_update(globalBounds, skeleton, true);

}


void SpineDrawable::setSkin(char* name)
{

	Skeleton_setSkinByName(SkeletonDrawable::skeleton, name);

}
void SpineDrawable::setState(char* name)
{
	AnimationState_setAnimationByName(SkeletonDrawable::state, 0, name, true);
}

/*

sf::FloatRect SpineDrawable::getLocalBounds() const { return getGlobalBounds(); }; //

sf::FloatRect SpineDrawable::getGlobalBounds() const
{
	return sf::FloatRect(
		0,
		0,
		globalBounds->maxX - globalBounds->minX,
		globalBounds->maxY - globalBounds->minY
		);
};

*/
