#include "soldier.h"
#include "../Utility/common.h"
#include "../Utility/LoadSounds.h"
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
	hitFlg = true;//当たり判定
	catchFlg = false;
	a = 0;
	LoadDivGraph("Resources/images/Soldier.png", 12, 3, 4, 64, 66, soldierimg);
	soldierDetimg = LoadGraph("Resources/images/d_Soldier.png");
}

void Soldier::Upadate(Vector2D PL)
{
	if (dmgflg == true)
	{
		Move(PL);
	}
	else
	{
		hitFlg = false;
		if (Musicflg == 0)
		{
			PlaySoundMem(Sounds::SE_DeleteSoldier, DX_PLAYTYPE_BACK);
			Musicflg = 1;
		}
		
		countNum++;
		if (240 <= countNum)
		{
			dmgflg = true;
			deleteFlg = true;
			countNum = 0;
		}
	}

	PositionCheck();
}

void Soldier::Draw(Vector2D PL, float _distance)
{
	if (dmgflg == true)
	{
		cnt++;
		if ((cnt % 60) == 0)
		{
			animcnt++;
		}
		if (3 <= animcnt)
		{
			animcnt = 0;
		}
		//兵隊イラストの描画
		DrawRotaGraphF(DrawFromCameraX(location, _distance, PL)
			, DrawFromCameraY(location, _distance, PL)
			, 1.4 * ScaleFromCamera(_distance), 0.0, soldierimg[Velimg + animcnt], true);
	}
	else
	{
		if (catchFlg == false)
		{
			DrawRotaGraphF(DrawFromCameraX(location, _distance, PL)
				, DrawFromCameraY(location, _distance, PL)
				, 1.4 * ScaleFromCamera(_distance), 0.0, soldierDetimg, true);
		}
	}
}

void Soldier::Move(Vector2D PL)
{
	//プレイヤーとの中心座標の距離
	length = location - PL;
	CD = (int)sqrtf(length.x * length.x + length.y * length.y);

	if (knockback != 0.0f) {
		knockback /= 1.1f;
	}

	if (moveFlg == true)
	{
		location += knockback;
		location += velocity * move;
	}
	else
	{
		countNum++;
		if (240 <= countNum)
		{
			moveFlg = true;
			countNum = 0;
		}
	}
	//移動速度の処理
	if (length.x < 0 && move.x < EMMAX)
	{
		move += Vector2D(EM, 0.0f);
		Velimg = 6;
	}
	if (length.x > 0 && move.x > EMMIN)
	{
		move -= Vector2D(EM, 0.0f);
		Velimg = 3;
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
void Soldier::SetDLflg(bool i)
{
	deleteFlg = i;
}
bool Soldier::ChekDLflg()
{
	return deleteFlg;
}

bool Soldier::ChekhitFlg()
{
	return hitFlg;
}

void Soldier::SetcatchFlg(bool i)
{
	catchFlg = i;
}
void Soldier::SetmoveFlg(bool i)
{
	moveFlg = i;
}
bool Soldier::ChekmoveFlg()
{
	return moveFlg;
}