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
}

void AddScore::Draw(CameraManager* camera) const
{
	int bufscore = score;
	for (int i = 0; i < digit; i++) {
			//DrawRotaGraphF(DrawFromCameraX(location, _distance, loc) + (20 * (digit - 2)) - (i * 20)
			//	, DrawFromCameraY(location, _distance, loc) + addy, 0.5, 0.0, numimg[bufscore % 10], true);

			DrawRotaGraphF(viewlocation.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2)) + (20 * (digit - 2)) - (i * 20)
						 , viewlocation.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)) + addy
						 , 0.5, 0.0, numimg[bufscore % 10], true);

		bufscore /= 10;
	}
}

void AddScore::Hit(SphereCollider* _sphere)
{
	if (static_cast<Object*>(_sphere)->GetType() == TYPE::_PLAYER)
	{
		flg = false;
	}
}
