#include "soldier.h"
#include "../Utility/common.h"
#include "../Utility/LoadSounds.h"
#include "DxLib.h"
#include "math.h"
#include "../Scene/GameMain.h"
#include "CameraManager.h"

#define EM 0.1f
#define EMRIGHT 2.0f
#define EMLEFT -2.0f

Soldier::Soldier()
{

}

Soldier::~Soldier()
{

}

void Soldier::Initialize(GameMain* _g, int _obj_pos)
{
	CharaBase::Initialize(_g, _obj_pos);
	type = (int)TYPE::_SOLDIER;
	mode = 1;
	deleteFlg = false;
	LoadDivGraph("Resources/images/Soldier.png", 12, 3, 4, 64, 66, soldierimg);
	soldierDetimg = LoadGraph("Resources/images/d_Soldier.png");
}

void Soldier::Finalize()
{
}

void Soldier::Hit(SphereCollider* _sphere)
{
	// 兵隊とプレイヤーの当たり判定
	if (static_cast<Object*>(_sphere)->GetType() == TYPE::_PLAYER)
	{
		if (static_cast<Player*>(_sphere)->GetHitFlg() == false && CheckMode() == 1)
		{
			gamemain->AddLife(-1);
			//hitmoment = true;
			static_cast<Player*>(_sphere)->SetHitFlg(true);
			static_cast<Player*>(_sphere)->SetHitSoldier(true);
			for (int c = 0; c < GM_MAX_OBJECT; c++)
			{
				if (gamemain->GetObjectA(c) != nullptr)
				{
					if (gamemain->GetObjectA(c)->GetType() == TYPE::_SOLDIER)
					{
						static_cast<Soldier*>(gamemain->GetObjectA(c))->SetMode(0);
					}
				}
			}
			SetMode(2);
		}
	}
	//else if (!soldier[i]->HitSphere(player) && hitmoment == true)
	//{
	//	hitmoment = false;
	//}
	//if (soldier[i]->CheckDLflg() == true)
	//{
	//	soldier[i] = nullptr;
	//	delete soldier[i];
	//	break;
	//}
	if (static_cast<Object*>(_sphere)->GetType() == TYPE::_EXPLOSION)
	{
		if (CheckMode() == 1)
		{
			SetMode(3);
		}
	}
}

void Soldier::Update(GameMain* _g)
{
	if (mode == 1)
	{
		Move(gamemain->GetPlayer()->GetLocation());

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
				if (mode == 0)
				{
					mode = 1;
					countNum = 0;

				}
				else
				{
					gamemain->DeleteObject(this, obj_pos);
					deleteFlg = true;
					countNum = 0;

				}
			}
		if (SEflg == false && mode == 2)
		{
			//プレイヤーを捕まえた
			PlaySoundMem(Sounds::SE_CD_Soldier, DX_PLAYTYPE_BACK);
			SEflg = true;
		}
		if (SEflg == false && mode == 3)
		{
			//爆発に巻き込まれた
			PlaySoundMem(Sounds::SE_ED_Soldier, DX_PLAYTYPE_BACK);
			SEflg = true;
		}
	}

	PositionCheck();
}

void Soldier::Draw(CameraManager* camera)const
{
	if (mode == 1 || mode == 0)
	{
		//兵隊イラストの描画
		//DrawRotaGraphF(DrawFromCameraX(location, _distance, PL)
		//	, DrawFromCameraY(location, _distance, PL)
		//	, 1.4 * ScaleFromCamera(_distance), 0.0, soldierimg[Velimg + animcnt], true);
		DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
					,  location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
					,  1.4f * (1 - ((camera->GetDistance() / DISTANCE_NUM))), 0.0, soldierimg[Velimg + animcnt], true);
	}
	else
	{
		//爆発に巻き込まれたときのイラストを表示
		if (mode == 3)
		{
			DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
						,  location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
						,  1.4f * (1 - ((camera->GetDistance() / DISTANCE_NUM))), 0.0, soldierDetimg, true);
		}
	}
}

void Soldier::Move(Vector2D PL)
{
	//プレイヤーとの中心座標の距離
	length = PL - location;
	float a = sqrt(pow(length.x, 2) + pow(length.y, 2));
	move.x = ((length.x / a) * 2);
	move.y = ((length.y / a) * 2);

	if (move.x <= 0)
	{
		Velimg = 3;
	}
	if (move.x >= 0)
	{
		Velimg = 6;
	}

	//フラグが立っているなら動ける
	if (mode == 1)
	{
		location += move;
		location += velocity;
	}

	else if(mode == 0)
	{
		//一定時間停止したら動けるようになる
		countNum++;
		if (180 <= countNum)
		{
			mode = 1;
			countNum = 0;
		}
	}
	
	Vector2D ee = 0;
	float eel = 65535;
	int chek = -1;

	//兵隊同士の当たり判定
	for (int j = 0; j < GM_MAX_OBJECT; j++)
	{
		if (gamemain->GetObjectA(j) != nullptr)
		{
			if (gamemain->GetObjectA(j) != this)
			{
				// nullptrじゃないなら距離を見る
				if (gamemain->GetObjectA(j)->GetType() == TYPE::_SOLDIER || 
					gamemain->GetObjectA(j)->GetType() == TYPE::_BOMB)
				{

					// 距離が短いなら変数を保存する
					if (eel > direction(gamemain->GetObjectA(j)->GetLocation()))
					{
						chek = j;
						eel = direction(gamemain->GetObjectA(j)->GetLocation());
					}
				}
			}
		}
	}
	if (chek != -1)
	{
		if (eel < 80)
		{
			ee = (gamemain->GetObjectA(chek)->GetLocation() - GetLocation());
			ee /= eel;
			SetVelocity(ee);
		}
	}

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
	mode = i;
}
int Soldier::CheckMode()
{
	return mode;
}

bool Soldier::CheckDLflg()
{
	return deleteFlg;
}