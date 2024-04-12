#include "Explosion.h"
#include "DxLib.h"
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
		if (count > 45) {
			flg = false;
		}
		count++;
		radius = count * 2;
	}
}

void Explosion::Draw() const
{
	DrawCircle(location.x, location.y, radius, 0xff4444, true, true);
}

bool Explosion::Getflg() const
{
	return flg;
}
