#include "Explosion.h"
#include "DxLib.h"
#include "../Utility/common.h"

int Explosion::images[30];

Explosion::Explosion()
{
	radius = 15.0f;
	for (int i = 0; i < 3; i++) {
		RGB[i] = GetRand(127) + 128;
	}
}

Explosion::~Explosion()
{
}

void Explosion::Update()
{
	if (flg) {
		if (count > 15) {
			flg = false;
		}
		count++;
		radius = (float)count * size;
	}
}

void Explosion::Draw(Vector2D loc) const
{
	//SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count * 8);
	DrawCircleAA(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), radius, 16, 0xffffff, true, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Explosion::Getflg() const
{
	return flg;
}

int Explosion::LoadImages() {
	int ret = LoadDivGraph("Resources/images/explosion.png", 30, 6, 5, 128, 128, images);
	return ret;
}

void Explosion::DeleteImages()
{
	DeleteGraph(*images);
}
