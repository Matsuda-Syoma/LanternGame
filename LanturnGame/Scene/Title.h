#pragma once
#include "AbstractScene.h"
class Title : public AbstractScene
{
public:
	Title();
	~Title();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

