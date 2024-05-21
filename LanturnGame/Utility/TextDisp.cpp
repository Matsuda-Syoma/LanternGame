#include "TextDisp.h"
#include "DxLib.h"
#include "common.h"
#include "InputControl.h"

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
	char one[3] = {};
	if (*p != '\0')
	{
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
		strcat_sDx(buf, 128, one);
	}
	
	StrLen = (int)strlen(buf);
	StrWidth = GetDrawStringWidth(buf, StrLen);
	CenterX = (int)((0 + ((SCREEN_WIDTH - 0) / 2)) - (StrWidth / 2));
	if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
	{
		if (textnum - 1 > textorder)
		{
			CenterX = 0;
			memset(buf, 0, sizeof(buf));
			p = temp[++textorder];
		}
		else
		{
			// ‚±‚±‚Éƒtƒ‰ƒO‚ð•Ï‚¦‚éˆ—
			flg = false;
		}
	}
}

void TextDisp::Draw() const
{
	if (flg)
	{
		DrawRotaGraph(SCREEN_WIDTH / 2, 480 + (GetFontSize() / 2), 1.0, 0.0, boximg, true);
		DrawFormatString(CenterX, 480, 0xffffff, "%s", buf);
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
		// ”’l‚ð“ü‚ê‚é
		strcat_s(temp[textnum], 64, buf);
		//printfDx("%d %s\n", textnum, temp[textnum]);
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
