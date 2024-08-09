#pragma once
#include "Object.h"
class GameMain;
class CameraManager;

class AddScore : public Object
{
private:
	bool flg = true;
	int cnt = 0;
	int addy = 0;
	int score = 0;
	int digit = 0;
	static int numimg[10];
	Vector2D viewlocation;
public:

	AddScore() {}
	AddScore(Vector2D loc, int _score);
	~AddScore();
	static void LoadImages();
	static void DeleteImages();
	bool GetFlg()const;
	void SetScore(int _score);

	void Initialize(GameMain* _g, int _obj_pos) override;
	void Finalize() override {};
	void Update(GameMain* _g) override;
	void Draw(CameraManager* camera)const override;
	void Hit(SphereCollider* _sphere) override;
};

