#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "ObjectManager.h"

class Game;

class Object {
public:
	Object();
	virtual ~Object();

	virtual bool Update() = 0;

	bool bDestroyedOnUpdate;

protected:


};


#endif
