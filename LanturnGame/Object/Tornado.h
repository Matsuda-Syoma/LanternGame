#pragma once
#include "Object.h"
class GameMain;
class CameraManager;
class Tornado : public Object
{
private:
	static int images;
	int cnt = 0;
public:
	Tornado();
	~Tornado();
	static int LoadImages();
	static void DeleteImages();

	void Initialize(int _obj_pos) override;
	void Finalize() override {};
	void Update(GameMain* _g) override;
	void Draw(CameraManager* camera)const override;
	void Hit(SphereCollider* _sphere) override {};                         // 当たった時の処理
};

