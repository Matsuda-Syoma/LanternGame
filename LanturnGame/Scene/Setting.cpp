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
	settingimage = LoadGraph("Resources/images/brick.png", 0);
	
	bgm = UserData::LoadData(UserData::Type::SOUNDS, 0);
	se = UserData::LoadData(UserData::Type::SOUNDS, 1);
	for (int i = 0; i < 4; i++)
	{
		config[i] = UserData::LoadData(UserData::Type::SETTING, i);
	}
}

Setting::~Setting()
{
}

AbstractScene* Setting::Update()
{

	// デッドゾーンの変更
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	{
		switch (menu_cursor)
		{
		case 0:
			if (isActive)
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				config[0] += -0.1f;
				// 下限に到達したら固定する
				if (config[0] < 0.f)
				{
					config[0] = 0.f;
				}
			}

			break;
		case 1:
			if (isActive)
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				switch (sound_cursor)
				{
				case 0:
					bgm += -25.5f;
					// 下限に到達したら固定する
					if (bgm < 0.f)
					{
						bgm = 0.f;
					}
					break;
				case 1:
					se += -25.5f;
					// 下限に到達したら固定する
					if (se < 0.f)
					{
						se = 0.f;
					}
					break;
				}
			}
			break;
		case 2:
			if (isActive)
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				for (int i = 0; i < 3; i++)
				{
					if (i == config_cursor)
					{
						int min = 0;
						int minus = -1;
						switch (config_cursor)
						{
						case 0:
							min = 50;
							minus = -10;
							break;
						case 1:
							min = 8;
							minus = -1;
							break;
						case 2:
							min = 3;
							minus = -1;
							break;
						}
						config[i + 1] += minus;

						if (config[i + 1] < min)
						{
							config[i + 1] = min;
						}
					}
				}
			}
			break;
		case 3:
			break;
		}

	}
	// 右入力
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	{
		switch (menu_cursor)
		{

			// デッドゾーンの変更
		case 0:
			if (isActive)
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				config[0] += 0.1f;
				// 上限に到達したら固定する
				if (config[0] > 1.f)
				{
					config[0] = 1.f;
				}
			}
			break;

			// サウンドの変更
		case 1:
			if (isActive)
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				switch (sound_cursor)
				{
				case 0:
					bgm += 25.5f;
					// 上限に到達したら固定する
					if (bgm > 255.f)
					{
						bgm = 255.f;
					}
					break;
				case 1:
					se += 25.5f;
					// 上限に到達したら固定する
					if (se > 255.f)
					{
						se = 255.f;
					}
					break;
				}
			}
			break;

			// ゲームの変更
		case 2:
			if (isActive)
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				for (int i = 0; i < 3; i++)
				{
					if (i == config_cursor)
					{
						int max = 100;
						int plus = 1;
						switch (config_cursor)
						{
						case 0:
							max = 200;
							plus = 10;
							break;
						case 1:
							max = 16;
							plus = 1;
							break;
						case 2:
							max = 10;
							plus = 1;
							break;
						}
						config[i + 1] += plus;
						
						if (config[i + 1] > max)
						{
							config[i + 1] = max;
						}
					}
				}
			}
			break;
		}
	}

	// 決定していないなら
	if (!isActive)
	{
		//active_menu_cursor = menu_cursor;
		// 下入力
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

		// 上入力
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
	}
	// 決定を押しているなら
	else
	{
		switch (menu_cursor)
		{
			// デッドゾーンの変更
		case 0:
			break;

			// サウンドの変更
		case 1:
			if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				sound_cursor++;
				// 一番下に到達したら、一番上にする
				if (sound_cursor > 1)
				{
					sound_cursor = 0;
				}
			}

			// カーソル上移動
			if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				sound_cursor--;
				// 一番上に到達したら、一番下にする
				if (sound_cursor < 0)
				{
					sound_cursor = 1;
				}
			}
			break;

			// ゲームの変更
		case 2:
			if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				config_cursor++;
				// 一番下に到達したら、一番上にする
				if (config_cursor > 2)
				{
					config_cursor = 0;
				}
			}

			// カーソル上移動
			if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
			{
				PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
				config_cursor--;
				// 一番上に到達したら、一番下にする
				if (config_cursor < 0)
				{
					config_cursor = 2;
				}
			}
			break;

		case 3:
			break;
		}
	}
	// カーソル決定
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (!isActive)
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
				for (int i = 0; i < 4; i++)
				{
					UserData::SaveData(UserData::Type::SETTING, i, config[i]);
				}
				UserData::SaveData(UserData::Type::SOUNDS, 0, bgm);
				UserData::SaveData(UserData::Type::SOUNDS, 1, se);
				Sounds::SetSoundVolume(Sounds::BGM, bgm);
				Sounds::SetSoundVolume(Sounds::SE, se);
				return new Title;
				break;
			}
		}

		isActive = true;
	}
	if (InputControl::GetButtonDown(XINPUT_BUTTON_B))
	{
		if (!isActive)
		{
			PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
			for (int i = 0; i < 4; i++)
			{
				UserData::SaveData(UserData::Type::SETTING, i, config[i]);
			}
			UserData::SaveData(UserData::Type::SOUNDS, 0, bgm);
			UserData::SaveData(UserData::Type::SOUNDS, 1, se);
			Sounds::SetSoundVolume(Sounds::BGM, bgm);
			Sounds::SetSoundVolume(Sounds::SE, se);
			return new Title;
		}
		else
		{
			isActive = false;
			PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
			sound_cursor = 0;
			config_cursor = 0;
		}

	}
	return this;
}

