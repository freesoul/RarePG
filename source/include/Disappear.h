#ifndef _DISAPPEAR_H_
#define _DISAPPEAR_H_

#include "Constants.h"
#include "DrawableBase.h"
#include "DUO.h"

class Disappear : virtual public DrawableBase, public DUO {
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
			SetColor(sf::Color(255, 255, 255, alpha));
		}
		return true;
	};

private:
	DisappearStatus status;
	float alpha;
	float disSpeed;

};


#endif