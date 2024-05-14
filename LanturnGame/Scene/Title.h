#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene
{
private:
	int menu_cursor = 0;
	int menuimage[3];
	int cursorimage;
	int cursorX, cursorY;
	int menufireimage[3][63];
	int MouseX, MouseY;
	int fireanim = 0;
public:
	Title();
	~Title();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

