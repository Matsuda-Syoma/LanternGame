#include "ComboEnd.h"
#include "DxLib.h"
#include "../Utility/common.h"

int ComboEnd::hukidasiimg;
int ComboEnd::numimg[10];
int ComboEnd::alphabetimage[26];

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

}

int ComboEnd::LoadImages()
{
	hukidasiimg = LoadGraph("Resources/images/hukidasi.png", 0);
	LoadDivGraph("Resources/images/number.png", 10, 10, 1, 64, 64, numimg);
	LoadDivGraph("Resources/images/alphabet.png", 26, 7, 4, 64, 64, alphabetimage);
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
