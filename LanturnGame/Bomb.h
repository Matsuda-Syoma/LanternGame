#pragma once
#include "CharaBase.h"

class Bomb : public CharaBase
{
private:
	bool flg = true;
	bool expflg = false;
	int expcnt = 180;
public:
	Bomb();
	~Bomb();
	void Update();
	void Draw(Vector2D loc) const;
	bool GetFlg() const;
	void SetFlg(bool b);
	void SetExpFlg(bool b);

	float SetMinBomb(Vector2D loc);

	void SetNormalize(Vector2D loc);

	
};

