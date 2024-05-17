#pragma once
#include "SphereCollider.h"
class Tornado : public SphereCollider
{
private:
	static int images;
	int cnt = 0;
public:
	Tornado();
	~Tornado();
	void Update();
	void Draw(Vector2D loc)const;
	static int LoadImages();
	static void DeleteImages();
};

