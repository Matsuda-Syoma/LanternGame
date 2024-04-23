#include "Setting.h"
#include "Title.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Utility/UserData.h"
Setting::Setting()
{
	deadzone = UserData::LoadData(0);

}

Setting::~Setting()
{
}

AbstractScene* Setting::Update()
{

	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		menu_cursor++;
		// 一番下に到達したら、一番上にする
		if (menu_cursor > 3)
		{
			menu_cursor = 0;
		}
	}

	// カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		menu_cursor--;
		// 一番上に到達したら、一番下にする
		if (menu_cursor < 0)
		{
			menu_cursor = 3;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		return new Title;
	}
	return this;
}

void Setting::Draw() const
{
	int OldSize = GetFontSize();
	SetFontSize(32);

	DrawBox( 120, 120, SCREEN_WIDTH - 120, SCREEN_HEIGHT - 120, 0xffffff, true);
	DrawBox( 128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, 0x888888, true);

	DrawCircleAA( 320.f, 400.f, 136.f, 24, 0x4444ff, true);
	DrawCircleAA( 320.f, 400.f, 128.f, 24, 0x000044, true);
	DrawCircleAA( 320.f, 400.f, deadzone * 128.f, 24, 0xff00ff, true);
	DrawCircleAA( 320.f + (InputControl::GetLeftStick().x * 128.f)
				, 400.f + (-InputControl::GetLeftStick().y * 128.f), 8.f, 24, 0x00ffff, true);

	DrawString(220, 192, "デッドゾーン", 0xffffff);


	DrawBox(640, 192 - 4, 640 + (32 + 4) * 9, 192 + 32 + 4, 0xff4444, true);
	DrawString(640, 192, "デッドゾーンの設定", 0xffffff);

	DrawBox(640, 192 - 4, 640 + (32 + 4) * 9, 192 + 32 + 4, 0xff4444, true);
	DrawString(640, 192, "デッドゾーンの設定", 0xffffff);

	DrawString(640, 60, "ここは設定画面です", 0xffffff);
	SetFontSize(OldSize);
}
