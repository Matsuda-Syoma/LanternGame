#pragma once
#include "SphereCollider.h"

class Bomb : public SphereCollider
{
private:
	bool flg = true;
public:
	Bomb();
	~Bomb();
	void Update();
	void Draw(Vector2D loc) const;
	bool GetFlg() const;
	void SetFlg(bool b);
	
};

