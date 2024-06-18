#include "TextDisp.h"
#include "DxLib.h"
#include "common.h"
#include "InputControl.h"
#include "../Utility/LoadSounds.h"

char TextDisp::temp[16][64];
TextDisp::TextDisp()
{
	boximg = LoadGraph("Resources/images/textbox.png");
	memset(buf, 0, sizeof(buf));
	for (int i = 0; i < 16; i++)
	{
		memset(temp[i], 0, sizeof(temp[i]));
	}
	p = temp[0];
}

TextDisp::~TextDisp()
{
}

void TextDisp::Update()
{
	// 全角、半角の判定
	char one[3] = {};
	if (*p != '\0')
	{
		nextflg = false;
		cnt = 0;
		switch (_mbclen((BYTE*)p))
		{
		case 1:
			one[0] = *(p++);
			one[1] = '\0';
			break;
		case 2:
			one[0] = *(p++);
			one[1] = *(p++);
			one[2] = '\0';
			break;
		default:
			break;
		}
		// bufに入れる
		strcat_sDx(buf, 128, one);
	}
	else
	{
		nextflg = true;
	}
	
	StrLen = (int)strlen(buf);
	StrWidth = GetDrawStringWidth(buf, StrLen);
	CenterX = (int)((0 + ((SCREEN_WIDTH - 0) / 2)) - (StrWidth / 2));

	// Aボタンで次のテキスト
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (textnum - 1 > textorder)
		{
			CenterX = 0;
			memset(buf, 0, sizeof(buf));
			p = temp[++textorder];
			PlaySoundMem(Sounds::SE_transition, DX_PLAYTYPE_BACK);
		}
		else
		{
			// ここにフラグを変える処理
			flg = false;
		}
	}
	if (nextflg)
	{
		cnt++;
		if (cnt > 60)
		{
			cnt = 0;
		}
	}
}

void TextDisp::Draw() const
{
	if (flg)
	{
		DrawRotaGraph(SCREEN_WIDTH / 2, 480 + (GetFontSize() / 2), 1.0, 0.0, boximg, true);
		DrawFormatString(CenterX, 480, 0xffffff, "%s", buf);
		if (nextflg)
		{
			if (cnt < 30)
			{
				DrawFormatString(920, 520, 0xffffff, "▼");
			}
		}
	}
}
	

int TextDisp::LoadText(int i)
{
	FILE* fp = nullptr;
	fopen_s(&fp, "Resources/Book1.csv", "r");
	if (fp == NULL)
	{
		return -1;
	}
	int cnt = 0;
	textnum = 0;

	int row = 0;
	while (1)
	{
		if (row == i) {
			break;
		}
		if (fgetc(fp) == '\n')
		{
			row++;
		}

	}
	while (1)
	{
		while (1)
		{
			c = fgetc(fp);
			buf[cnt] = c;
			if (c == ',' || c == '\n' || c == EOF)
			{
				buf[cnt] = '\0';
				break;
			}
			cnt++;
		}

		if (c == '\n' || c == EOF)
		{
			break;
		}
		// 数値を入れる
		strcat_s(temp[textnum], 64, buf);
		cnt = 0;
		textnum++;
		memset(buf, 0, sizeof(buf));
	}
	fclose(fp);
	memset(buf, 0, sizeof(buf));
	return 0;
}

bool TextDisp::GetFlg() const
{
	return this->flg;
}
