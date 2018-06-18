#ifndef _OBSTACLE_H_
#define _OBSTACLE_H_

#include "Drawable3D.h"

class Obstacle : virtual public D3D  {
public:

	enum Entity { OBSTACULIZED, OBSTACLE, BOTH };

	Obstacle(int _radius=25);
	~Obstacle();

	// bool obstaculizes_right(D3D* to_who);
	// bool obstaculizes_left(D3D* to_who);
	// bool obstaculizes_left(D3D* to_who);
	// bool obstaculizes_left(D3D* to_who);

	bool is_obstacle(D3D* to_who);
	bool separate_from(D3D* who, Entity who_to_move);

private:
	int radius;

};


#endif
