#pragma once
#include "AbstractScene.h"
class Setting : public AbstractScene
{
private:
	float deadzone;
	int menu_cursor = 0;
public:
	Setting();
	~Setting();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

