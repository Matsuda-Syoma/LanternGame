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
	radius = 96;
	map_radius = 0;
	type = (int)TYPE::_ADDSCORE;

	totalscorelocation = Vector2D(SCREEN_WIDTH - 140, SCREEN_HEIGHT - 230);
	startlocation = Vector2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 20);
}

void AddScore::Update(GameMain* _g)
{

	PL = gamemain->GetPlayer()->GetLocation();

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
		speed = 0;
		fontsize = 0.5;
		interval = 20.0;
		movewait = 0;
	}
	else {
		if (!moveflg)
		{
			if (movewait <= 30)
			{
				movewait++;
			}
			else {
				/*location = startlocation;*/
				fontsize = 0.8;
				interval = 22.0;
				moveflg = true;
				

			}

		}
		else {
			if (movewait <= 60)
			{

				movewait++;
			}

		}

	}

	if (cnt < 7 * 2)
	{
		cnt++;
	}


	if (moveflg)
	{
		/*if (totalscorelocation.x <= location.x)
		{
			gamemain->AddGameScore(score);
			flg = false;
			moveflg = false;
			speed = 0;
			fontsize = 0.5;
			interval = 20.0;
		}
		else
		{*/
			MoveTest(PL);
			speed += 0.2;
			if (fontsize > 0.1 && movewait >= 60)
			{
				fontsize -= 0.02;
				interval -= 0.5;
			}
	/*	}*/
	}

}

void AddScore::Draw(CameraManager* camera) const
{
	int bufscore = score;
	for (int i = 0; i < digit; i++) {
			//DrawRotaGraphF(DrawFromCameraX(location, _distance, loc) + (20 * (digit - 2)) - (i * 20)
			//	, DrawFromCameraY(location, _distance, loc) + addy, 0.5, 0.0, numimg[bufscore % 10], true);

		/*if (!moveflg)
		{
			DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + (20 * (digit - 2)) - (i * 20)
				, location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) + addy
				, 0.5, 0.0, numimg[bufscore % 10], true);

		}
		else 
		{*/
			if (fontsize <= 0.1)
			{
				DrawCircle(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)),
					location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) + addy,
					4, 0xffffff, TRUE);
			}
			else
			{
				//DrawRotaGraphF(location.x + (interval * (digit - 2)) - (i * interval), location.y, fontsize, 0.0, numimg[bufscore % 10], true);
				DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + (interval * (digit - 2)) - (i * interval)
					, location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) + addy
					, 0.5, 0.0, numimg[bufscore % 10], true);
			}
		/*}*/

		bufscore /= 10;
	}

}

void AddScore::Hit(Object* _obj)
{
	if (static_cast<Object*>(_obj)->GetType() == TYPE::_PLAYER)
	{
		flg = false;
		gamemain->AddGameScore(score);
		moveflg = false;
		

		/*if (!moveflg)
		{
			location = startlocation;
			fontsize = 0.8;
			interval = 25.0;
			moveflg = true;

		}*/
	}

	if (static_cast<Object*>(_obj)->GetType() == TYPE::_SOLDIER)
	{
		//int soldier = gamemain->CreateObject(new Soldier);
		int mode = static_cast<Soldier*>(_obj)->CheckMode();
		if (mode == 1)
		{
			static_cast<Soldier*>(_obj)->SetMyScore(score);
			flg = 0;
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

void AddScore::MoveTest(Vector2D PL)
{
	length = PL - location;
	float a = sqrt(pow(length.x, 2) + pow(length.y, 2));
	move.x = ((length.x / a) * speed);
	move.y = ((length.y / a) * speed);

	location += move;
}
