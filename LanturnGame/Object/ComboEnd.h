#pragma once
#include "../Utility/Vector2D.h"
class ComboEnd
{
private:
	Vector2D location;
	int cnt = 0;
	static int hukidasiimg;
	static int numimg[10];
public:
	ComboEnd();
	~ComboEnd();
	void Update();
	void Draw()const;
	static int LoadImages();
	static void DeleteImages();
};

