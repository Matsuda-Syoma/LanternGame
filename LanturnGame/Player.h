#pragma once
#include "SphereCollider.h"
class Player : public SphereCollider
{
private:
	float speed;
	Vector2D velocity;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
};

