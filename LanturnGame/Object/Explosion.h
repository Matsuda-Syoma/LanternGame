#pragma once
#include "SphereCollider.h"
class Explosion : public SphereCollider
{
private:
	bool flg = true;		// �t���O
	int size = 10 - 2;		// �傫��
	unsigned int count = 0;	// �p������
	static int images[];	// �摜
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

