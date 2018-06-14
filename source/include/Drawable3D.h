
#ifndef _D3D_H_
#define _D3D_H_

#include "Constants.h"
#include "DrawableBase.h"

class Shadow;

class D3D : public virtual DrawableBase {
public:
	D3D(bool bshadow = 0);
	//D3D(float _x, float _y, bool bshadow = 0) : x(_x), y(_y), z(0)  { InitShadow(bshadow);  };
	//D3D(float _x, float _y, float _z, bool bshadow = 0) : x(_x), y(_y), z(_z) { InitShadow(bshadow); };

	void InitShadow(bool bShadow);

	virtual ~D3D();

	void SetWorldPosition(float _x, float _y, float _z) {
		x = _x;
		y = _y;
		z = _z;
		UpdateWorldPosition();
	};

	sf::Vector3f GetWorldPosition() { return sf::Vector3f(x, y, z); };

	void MoveInWorld(float _x, float _y, float _z)
	{
		x += _x;
		y += _y;
		z += _z;
		UpdateWorldPosition();
	}

protected:
	Shadow* shadow;

private:

	float x,y,z;
	void UpdateWorldPosition() {
		float fixX = (512-x) * (z / MAX_Z) * 0.35;
		SetPosition(x + fixX , y - 0.8*z);
		//float scale = 1 - z * 0.0025f;
		//SetScale(sf::Vector2f(scale, scale));
	};
};



#endif
