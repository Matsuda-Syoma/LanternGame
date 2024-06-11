#pragma once
#include "SphereCollider.h"
class Particle : public SphereCollider
{
private:
	bool flg = true;
	bool visible = true;
	unsigned int type = 0;
	static int images[][30];
	unsigned int lifetime = 0;
	float imageangle = 0.f;
	float angle = 0.f;
	float speed = 0.f;
	SphereCollider* root = nullptr;
	bool loopflg = false;
	float scale = 1.f;
	Vector2D addloc = 0;
	Vector2D velocity = 0.f;
	int color[3] = {};
public:
	Particle();
	~Particle();

	void Update();
	void Draw(Vector2D loc, float _distance)const;
	bool Getflg()const;
	static int LoadImages();
	static void DeleteImages();
	void SetAngle(Vector2D loc, Vector2D loc2);
	void SetAngle(float _angle);
	void Init(int _type, SphereCollider * _root, bool _loop, float _scale);

	void SetRootLocation(Vector2D loc);

	void SetSpeed(float _speed);

	void SetVisible(bool b);

};

