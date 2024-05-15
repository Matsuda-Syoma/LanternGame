#include "soldier.h"
#include "../Utility/common.h"
#include "DxLib.h"
#include "math.h"

#define EM 0.1f
#define EMMAX 2.0f
#define EMMIN -2.0f

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
	dmgflg = true;
	deleteFlg = false;
	LoadDivGraph("Resources/images/Soldier.png", 12, 3, 4, 64, 64, soldierimg);
}

void Soldier::Upadate(Vector2D PL)
{
	if (dmgflg == true)
	{
		Move(PL);
	}
	else
	{
		countNum++;
		if (720 <= countNum)
		{
			dmgflg = true;
			deleteFlg = true;
			countNum = 0;
		}
	}
	
	PositionCheck();
}

void Soldier::Draw(Vector2D PL)
{
	//兵隊イラストの描画
	DrawRotaGraph(location.x + (-PL.x + (SCREEN_WIDTH / 2)), location.y + (-PL.y + (SCREEN_HEIGHT / 2)), 1.0, 0.0, soldierimg[1], true);
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

	
}

void Soldier::finalize()
{
	
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

void Soldier::PositionCheck()
{
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

 void Soldier::SetDMGflg(bool i)
{
	dmgflg = i;
}
bool Soldier::ChekDMGflg()
{
	return dmgflg;
}
bool Soldier::ChekDLflg()
{
	return deleteFlg;
}
