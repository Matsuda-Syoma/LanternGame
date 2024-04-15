#pragma once
#include "CharaBase.h"

class Bomb : public CharaBase
{
private:
	int mode = 0;
	bool flg = true;
	bool expflg = false;
	int expcnt = 180;
	Vector2D velocity = 0;
public:
	Bomb();
	~Bomb();
	void Update();
	void Draw(Vector2D loc) const;
	bool GetFlg() const;
	void SetFlg(bool b);
	void SetExpFlg(bool b);

	float GetLength(Vector2D loc);

	void SetVelocity(Vector2D loc);

	// 0:待機 1:集合 2:逃げる 3:追跡
	void SetMode(int i);

	int GetMode();
};

