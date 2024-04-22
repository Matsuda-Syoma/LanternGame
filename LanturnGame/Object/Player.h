#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	bool hitflg = false;
	int cun = 0;
	int playerimg[12];
	int direction = 0;	// 

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
	void Invincible();

	bool GetFlg() const;
	void SetFlg(bool b);
	Vector2D GetVelocity();
};

