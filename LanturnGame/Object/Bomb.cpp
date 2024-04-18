#include "Bomb.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include <math.h>
Bomb::Bomb()
{
	speed = 2;
}
Bomb::~Bomb()
{
}
void Bomb::Update()
{
	if (expflg) {
		mode = 3;
		speed = 3;
		expcnt--;
		if (expcnt < 0) {
			flg = false;
		}
	}
	if (knockback != 0.0f) {
		knockback /= 1.1;
	}
	location += velocity * speed;
	location += knockback;

	// ‰æ–ÊŠO‚Éo‚È‚¢‚æ‚¤‚É

	if (location.x < -MapSize + radius)
	{
		location.x = -MapSize + radius;
	}
	if (location.x >= MapSize - radius)
	{
		location.x = MapSize - radius;
	}
	if (location.y < -MapSize + radius)
	{
		location.y = -MapSize + radius;
	}
	if (location.y >= MapSize - radius)
	{
		location.y = MapSize - radius;
	}
}

void Bomb::Draw(Vector2D loc) const
{
	DrawCircle(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), radius, 0xffffff, true, true);
	if (expcnt % 60 > 30) {
		DrawCircle(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), radius, 0x888888, true, true);
	}
	if (expflg) {
		DrawFormatString((location.x - 4) + (-loc.x + (SCREEN_WIDTH / 2)), (location.y - 8) + (-loc.y + (SCREEN_HEIGHT / 2)), GetColor(255 - expcnt * 1.5, 0, 0), "%d", expcnt / 60);
	}

}

bool Bomb::GetFlg() const
{
	return flg;
}

void Bomb::SetFlg(bool b)
{
	this->flg = b;
}

void Bomb::SetExpFlg(bool b)
{
	this->expflg = b;
}

float Bomb::GetLength(Vector2D loc) 
{
	return sqrtf(powf((loc.x - location.x), 2) + powf((loc.y - location.y), 2));
}

void Bomb::SetVelocity(Vector2D loc)
{
	this->velocity = loc;
}

void Bomb::SetMode(int i)
{
	this->mode = i;
}

int Bomb::GetMode()
{
	return this->mode;
}

void Bomb::SetKnockBack(Vector2D vec, int i)
{
	this->knockback = vec * i;
}
