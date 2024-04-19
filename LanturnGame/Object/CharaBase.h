#pragma once
#include "SphereCollider.h"
class CharaBase : public SphereCollider
{
protected:
	float speed = 0;
	float MapSize = 1000;
public:
	virtual void GetMapSize(float i) {
		MapSize = i;
	}
};