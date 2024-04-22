#pragma once
#include "AbstractScene.h"
class Setting : public AbstractScene
{
public:
	Setting();
	~Setting();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

