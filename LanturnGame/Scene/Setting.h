#pragma once
#include "AbstractScene.h"
class Setting : public AbstractScene
{
private:
	float deadzone;
public:
	Setting();
	~Setting();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

