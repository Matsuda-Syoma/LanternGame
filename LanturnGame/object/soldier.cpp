#include "soldier.h"
#include "../Utility/common.h"
#include "DxLib.h"
#include "math.h"

Soldier::Soldier()
{
	Initialize();
}

Soldier::~Soldier()
{

}

void Soldier::Initialize()
{
	speed = 2;	//���x�̏�����
	
	//�摜�̓ǂݍ��݂Ɖ摜�����邩�̊m�F
	/*image = LoadGraph();

	if (image == -1)
	{
		throw("���������܂���B\n");
	}*/
}

void Soldier::Upadate(Vector2D PL)
{
	Move(PL);
}

void Soldier::Draw(Vector2D PL)
{
	DrawCircleAA(location.x + (-PL.x + (SCREEN_WIDTH / 2)), location.y + (-PL.y + (SCREEN_HEIGHT / 2)), radius, 16, 0xf14f5f, true, true);
	/*DrawGraph(location.x, location.y, image, TRUE);*/
}

void Soldier::Move(Vector2D PL)
{
	//プレイヤーとの中心座標の距離
	length = location - PL;
	CD = (int)sqrtf(length.x * length.x + length.y * length.y);

	if (knockback != 0.0f) {
		knockback /= 1.1f;
	}

	location += knockback;


	if (length.x <= 0)
	{
		location += Vector2D(5.0f,0.0f);
	}
	if (length.x >= 0)
	{
		location -= Vector2D(5.0f, 0.0f);
	}
	if (length.y <= 0)
	{
		location += Vector2D(0.0f, 5.0f);
	}
	if (length.y >= 0)
	{
		location -= Vector2D(0.0f, 5.0f);
	}
}

void Soldier::finalize()
{
	/*printfDx("捕まえた");*/
	delete this;
}

float Soldier::direction(Vector2D PL)
{
	return  sqrtf(powf((PL.x - location.x), 2) + powf((PL.y - location.y), 2));
}

void Soldier::Knockback(Vector2D V, float P)
{
	this->knockback = V * P;
}