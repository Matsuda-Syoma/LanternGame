#pragma once
#include "Object.h"
class GameMain;
class CameraManager;

class AddScore : public Object
{
private:
	bool flg = true;
	bool moveflg = false;
	int cnt = 0;
	int movewait = 0;
	int addy = 0;
	int score = 0;
	int totalscore = 0;
	int digit = 0;
	float interval = 20;
	static int numimg[10];
	float speed = 2.0;
	float fontsize = 0.5;
	Vector2D viewlocation;
	Vector2D totalscorelocation;
	Vector2D length = 0;
	Vector2D move = 0;
	Vector2D startlocation;
	Vector2D PL = 0;


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
	// void Hit(SphereCollider* _sphere) override;
	void Hit(Object* _obj) override;

	void Move();
	void MoveTest(Vector2D PL);
};