void Setting::Draw() const
{
	int OldSize = GetFontSize();
	SetFontSize(32);

	DrawGraph(0, 0, settingimage, true);

	DrawBox( 120, 120, SCREEN_WIDTH - 120, SCREEN_HEIGHT - 120, 0xffffff, true);
	DrawBox( 128, 128, SCREEN_WIDTH - 128, SCREEN_HEIGHT - 128, 0x888888, true);
	switch (menu_cursor)
	{
	case 0:
		DrawCircleAA(320.f, 400.f, 136.f, 24, 0x4444ff, true);
		DrawCircleAA(320.f, 400.f, 128.f, 24, 0x000044, true);
		DrawCircleAA(320.f, 400.f, config[0] * 128.f, 24, 0xff00ff, true);
		if (fabsf(InputControl::GetLeftStick().x) > config[0] ||
			fabsf(InputControl::GetLeftStick().y) > config[0]) {
			DrawCircleAA(320.f + (InputControl::GetLeftStick().x * 128.f)
				, 400.f + (-InputControl::GetLeftStick().y * 128.f), 8.f, 24, 0xff0000, true);
		}
		else {
			DrawCircleAA(320.f + (InputControl::GetLeftStick().x * 128.f)
				, 400.f + (-InputControl::GetLeftStick().y * 128.f), 8.f, 24, 0x00ffff, true);
		}
		DrawString(220, 170, "デッドゾーン", 0xffffff);
		DrawFormatString(220, 210, 0xffffff, "%.1f", config[0]);
		break;
	case 1:
		DrawString(220, 170, "サウンドの設定", 0xffffff);
		DrawFormatString(220, 210, 0xffffff, "%.1f", (bgm / 255.));
		DrawFormatString(320, 210, 0xffffff, "%.1f", (se / 255.));
		if (isActive)
		{
			switch (sound_cursor)
			{
			case 0:
				DrawBox(220, 300 - 4, 220 + (16 + 4) * 3, 300 + (32 + 4), 0xff4444, true);
				break;
			case 1:
				DrawBox(220, 400 - 4, 220 + (16 + 4) * 2, 400 + (32 + 4), 0xff4444, true);
				break;
			}
		}
		DrawString(220, 300, "BGM", 0xffffff);
		DrawString(220, 400, "SE", 0xffffff);
		DrawBox(220, 358, 604, 378, 0x444444, true);
		DrawBox(220 + 8, 358 + 8, 220 + 8 + ((bgm / 255.) * 368.), 378 - 8, 0xffffff, true);
		DrawBox(220, 458, 604, 478, 0x444444, true);
		DrawBox(220 + 8, 458 + 8, 220 + 8 + ((se / 255.) * 368.), 478 - 8, 0xffffff, true);
		break;
	case 2:
		DrawString(220, 170, "ゲームの設定", 0xffffff);
		DrawFormatString(220, 210, 0xffffff, "%d", (int)config[1]);
		DrawFormatString(320, 210, 0xffffff, "%d", (int)config[2]);
		DrawFormatString(420, 210, 0xffffff, "%d", (int)config[3]);
		if (isActive)
		{
			switch (config_cursor)
			{
			case 0:
				DrawBox(220, 300 - 4, 220 + (32 + 4) * 4, 300 + (32 + 4), 0xff4444, true);
				break;
			case 1:
				DrawBox(220, 400 - 4, 220 + (32 + 4) * 5, 400 + (32 + 4), 0xff4444, true);
				break;
			case 2:
				DrawBox(220, 500 - 4, 220 + (32 + 4) * 4, 500 + (32 + 4), 0xff4444, true);
				break;
			}
		}
		DrawString(220, 300, "爆弾の数", 0xffffff);
		DrawString(220, 400, "爆発サイズ", 0xffffff);
		DrawString(220, 500, "兵士の数", 0xffffff);
		DrawBox(220, 358, 604, 378, 0x444444, true);
		DrawBox(220 + 8, 358 + 8, 220 + 8 + max(4, (((config[1] - 50) / 150.) * 368.)), 378 - 8, 0xffffff, true);
		DrawBox(220, 458, 604, 478, 0x444444, true);
		DrawBox(220 + 8, 458 + 8, 220 + 8 + max(4, (((config[2] - 8) / 8.) * 368.)), 478 - 8, 0xffffff, true);
		DrawBox(220, 558, 604, 578, 0x444444, true);
		DrawBox(220 + 8, 558 + 8, 220 + 8 + max(4, (((config[3] - 3) / 7.) * 368.)), 578 - 8, 0xffffff, true);
		break;
	case 3:
		break;
	}
	
	int color = 0x222222;
	if (isActive)
	{
		color = 0xff4444;
	}
	switch (menu_cursor) {
	case 0:
		DrawBox(640, 200 - 4, 640 + (32 + 4) * 9, 200 + (32 + 4), color, true);
		break;
	case 1:
		DrawBox(640, 300 - 4, 640 + (32 + 4) * 7, 300 + (32 + 4), color, true);
		break;
	case 2:
		DrawBox(640, 400 - 4, 640 + (32 + 4) * 6, 400 + (32 + 4), color, true);
		break;
	case 3:
		DrawBox(640, 500 - 4, 640 + (32 + 4) * 7, 500 + (32 + 4), color, true);
		break;
	default:
		break;
	}

	DrawString(640, 200, "デッドゾーンの設定", 0xffffff);
	DrawString(640, 300, "サウンドの設定", 0xffffff);
	DrawString(640, 400, "ゲームの設定", 0xffffff);
	DrawString(640, 500, "タイトルに戻る", 0xffffff);

	DrawString(640, 60, "ここは設定画面です", 0xffffff);
	SetFontSize(OldSize);
}
