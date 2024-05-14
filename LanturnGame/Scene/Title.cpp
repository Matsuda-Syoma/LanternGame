#include "Title.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include "GameMain.h"
#include "Setting.h"


Title::Title()
{
	menuimage[0] = LoadGraph("Resources/images/titlemenu_start.png");
	menuimage[1] = LoadGraph("Resources/images/titlemenu_setting.png");
	menuimage[2] = LoadGraph("Resources/images/titlemenu_end.png");
	if (menuimage[0] == -1) {
		printfDx("err : menuimage\n");
	}
	LoadDivGraph("Resources/images/titlemenu_game.png", 63, 9, 7, 512, 512, menufireimage[0]);
	LoadDivGraph("Resources/images/titlemenu_setting_fire.png", 63, 9, 7, 512, 512, menufireimage[1]);
	LoadDivGraph("Resources/images/titlemenu_end_fire.png", 63, 9, 7, 512, 512, menufireimage[2]);
	cursorimage = LoadGraph("Resources/images/match.png", 0);
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
	GetMousePoint(&MouseX,&MouseY);
	clsDx();
	printfDx("%d %d", MouseX, MouseY);
	if (fireanim < 62) {
		fireanim++;
	}
	else {
		fireanim = 0;
	}

	return this;
}

void Title::Draw() const
{
	DrawString(580, 60, "ここはタイトルです", 0xffffff);
	int OldBlendMode, OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - ((fireanim / 70.) * 511));
	for (int i = 0; i < 3; i++) {
		DrawRotaGraph(SCREEN_WIDTH / 2, 380 + (i * 65), 1.0, 0.0, menuimage[i], true);
	}
	SetDrawBlendMode(OldBlendMode, OldBlendParam);
	DrawRotaGraph(SCREEN_WIDTH / 2, 380 + (menu_cursor * 65), 1.0, 0.0, menufireimage[menu_cursor][fireanim], true);
	switch (menu_cursor)
	{
	case 0:
		DrawRotaGraph(380, 380, 1.0, 0.0, cursorimage, true);
		break;
	case 1:
		DrawRotaGraph(490, 445, 1.0, 0.0, cursorimage, true);
		break;
	case 2:
		DrawRotaGraph(555, 510, 1.0, 0.0, cursorimage, true);
		break;
	default:
		break;
	}
	//DrawCircle(560, 346 + menu_cursor * GetFontSize(), 8,0xffffff, TRUE);
	//DrawString(580, 336 + (0 * GetFontSize()), "ゲームスタート", 0xffffff);
	//DrawString(580, 336 + (1 * GetFontSize()), "設定画面", 0xffffff);
	//DrawString(580, 336 + (2 * GetFontSize()), "ヘルプ", 0xffffff);
	//DrawString(580, 336 + (3 * GetFontSize()), "終了", 0xffffff);
}
