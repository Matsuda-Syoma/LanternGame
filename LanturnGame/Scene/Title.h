#pragma once
#include "AbstractScene.h"

class Title : public AbstractScene
{
private:
	int menu_cursor = 0;
public:
	Title();
	~Title();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};
