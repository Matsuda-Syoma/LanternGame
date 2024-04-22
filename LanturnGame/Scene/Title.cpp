#include "Title.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "GameMain.h"
#include "Setting.h"


Title::Title()
{
}

Title::~Title()
{
}

AbstractScene* Title::Update()
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



	// カーソル決定
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		switch (menu_cursor)
		{
		case 0:
			return new GameMain;
			break;
		case 1:
			return new Setting;
			break;
		case 2:
			//return new Help;
			break;
		default:
			//return new End;
			break;
		}
	}
	return new Setting;
}

void Title::Draw() const
{
	DrawString(640, 60, "ここはタイトルです", 0xffffff);
	DrawCircle(640, 340 + menu_cursor * 32, 16,0xffffff, TRUE);
}
