#include "Bomb.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include <math.h>

int Bomb::images;
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
		knockback /= 1.1f;
	}
	location += velocity * speed;
	location += knockback;

	// ��ʊO�ɏo�Ȃ��悤��

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
	if (expcnt % 60 > 30 && expflg) {
		SetDrawBright(255, 0, 0);// 赤以外を暗くする
	}
	DrawRotaGraphF(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0, 0.0, images, true);
	SetDrawBright(255, 255, 255);// 全色暗くしない（デフォルト）
	if (expflg) {
		DrawFormatString((int)((location.x - 4) + (-loc.x + (SCREEN_WIDTH / 2))), (int)((location.y - 8) + (-loc.y + (SCREEN_HEIGHT / 2))), GetColor(255 - (int)(expcnt * 1.5), 0, 0), "%d", expcnt / 60);
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
	this->knockback = vec * (float)i;
}

void Bomb::LoadImages()
{
	images = LoadGraph("Resources/images/bomb.png", 0);
}