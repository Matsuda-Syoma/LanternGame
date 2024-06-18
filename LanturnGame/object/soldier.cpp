#include "soldier.h"
#include "../Utility/common.h"
#include "../Utility/LoadSounds.h"
#include "DxLib.h"
#include "math.h"

#define EM 0.1f
#define EMRIGHT 2.0f
#define EMLEFT -2.0f

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
	dmgflg = 1;
	deleteFlg = false;
	hitFlg = true;//当たり判定
	catchFlg = false;
	LoadDivGraph("Resources/images/Soldier.png", 12, 3, 4, 64, 66, soldierimg);
	soldierDetimg = LoadGraph("Resources/images/d_Soldier.png");
}

void Soldier::Upadate(Vector2D PL)
{
	if (dmgflg == 1)
	{
		Move(PL);
	}
	else
	{
		hitFlg = false;

		if (Musicflg == false && dmgflg == 2)
		{
			//プレイヤーを捕まえた
			PlaySoundMem(Sounds::SE_CD_Soldier, DX_PLAYTYPE_BACK);
			Musicflg = true;
		}
		else if (Musicflg == false && dmgflg == 3)
		{
			//爆発に巻き込まれた
			PlaySoundMem(Sounds::SE_ED_Soldier, DX_PLAYTYPE_BACK);
			Musicflg = true;
		}
		
		countNum++;
		if (240 <= countNum)
		{
			dmgflg = 1;
			deleteFlg = true;
			countNum = 0;
		}
	}

	PositionCheck();
}

void Soldier::Draw(Vector2D PL, float _distance)
{
	if (dmgflg == 1)
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
		if (dmgflg == 3)
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

	//フラグが立っているなら動ける
	if (moveFlg == true)
	{
		location += velocity * move;
	}

	else
	{
		//一定時間停止したら動けるようになる
		countNum++;
		if (240 <= countNum)
		{
			moveFlg = true;
			countNum = 0;
		}
	}
	//プレイヤーとの中心座標の距離を比べて移動方向を変える
	//兵隊がプレイヤーから見て左
	if (length.x < 0 && move.x < EMRIGHT)
	{
		move += Vector2D(EM, 0.0f);
		Velimg = 6;
	}
	//兵隊がプレイヤーから見て右
	if (length.x > 0 && move.x > EMLEFT)
	{
		move -= Vector2D(EM, 0.0f);
		Velimg = 3;
	}
	//兵隊がプレイヤーから見て下
	if (length.y < 0 && move.y < EMRIGHT)
	{
		move += Vector2D(0.0f, EM);
	}
	//兵隊がプレイヤーから見て上
	if (length.y > 0 && move.y > EMLEFT)
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

void Soldier::SetDMGflg(int i)
{
	dmgflg = i;
}
bool Soldier::ChekDLflg()
{
	return deleteFlg;
}

bool Soldier::ChekhitFlg()
{
	return hitFlg;
}

void Soldier::SetcatchFlg()
{
	catchFlg = true;
}
void Soldier::SetmoveFlg()
{
	moveFlg = false;
}