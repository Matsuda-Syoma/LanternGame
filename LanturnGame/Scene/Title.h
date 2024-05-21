#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene
{
private:
	int cursor_menu = 0;
	int titleimage;
	int menuimage[4];
	int cursorimage;
	int cursorX, cursorY;
	int menufireimage[4][63];
	int cursorfireimage[16];
	int MouseX, MouseY;
	int fireanim = 0;
	int cursor_fireanim = 0;
	bool isCheck = false;
	int cursor_last = 0;
public:
	Title();
	~Title();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

