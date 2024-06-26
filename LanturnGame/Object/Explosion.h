#pragma once
#include "SphereCollider.h"
class Explosion : public SphereCollider
{
private:
	bool flg = true;		// フラグ
	int size = 10 - 2;		// 大きさ
	unsigned int count = 0;	// 継続時間
	static int images[];	// 画像
public:
	Explosion();
	~Explosion();
	void Init(int _size);
	void Update();
	void Draw(Vector2D loc, float _distance) const;
	bool Getflg()const;
	static int LoadImages();
	static void DeleteImages();
};

