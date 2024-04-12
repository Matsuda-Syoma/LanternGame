#pragma once
#include "SphereCollider.h"
class Explosion : public SphereCollider
{
private:
	bool flg = true;
	int count = 0;
public:
	Explosion();
	~Explosion();
	void Update();
	void Draw() const;
	bool Getflg()const;

};

