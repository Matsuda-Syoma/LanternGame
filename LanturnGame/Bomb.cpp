#include "Bomb.h"
#include "DxLib.h"
Bomb::Bomb()
{
}
Bomb::~Bomb()
{
}
void Bomb::Update()
{
}

void Bomb::Draw() const
{
	DrawCircle(location.x, location.y, radius, 0xffffff, true, true);

}

bool Bomb::GetFlg() const
{
	return flg;
}

void Bomb::SetFlg(bool b)
{
	this->flg = b;
}
