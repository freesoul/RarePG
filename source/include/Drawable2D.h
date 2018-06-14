
#ifndef _D2D_H_
#define _D2D_H_

#include <SFML/Graphics.hpp>
#include "DrawableBase.h"

class D2D : virtual public DrawableBase {
public:
	D2D(bool _bGui = false);
	virtual ~D2D();

private:
	bool bGui;
};

#endif
