#include "Explosion.h"
#include "DxLib.h"
#include "common.h"
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
		radius = count * 4;
	}
}

void Explosion::Draw(Vector2D loc) const
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count * 8);
	DrawCircle(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), radius, 0xff4444, true, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool Explosion::Getflg() const
{
	return flg;
}
