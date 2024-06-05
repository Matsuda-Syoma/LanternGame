#pragma once
#include "CharaBase.h"

class Bomb : public CharaBase
{
private:
	static int images[];
	int mode = 0;
	bool flg = true;
	bool expflg = false;
	int maxexpcnt = 180;
	int expcnt = maxexpcnt;
	int expsize = 10;
	Vector2D velocity = 0;
	Vector2D exvelocity = 0;
	Vector2D knockback = 0;
	Vector2D movetoloc = 0;
public:
	Bomb();
	~Bomb();
	void Init(int _expsize);
	void Update();
	void Draw(Vector2D loc, float _distance) const;
	bool GetFlg() const;
	void SetFlg(bool b);
	bool GetExpFlg() const;
	void SetExpFlg(bool b);

	float GetLength(Vector2D loc);

	void SetVelocity(Vector2D loc);
	void SetEXVelocity(Vector2D loc);

	void SetMode(int i);

	int GetMode();
	void SetKnockBack(Vector2D vec, int i);
	static void LoadImages();
	static void DeleteImages();
};

