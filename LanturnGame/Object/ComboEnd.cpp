#include "ComboEnd.h"
#include "DxLib.h"
#include "../Utility/common.h"

int ComboEnd::hukidasiimg;
int ComboEnd::numimg[10];

ComboEnd::ComboEnd()
{
	location.x = GetRand(200) - 100;
	location.y = GetRand(200) - 100;
}

ComboEnd::ComboEnd(int _combo)
{
	location.x = GetRand(200) - 100;
	location.y = GetRand(200) - 100;
	combo = _combo;
}

ComboEnd::~ComboEnd()
{
}

void ComboEnd::Update()
{
	if (cnt > 180) {
		flg = false;
	}
	cnt++;
}

void ComboEnd::Draw() const
{
	int bufcombo = combo;
	//DrawRotaGraph((SCREEN_WIDTH / 2) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, 1.5, 0.0, hukidasiimg, true);
	//for (int i = 0; i < 2; i++) {
	//	DrawRotaGraph((SCREEN_WIDTH / 2) + 48 - (i * 96) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, 2.0, 0.0, numimg[bufcombo % 10], true);
	//	bufcombo /= 10;
	//}
	DrawRotaGraph((SCREEN_WIDTH / 2) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, 1.5 - ((cnt / 180.0) * 1.5), 0.0, hukidasiimg, true);
	for (int i = 0; i < 2; i++) {
		DrawRotaGraph((SCREEN_WIDTH / 2) + 48 - (i * 96) + location.x + ((cnt / 180.0) * 2.0), (SCREEN_HEIGHT / 2) + 96 + location.y, 2.0 - ((cnt / 180.0) * 2.0), 0.0, numimg[bufcombo % 10], true);
		bufcombo /= 10;
	}
}

int ComboEnd::LoadImages()
{
	hukidasiimg = LoadGraph("Resources/images/hukidasi.png", 0);
	LoadDivGraph("Resources/images/number.png", 10, 10, 1, 64, 64, numimg);
	return 0;
}

void ComboEnd::DeleteImages()
{
	DeleteGraph(hukidasiimg);
	DeleteGraph(*numimg);
}

bool ComboEnd::GetFlg()
{
	return this->flg;
}
