#pragma once
#include "AbstractScene.h"
#include "../Object/ComboEnd.h"

class Credit : public AbstractScene
{
private:
	ComboEnd** comboend;

	int time = 0;
	int creditimg;
	int alphabetimage[26];

public:
	Credit();
	~Credit();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

