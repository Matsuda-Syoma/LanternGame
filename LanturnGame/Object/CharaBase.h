#pragma once
#include "SphereCollider.h"
class CharaBase : public SphereCollider
{
protected:
	float speed;
	float MapSize;
public:
	virtual void GetMapSize(int i) {
		MapSize = i;
	}
};