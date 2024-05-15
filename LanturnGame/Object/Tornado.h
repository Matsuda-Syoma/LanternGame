#pragma once
#include "SphereCollider.h"
class Tornado : public SphereCollider
{
private:

public:
	Tornado();
	~Tornado();
	void Update();
	void Draw(Vector2D loc)const;
};

