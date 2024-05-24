#pragma once
#include "../Utility/Vector2D.h"
class AddScore
{
private:
	bool flg = true;
	int cnt = 0;
	int addy = 0;
	int score = 0;
	int digit = 0;
	static int numimg[10];
	Vector2D location;
	Vector2D viewlocation;
public:

	//AddScore(int _score);
	AddScore(Vector2D loc, int _score);
	~AddScore();
	void Update(Vector2D loc);
	//void Update();
	void Draw(Vector2D loc)const;
	static void LoadImages();
	static void DeleteImages();
	bool GetFlg()const;
};

