#pragma once
#include "SphereCollider.h"
class Explosion : public SphereCollider
{
private:
	bool flg = true;		// ƒtƒ‰ƒO
	int size = 10 - 2;		// ‘å‚«‚³
	unsigned int count = 0;	// Œp‘±ŽžŠÔ
	static int images[];	// ‰æ‘œ
public:
	Explosion();
	~Explosion();
	void Init(int _size);
	void Update();
	void Draw(Vector2D loc, float _distance) const;
	bool Getflg()const;
	static int LoadImages();
	static void DeleteImages();
};

