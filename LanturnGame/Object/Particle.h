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
	Vector2D addloc = 0;
public:
	Particle();
	~Particle();

	void Update();
	void Draw(Vector2D loc)const;
	bool Getflg()const;
	static int LoadImages();
	static void DeleteImages();
	void SetAngle(Vector2D loc, Vector2D loc2);
	void Init(int _type, SphereCollider * _root, bool _loop, float _scale);

	void SetRootLocation(Vector2D loc);

};
