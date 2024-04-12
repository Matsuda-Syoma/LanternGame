#include "Bomb.h"
#include "DxLib.h"
#include "common.h"
Bomb::Bomb()
{
}
Bomb::~Bomb()
{
}
void Bomb::Update()
{
}

void Bomb::Draw(Vector2D loc) const
{
	DrawCircle(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), radius, 0xffffff, true, true);

}

bool Bomb::GetFlg() const
{
	return flg;
}

void Bomb::SetFlg(bool b)
{
	this->flg = b;
}
