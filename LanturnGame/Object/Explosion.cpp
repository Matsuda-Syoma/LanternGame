#include "Explosion.h"
#include "DxLib.h"
#include "../Utility/common.h"
Explosion::Explosion()
{
	radius = 15.0f;
}

Explosion::~Explosion()
{
}

void Explosion::Update()
{
	if (flg) {
		if (count > 30) {
			flg = false;
		}
		count++;
		radius = (float)count * 4;
	}
}

void Explosion::Draw(Vector2D loc) const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count * 8);
	DrawCircleAA(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), radius, 16, 0xff4444, true, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Explosion::Getflg() const
{
	return flg;
}
