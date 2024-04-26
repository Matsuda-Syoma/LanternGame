#pragma once
#include "SphereCollider.h"
class Particle : public SphereCollider
{
private:
	bool flg = true;
	unsigned int type = 0;
	static int images[][30];
	unsigned int count = 0;
	float angle = 0.f;
	SphereCollider* root = nullptr;
	bool rootflg = false;
	bool loopflg = false;
	float scale = 1.f;
public:
	Particle();
	~Particle();

	void Update();
	void Draw(Vector2D loc)const;
	bool Getflg()const;
	static int LoadImages();
	void SetAngle(Vector2D loc, Vector2D loc2);
	void Init(int i, SphereCollider* obj, bool b2, float f);
	bool GetRootFlg();
};

