#ifndef _DUO_H_
#define _DUO_H_

#include "Constants.h"
#include "Game.h"
#include "ObjectManager.h"

class DUO {
public:
	DUO() : bDestroyedOnDeltaUpdate(false) {
		Game::s_game->objects.AddDeltaUpdateObject(this);
	}
	virtual bool DeltaUpdate(float elapsed) { return true;  };
	virtual ~DUO() {
		if (!bDestroyedOnDeltaUpdate)
			Game::s_game->objects.RemoveDeltaUpdateObject(this);//
	};

	bool bDestroyedOnDeltaUpdate;
private:
};


#endif
