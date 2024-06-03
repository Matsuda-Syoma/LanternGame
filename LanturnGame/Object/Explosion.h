#pragma once
#include "SphereCollider.h"
class Explosion : public SphereCollider
{
private:
	bool flg = true;
	int size = 10 - 2;
	unsigned int count = 0;
	static int images[];
	int RGB[3] = { 0 };
public:
	Explosion();
	~Explosion();
	void Init(int _size);
	void Update();
	void Draw(Vector2D loc) const;
	bool Getflg()const;
	static int LoadImages();
	static void DeleteImages();
};

