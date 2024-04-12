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
		if (count > 90) {
			flg = false;
		}
		count++;
		radius = count;
	}
}

void Explosion::Draw() const
{
	DrawCircle(location.x, location.y, count, 0xff4444, true, true);
}

bool Explosion::Getflg() const
{
	return flg;
}
