#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
};

