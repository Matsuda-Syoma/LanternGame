#include "AddScore.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include "../Scene/GameMain.h"
#include "CameraManager.h"

int AddScore::numimg[10];

AddScore::AddScore(Vector2D loc, int _score)
{
	//location = loc;
	//score = _score;
	//int bufscore = score;
	//while (bufscore != 0)
	//{
	//	bufscore /= 10;
	//	digit++;
	//}
}

AddScore::~AddScore()
{
}

void AddScore::LoadImages()
{
	LoadDivGraph("Resources/images/number.png", 10, 10, 1, 64, 64, numimg);
}

void AddScore::DeleteImages()
{
	DeleteGraph(*numimg);
}

bool AddScore::GetFlg() const
{
	return this->flg;
}

void AddScore::SetScore(int _score)
{
	score = _score;
	int bufscore = score;
	while (bufscore != 0)
	{
		bufscore /= 10;
		digit++;
	}
}

void AddScore::Initialize(GameMain* _g, int _obj_pos)
{
	gamemain = _g;
	obj_pos = _obj_pos;
	map_radius = 0;
	type = (int)TYPE::_ADDSCORE;

	totalscorelocation = Vector2D(SCREEN_WIDTH - 140, SCREEN_HEIGHT - 230);
	startlocation = Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20);
}

void AddScore::Update(GameMain* _g)
{
	// 左に出ないように
	viewlocation = location;

	if (gamemain->GetCamera()->GetLocation().x - viewlocation.x > SCREEN_WIDTH / 2.f)
	{
		viewlocation.x = gamemain->GetCamera()->GetLocation().x - SCREEN_WIDTH / 2.f;
	}
	// 右に出ないように
	if (gamemain->GetCamera()->GetLocation().x - viewlocation.x < -SCREEN_WIDTH / 2.f)
	{
		viewlocation.x = gamemain->GetCamera()->GetLocation().x - -SCREEN_WIDTH / 2.f;
	}
	// 上に出ないように
	if (gamemain->GetCamera()->GetLocation().y - viewlocation.y > SCREEN_HEIGHT / 2.1f)
	{
		viewlocation.y = gamemain->GetCamera()->GetLocation().y - SCREEN_HEIGHT / 2.1f;
	}
	// 下に出ないように
	if (gamemain->GetCamera()->GetLocation().y - viewlocation.y < -SCREEN_HEIGHT / 2.f)
	{
		viewlocation.y = gamemain->GetCamera()->GetLocation().y - -SCREEN_HEIGHT / 2.f;
	}

	if (cnt < 7)
	{
		addy += -3;
	}
	else if (cnt < 7 * 2)
	{
		addy += 3;
	}

	//if (cnt > 60)
	//{
	//	flg = false;
	//}

	if (!flg)
	{
		gamemain->DeleteObject(this, obj_pos);
	}

	if (cnt < 7 * 2)
	{
		cnt++;
	}

	if (moveflg)
	{
		if (totalscorelocation.x <= location.x)
		{
			gamemain->AddGameScore(score);
			flg = false;
			moveflg = false;
			speed = 0;
			fontsize = 0.5;
			interval = 20.0;
		}
		else
		{
			Move();
			speed += 0.2;
			if (fontsize > 0.1)
			{
				fontsize -= 0.02;
				interval -= 0.5;
			}
		}
	}

}

void AddScore::Draw(CameraManager* camera) const
{
	int bufscore = score;
	for (int i = 0; i < digit; i++) {
			//DrawRotaGraphF(DrawFromCameraX(location, _distance, loc) + (20 * (digit - 2)) - (i * 20)
			//	, DrawFromCameraY(location, _distance, loc) + addy, 0.5, 0.0, numimg[bufscore % 10], true);

		if (!moveflg)
		{
			DrawRotaGraphF(viewlocation.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + (20 * (digit - 2)) - (i * 20)
				, viewlocation.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) + addy
				, 0.5, 0.0, numimg[bufscore % 10], true);

		}
		else 
		{
			if (fontsize <= 0.1)
			{
				DrawCircle(location.x, location.y, 4, 0xffffff, TRUE);
			}
			else
			{
				DrawRotaGraphF(location.x + (interval * (digit - 2)) - (i * interval), location.y, fontsize, 0.0, numimg[bufscore % 10], true);
			}
		}

		bufscore /= 10;
	}

}

void AddScore::Hit(SphereCollider* _sphere)
{
	if (static_cast<Object*>(_sphere)->GetType() == TYPE::_PLAYER)
	{
		if (!moveflg)
		{
			location = startlocation;
			fontsize = 0.8;
			interval = 25.0;
			moveflg = true;

		}
	}
}

void AddScore::Move()
{
	length = totalscorelocation - location;
	float a = sqrt(pow(length.x, 2) + pow(length.y, 2));
	move.x = ((length.x / a) * speed);
	move.y = ((length.y / a) * speed);

	location += move;
}