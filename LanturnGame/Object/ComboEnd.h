#pragma once
#include "../Utility/Vector2D.h"
class ComboEnd
{
private:
	Vector2D location;
	int cnt = 0;
	int combo = 0;
	bool flg = true;
	static int hukidasiimg;
	static int numimg[10];
	static int alphabetimage[26];
public:
	ComboEnd(int _combo);
	ComboEnd();
	~ComboEnd();
	void Update();
	void Draw()const;
	static int LoadImages();
	static void DeleteImages();
	bool GetFlg();
};

