#include "ComboEnd.h"
#include "DxLib.h"
#include "../Utility/common.h"

int ComboEnd::hukidasiimg;
int ComboEnd::numimg[10];

ComboEnd::ComboEnd()
{
	
}

ComboEnd::~ComboEnd()
{
}

void ComboEnd::Update()
{
}

void ComboEnd::Draw() const
{
	//DrawRotaGraphF((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2));
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
