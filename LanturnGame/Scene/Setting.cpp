#include "Setting.h"
#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

Setting::Setting()
{
	
}

Setting::~Setting()
{
}

AbstractScene* Setting::Update()
{
	return this;
}

void Setting::Draw() const
{
	DrawString(640, 60, "�����͐ݒ��ʂł�", 0xffffff);
}
