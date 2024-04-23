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
	return this;
}

void Title::Draw() const
{
	DrawString(580, 60, "ここはタイトルです", 0xffffff);
	DrawCircle(560, 340 + menu_cursor * 32, 8,0xffffff, TRUE);
	DrawString(580, 336 + (0 * 32), "ゲームスタート", 0xffffff);
	DrawString(580, 336 + (1 * 32), "設定画面", 0xffffff);
	DrawString(580, 336 + (2 * 32), "ヘルプ", 0xffffff);
	DrawString(580, 336 + (3 * 32), "終了", 0xffffff);
}
