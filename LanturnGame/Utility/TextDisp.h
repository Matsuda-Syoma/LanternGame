#pragma once
#include "Vector2D.h"
class TextDisp
{
private:
	int boximg;
	int cnt = 0;
	bool flg = true;
	bool nextflg = false;
	int StrLen, StrWidth, CenterX, textnum;
	int textorder = 0;
	int textmaxorder = 0;
	char buf[1024] = "\0";
	char c;
	char* p;
	static char temp[][64];
public:
	TextDisp();
	~TextDisp();
	void Update();
	void Draw() const;
	int LoadText(int i);
	bool GetFlg()const;
};

