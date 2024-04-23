#pragma once
#include "SphereCollider.h"
class Explosion : public SphereCollider
{
private:
	bool flg = true;
	unsigned int count = 0;
	static int images[];

public:
	Explosion();
	~Explosion();
	void Update();
	void Draw(Vector2D loc) const;
	bool Getflg()const;
	static int LoadImages();
};

