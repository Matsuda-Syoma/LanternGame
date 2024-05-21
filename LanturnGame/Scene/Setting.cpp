#include "Setting.h"
#include "DxLib.h"
#include <math.h>
#include "Title.h"
#include "../Utility/InputControl.h"
#include "../Utility/UserData.h"
#include <string>
#include "../Utility/LoadSounds.h"
using namespace std;
Setting::Setting()
{
	deadzone = UserData::LoadData(0);

}

Setting::~Setting()
{
}

AbstractScene* Setting::Update()
{
	// デッドゾーンの変更
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
		deadzone += -0.1;
		// 一番下に到達したら、一番上にする
		if (deadzone < 0.f)
		{
			deadzone = 0.f;
		}
	}

	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
		deadzone += 0.1;
		// 一番下に到達したら、一番上にする
		if (deadzone > 1.f)
		{
			deadzone = 1.f;
		}
	}



	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
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
		PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
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
		PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
		switch (menu_cursor)
		{
		case 0:
			break;
		case 1:
			break;
		case 2:
			break;
		case 3:
			UserData::SaveData(0, deadzone);
			return new Title;
			break;
		}
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
		UserData::SaveData(0, deadzone);
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
	if (fabsf(InputControl::GetLeftStick().x) > deadzone ||
		fabsf(InputControl::GetLeftStick().y) > deadzone) {
		DrawCircleAA(320.f + (InputControl::GetLeftStick().x * 128.f)
			, 400.f + (-InputControl::GetLeftStick().y * 128.f), 8.f, 24, 0xff0000, true);
	}
	else {
		DrawCircleAA(320.f + (InputControl::GetLeftStick().x * 128.f)
			, 400.f + (-InputControl::GetLeftStick().y * 128.f), 8.f, 24, 0x00ffff, true);
	}

	

	DrawString(220, 192, "デッドゾーン", 0xffffff);

	switch (menu_cursor) {
	case 0:
		DrawBox(640, 200 - 4, 640 + (32 + 4) * 9, 200 + (32 + 4), 0xff4444, true);
		break;
	case 1:
		DrawBox(640, 300 - 4, 640 + (32 + 4) * 7, 300 + (32 + 4), 0xff4444, true);
		break;
	case 2:
		DrawBox(640, 400 - 4, 640 + (32 + 4) * 7, 400 + (32 + 4), 0xff4444, true);
		break;
	case 3:
		DrawBox(640, 500 - 4, 640 + (32 + 4) * 7, 500 + (32 + 4), 0xff4444, true);
		break;
	default:
		break;
	}

	DrawString(640, 200, "デッドゾーンの設定", 0xffffff);
	DrawString(640, 300, "タイトルに戻る", 0xffffff);
	DrawString(640, 400, "タイトルに戻る", 0xffffff);
	DrawString(640, 500, "タイトルに戻る", 0xffffff);

	DrawString(640, 60, "ここは設定画面です", 0xffffff);
	SetFontSize(OldSize);
}
