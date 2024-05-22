#pragma once
#include "../Utility/Vector2D.h"
class AddScore
{
private:
	int score = 0;
	int numimg[10];
	Vector2D location;
public:

	//AddScore(int _score);
	AddScore(Vector2D loc, int _score);
	~AddScore();
	void Update(Vector2D loc);
	//void Update();
	void Draw(Vector2D loc)const;
	void LoadImages();
	void DeleteImages();
};

