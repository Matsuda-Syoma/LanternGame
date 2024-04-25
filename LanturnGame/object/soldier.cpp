#include "soldier.h"
#include "../Utility/common.h"
#include "DxLib.h"
#include "math.h"

#define EM 0.1f
#define EMMAX 3.0f
#define EMMIN -3.0f

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
	location += velocity * move;

	//移動速度の処理
	if (length.x < 0 && move.x < EMMAX)
	{
		move += Vector2D(EM,0.0f);
	}
	if (length.x > 0 && move.x > EMMIN)
	{
		move -= Vector2D(EM, 0.0f);
	}
	if (length.y < 0 && move.y < EMMAX)
	{
		move += Vector2D(0.0f, EM);
	}
	if (length.y > 0 && move.y > EMMIN)
	{
		move -= Vector2D(0.0f, EM);
	}

	//ステージの壁より外に行かない
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

void Soldier::finalize()
{
	/*printfDx("捕まえた");*/
	delete this;
}

float Soldier::direction(Vector2D L)
{
	return  sqrtf(powf((L.x - location.x), 2) + powf((L.y - location.y), 2));
}

void Soldier::Knockback(Vector2D V, float P)
{
	this->knockback = V * P;
}
void Soldier::SetVelocity(Vector2D loc)
{
	this->velocity = loc;
}