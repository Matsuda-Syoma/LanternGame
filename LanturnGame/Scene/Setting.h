#pragma once
#include "AbstractScene.h"
class Setting : public AbstractScene
{
private:
	int settingimage;
	float bgm;
	float se;
	float config[4] = {};
	int menu_cursor = 0;
	int sound_cursor = 0;
	int config_cursor = 0;
	int active_menu_cursor = 0;
	bool isActive = false;
public:
	Setting();
	~Setting();
	virtual AbstractScene* Update() override;
	void Draw() const override;
};

