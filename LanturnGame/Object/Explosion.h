#pragma once
#include "CharaBase.h"
class Explosion : public CharaBase
{
private:
	bool flg = true;		// フラグ
	int size = 10 - 2;		// 大きさ
	unsigned int count = 0;	// 継続時間
	static int images[];	// 画像
public:
	Explosion();
	~Explosion();

	void Initialize(GameMain* _g, int _obj_pos)override;
	void Finalize()override;
	void Hit(Object* _obj)override {};

	void Init(int _expsize);
	void Update(GameMain* _g)override;
	void Draw(CameraManager* camera)const override;

	bool Getflg()const;
	static int LoadImages();
	static void DeleteImages();
};

