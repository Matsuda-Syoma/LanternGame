#pragma once
#include "../Utility/Vector2D.h"

class Notify
{
private:
	int enablenum[5][2] = {};
	char text[5][32] = {};
public:
	Notify();
	~Notify();
	void Update();
	void Draw(Vector2D loc)const;
	static int LoadImages();
	static void DeleteImages();
	void SetText(char* c);
};

