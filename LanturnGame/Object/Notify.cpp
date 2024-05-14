#include "Notify.h"
#include "DxLib.h"
#include "../Utility/common.h"
Notify::Notify()
{
	//for (int i = 0; i < 5; i++){
	//	enablenum[i][0] = 1;
	//	enablenum[i][1] = GetRand(120) + 60;
	//	char buf[4];
	//	sprintf_s(buf, "%d", i);
	//	strcat_s(text[i], 16, buf);
	//}
}

Notify::~Notify()
{
}

void Notify::Update()
{
	clsDx();
	for (int i = 0; i < 5; i++) {
		printfDx("%d %d\n",enablenum[i][0], enablenum[i][1]);
		}
	for (int i = 0; i < 5; i++) {
		if (enablenum[i][1] > 0) {
			enablenum[i][0] = 1;
			enablenum[i][1]--;
		}
		else {
			//enablenum[i][0] = 0;
		}
	}
}

void Notify::Draw(Vector2D loc) const
{
	int drawnum = 0;
	for (int i = 0; i < 5; i++)
	{
		if (enablenum[i][0] != 0) {
			DrawBox(SCREEN_WIDTH - 100, 100 + (100 * drawnum), SCREEN_WIDTH, 150 + (100 * drawnum), 0xffffff, false);
			DrawFormatString(SCREEN_WIDTH - 100 + GetFontSize(), 100 + (100 * drawnum) + GetFontSize(), 0xffffff, "%s", text[i]);
			drawnum++;
		}
	}

}

int Notify::LoadImages()
{
	return 0;
}

void Notify::DeleteImages()
{
}

void Notify::SetText(char* s) {

	for (int i = 0; i < 5; i++) {
		printfDx("%d",enablenum[i][0]);
		if (enablenum[i][0] == 0) {

			enablenum[0][0] = 1;
			enablenum[0][1] = 120;
			strcat_s(text[i], 32, s);
			break;
		}
	}
}