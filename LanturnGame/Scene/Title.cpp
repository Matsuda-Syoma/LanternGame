#include "Title.h"
#include "DxLib.h"
#include "../Utility/LoadSounds.h"
#include "../Utility/InputControl.h"
#include "GameMain.h"
#include "Setting.h"

Title::Title()
{
	SetUseASyncLoadFlag(true);
	menuimage[0] = LoadGraph("Resources/images/titlemenu_start.png");
	menuimage[1] = LoadGraph("Resources/images/titlemenu_setting.png");
	menuimage[2] = LoadGraph("Resources/images/titlemenu_help.png");
	menuimage[3] = LoadGraph("Resources/images/titlemenu_end.png");
	for (int i = 0; i < 4; i++)
	{
		if (menuimage[i] == -1) {
			printfDx("err : menuimage\n");
		}
	}
	LoadDivGraph("Resources/images/titlemenu_game.png", 63, 9, 7, 512, 512, menufireimage[0]);
	LoadDivGraph("Resources/images/titlemenu_setting_fire.png", 63, 9, 7, 512, 512, menufireimage[1]);
	LoadDivGraph("Resources/images/titlemenu_help_fire.png", 63, 9, 7, 512, 512, menufireimage[2]);
	LoadDivGraph("Resources/images/titlemenu_end_fire.png", 63, 9, 7, 512, 512, menufireimage[3]);
	LoadDivGraph("Resources/images/cursor_fire.png", 16, 4, 4, 32, 32, cursorfireimage);
	cursorimage = LoadGraph("Resources/images/match.png", 0);
	titleimage = LoadGraph("Resources/images/Title.png", 0);
	SetUseASyncLoadFlag(false);
}

Title::~Title()
{
}

AbstractScene* Title::Update()
{
	if (CheckSoundMem(Sounds::BGM_Title) == 0)
	{
		PlaySoundMem(Sounds::BGM_Title, DX_PLAYTYPE_BACK);
	}
	
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	{
		if (!isCheck)
		{
			PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
		}
		cursor_menu++;
		// 一番下に到達したら、一番上にする
		if (cursor_menu > 3)
		{
			cursor_menu = 0;
		}
	}

	// カーソル上移動
	if (InputControl::GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	{
		if (!isCheck)
		{
			PlaySoundMem(Sounds::SE_cursor, DX_PLAYTYPE_BACK);
		}
		cursor_menu--;
		// 一番上に到達したら、一番下にする
		if (cursor_menu < 0)
		{
			cursor_menu = 3;
		}
	}

	if (!isCheck) {
		cursor_last = cursor_menu;
	}

	if (cursor_fireanim < 15)
	{
		cursor_fireanim++;
	}
	else
	{
		cursor_fireanim = 0;
	}

	// カーソル決定
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (!isCheck) {
			PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
			isCheck = true;
		}
	}
	//GetMousePoint(&MouseX,&MouseY);
	//clsDx();
	//printfDx("%d %d", MouseX, MouseY);
	if (fireanim < 62) {
		if (isCheck) {
			fireanim++;
		}
	}
	else {
		switch (cursor_last)
		{
		case 0:
			StopSoundMem(Sounds::BGM_Title);
			return new GameMain;
			break;
		case 1:
			return new Setting;
			break;
		case 2:
			return new Title;
			break;
		case 3:
			return new Title;
			break;
		default:
			//return new End;
			break;
		}
	}

	if (CheckSoundMem(Sounds::SE_cursor) == 0)
	{
		StopSoundMem(Sounds::SE_cursor);
	}

	if (CheckSoundMem(Sounds::SE_transition) == 0)
	{
		StopSoundMem(Sounds::SE_transition);
	}

	return this;
}

void Title::Draw() const
{
	DrawGraph(0, 0, titleimage,true);
	//DrawString(580, 60, "ここはタイトルです", 0xffffff);
	int OldBlendMode, OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - ((fireanim / 70.) * 511));
	for (int i = 0; i < 4; i++) {
		DrawRotaGraph(1040, 380 + (i * 65), 1.0, 0.0, menuimage[i], true);
	}
	SetDrawBlendMode(OldBlendMode, OldBlendParam);
	DrawRotaGraph(1040, 380 + (cursor_last * 65), 1.0, 0.0, menufireimage[cursor_last][fireanim], true);
	DrawRotaGraph(800, 380 + (cursor_last * 65), 1.0, 0.0, cursorimage, true);
	//DrawRotaGraph(800, 370 + (cursor_last * 65), 1.0, 0.0, cursorfireimage[cursor_fireanim], true);

	//DrawCircle(560, 346 + menu_cursor * GetFontSize(), 8,0xffffff, TRUE);
	//DrawString(580, 336 + (0 * GetFontSize()), "ゲームスタート", 0xffffff);
	//DrawString(580, 336 + (1 * GetFontSize()), "設定画面", 0xffffff);
	//DrawString(580, 336 + (2 * GetFontSize()), "ヘルプ", 0xffffff);
	//DrawString(580, 336 + (3 * GetFontSize()), "終了", 0xffffff);
}
