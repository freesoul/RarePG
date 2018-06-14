#ifndef _DISAPPEAR_H_
#define _DISAPPEAR_H_

#include "Constants.h"
#include "Drawable2D.h"
#include "DUO.h"

#include <SFML/Graphics.hpp>


class Disappear : virtual public D2D, public DUO { // virtual public sf::Drawable,
public:
	enum DisappearStatus { NotStarted, Disappearing, Disappeared };

	Disappear(float _disTime=2.55f) {
		status = NotStarted;
		alpha = 255;
		disSpeed = 255 / _disTime;
	};

	void disappear() { status = Disappearing; alpha = 255; };

	bool disappeared() { return status == Disappeared; };

	DisappearStatus getDisappearStatus() { return status; };

	bool DeltaUpdate(float elapsed) override
	{
		if (status == Disappearing)
		{
			alpha -= elapsed*disSpeed;

			if (alpha <= 0)
			{
				status = Disappeared;
				alpha = 0;
			}
			setColor(sf::Color(255, 255, 255, alpha));
		}
		return true;
	};

private:
	DisappearStatus status;
	float alpha;
	float disSpeed;

};


#endif
