#pragma once
#include "SphereCollider.h"
class CharaBase : public SphereCollider
{
protected:
	float speed = 0;
	float MapSize = 1000;
	Vector2D movetoloc;
public:
	virtual void GetMapSize(float i) {
		MapSize = i;
	}
	virtual Vector2D GetMoveToLocation() {
		return this->movetoloc;
	}
	virtual void SetMoveToLocation(Vector2D loc) {
		movetoloc = loc;
	}
};