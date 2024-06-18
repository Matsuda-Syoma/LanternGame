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
	mode = 1;
	deleteFlg = false;
	LoadDivGraph("Resources/images/Soldier.png", 12, 3, 4, 64, 66, soldierimg);
	soldierDetimg = LoadGraph("Resources/images/d_Soldier.png");
}

void Soldier::Upadate(Vector2D PL)
{
	if (mode == 1)
	{
		Move(PL);
	}
	else
	{
		if (SEflg == false && mode == 2)
		{
			//プレイヤーを捕まえた
			PlaySoundMem(Sounds::SE_CD_Soldier, DX_PLAYTYPE_BACK);
			SEflg = true;
		}
		else if (SEflg == false && mode == 3)
		{
			//爆発に巻き込まれた
			PlaySoundMem(Sounds::SE_ED_Soldier, DX_PLAYTYPE_BACK);
			SEflg = true;
		}
		
		countNum++;
		//一定時間たったら動けるようになる
		if (240 <= countNum)
		{
			mode = 1;
			deleteFlg = true;
			countNum = 0;
		}
	}

	PositionCheck();
}

void Soldier::Draw(Vector2D PL, float _distance)
{
	if (mode == 1)
	{
		//アニメーション切り替え
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
		//爆発に巻き込まれたときのイラストを表示
		if (mode == 3)
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
	if (mode == 1)
	{
		location += velocity * move;
	}

	else if(mode == 0)
	{
		//一定時間停止したら動けるようになる
		countNum++;
		if (240 <= countNum)
		{
			mode = 1;
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
	mode = i;
}
int Soldier::CheckDMGflg()
{
	return mode;
}

bool Soldier::CheckDLflg()
{
	return deleteFlg;
}