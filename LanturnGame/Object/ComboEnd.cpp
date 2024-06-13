#include "ComboEnd.h"
#include "DxLib.h"
#include "../Utility/common.h"

int ComboEnd::hukidasiimg;
int ComboEnd::numimg[10];

ComboEnd::ComboEnd()
{
	location.x = GetRand(200) - 100.f;
	location.y = GetRand(200) - 100.f;
}

ComboEnd::ComboEnd(int _combo)
{
	location.x = GetRand(200) - 100.f;
	location.y = GetRand(200) - 100.f;
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
	//DrawRotaGraph((SCREEN_WIDTH - 300 + (40 * num) / 2) - (40 * i), 380, 1.0, 0.0, numimage[bufscore % 10], true);
	int bufcombo = combo;
	int num = 0;
	while (bufcombo > 0)
	{
		num++;
		bufcombo /= 10;
	}
	bufcombo = combo;
	DrawRotaGraphF((SCREEN_WIDTH / 2) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, 0.375f * ((combo / 100.0f) + 1.), 0.0, hukidasiimg, true);
	for (int i = 0; i < num; i++) {
		DrawRotaGraphF(((SCREEN_WIDTH / 2) - 16 * ((combo / 100.0f) + 1.0f) + (24 * ((combo / 100.0f) + 1.0f) * num) / 2) - (i * 24 * ((combo / 100.0f) + 1.0f)) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, 0.5f * ((combo / 100.) + 1.), 0.0, numimg[bufcombo % 10], true);
		bufcombo /= 10;
	}
	//DrawRotaGraph((SCREEN_WIDTH / 2) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, 1.5 - ((cnt / 180.0) * 1.5), 0.0, hukidasiimg, true);
	//for (int i = 0; i < 2; i++) {
	//	DrawRotaGraph((SCREEN_WIDTH / 2) + 48 - (i * 96) + location.x + ((cnt / 180.0) * 2.0), (SCREEN_HEIGHT / 2) + 96 + location.y, 2.0 - ((cnt / 180.0) * 2.0), 0.0, numimg[bufcombo % 10], true);
	//	bufcombo /= 10;
	//}
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
