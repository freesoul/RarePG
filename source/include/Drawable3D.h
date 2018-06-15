
#ifndef _D3D_H_
#define _D3D_H_

#include "Constants.h"
#include "Drawable2D.h"

class Shadow;

class D3D : virtual public D2D {
public:
	D3D(bool bShadow = 0);
	//D3D(float _x, float _y, bool bshadow = 0) : x(_x), y(_y), z(0)  { initShadow(bshadow);  };
	//D3D(float _x, float _y, float _z, bool bshadow = 0) : x(_x), y(_y), z(_z) { initShadow(bshadow); };

	void initShadow(bool bShadow);

	virtual ~D3D();

	void setWorldPosition(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
		updateWorldPosition();
	};

	// Needed for boundingbox update
	sf::Vector3f getWorldPosition() { return sf::Vector3f(x, y, z); };
	// virtual sf::Transform GetTransform() = 0;
	// virtual sf::FloatRect getLocalBounds() = 0;

	void moveInWorld(float _x, float _y, float _z)
	{
		x += _x;
		y += _y;
		z += _z;
		updateWorldPosition();
	}

protected:
	Shadow* shadow;

private:

	float x,y,z;
	void updateWorldPosition() {
		float fixX = (512-x) * (z / MAX_Z) * 0.35;
		setPosition(x + fixX , y - 0.8*z);
		float scale = GET_SCALE(z);
		setScale(sf::Vector2f(scale, scale));
	};
};



#endif
