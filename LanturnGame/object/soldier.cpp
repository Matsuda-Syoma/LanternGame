#include "soldier.h"
#include "../Utility/common.h"
#include "../Utility/InputControl.h"
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
	state = 1;
	Movemode = GetRandom(0,2);
	deleteFlg = false;
	LoadDivGraph("Resources/images/Soldier.png", 12, 3, 4, 64, 66, soldierimg);
	soldierDetimg = LoadGraph("Resources/images/d_Soldier.png");
}

void Soldier::Update(Vector2D PL)
{
	if (state == 1)
	{
			Move(PL);
		
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
	}
	else
	{
			countNum++;
			//一定時間たったら動けるようになる
			if (240 <= countNum)
			{
				if (state == 0)
				{
					state = 1;
					countNum = 0;

				}
				else
				{
					deleteFlg = true;
					countNum = 0;

				}
			}
		if (SEflg == false && state == 2)
		{
			//プレイヤーを捕まえた
			PlaySoundMem(Sounds::SE_CD_Soldier, DX_PLAYTYPE_BACK);
			SEflg = true;
		}
		if (SEflg == false && state == 3)
		{
			//爆発に巻き込まれた
			PlaySoundMem(Sounds::SE_ED_Soldier, DX_PLAYTYPE_BACK);
			SEflg = true;
		}
	}

	PositionCheck();
}

void Soldier::Draw(Vector2D PL, float _distance)
{
	if (state == 1 || state == 0)
	{
		//兵隊イラストの描画
		DrawRotaGraphF(DrawFromCameraX(location, _distance, PL)
			, DrawFromCameraY(location, _distance, PL)
			, 1.4 * ScaleFromCamera(_distance), 0.0, soldierimg[Velimg + animcnt], true);
	}
	else
	{
		//爆発に巻き込まれたときのイラストを表示
		if (state == 3)
		{
			DrawRotaGraphF(DrawFromCameraX(location, _distance, PL)
				, DrawFromCameraY(location, _distance, PL)
				, 1.4 * ScaleFromCamera(_distance), 0.0, soldierDetimg, true);
		}
	}
}

void Soldier::Move(Vector2D PL)
{
	if (Movemode == false)
	{
		//プレイヤーとの中心座標の距離
		length = PL - location;
		float a = sqrt(pow(length.x, 2) + pow(length.y, 2));
		move.x = ((length.x / a) * 2);
		move.y = ((length.y / a) * 2);
	}
	else
	{
		//プレイヤーとの中心座標の距離
		Vector2D input = InputControl::GetLeftStick() * 500;

		input.y *= -1;

		Pin = (PL + input);

		length = Pin - location;
		float a = sqrt(pow(length.x, 2) + pow(length.y, 2));
		move.x = ((length.x / a) * 2.5);
		move.y = ((length.y / a) * 2.5);
	}

	if (move.x <= 0)
	{
		Velimg = 3;
	}
	if (move.x >= 0)
	{
		Velimg = 6;
	}

	//フラグが立っているなら動ける
	if (state == 1)
	{
		location += move;
	}

	else if(state == 0)
	{
		//一定時間停止したら動けるようになる
		countNum++;
		if (180 <= countNum)
		{
			state = 1;
			countNum = 0;
		}
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

void Soldier::SetMode(int i)
{
	state = i;
}
int Soldier::CheckMode()
{
	return state;
}

bool Soldier::CheckDLflg()
{
	return deleteFlg;
}

//乱数取得
int Soldier::GetRandom(int min, int max)
{
	return min + (int)(rand() * (max - min + 1.0) / (1.0 + RAND_MAX));
}