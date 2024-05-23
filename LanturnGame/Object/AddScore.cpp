#include "AddScore.h"
#include "DxLib.h"
#include "../Utility/common.h"

int AddScore::numimg[10];

AddScore::AddScore(Vector2D loc, int _score)
{
	location = loc;
	score = _score;
	int bufscore = score;
	while (bufscore != 0)
	{
		bufscore /= 10;
		digit++;
	}
}

AddScore::~AddScore()
{
}

void AddScore::Update(Vector2D loc)
{
	// 左に出ないように
	viewlocation = location;

	if (loc.x - viewlocation.x > SCREEN_WIDTH / 2.f)
	{
		viewlocation.x = loc.x - SCREEN_WIDTH / 2.f;
	}
	// 右に出ないように
	if (loc.x - viewlocation.x < -SCREEN_WIDTH / 2.f)
	{
		viewlocation.x = loc.x - -SCREEN_WIDTH / 2.f;
	}
	// 上に出ないように
	if (loc.y - viewlocation.y > SCREEN_HEIGHT / 2.1f)
	{
		viewlocation.y = loc.y - SCREEN_HEIGHT / 2.1f;
	}
	// 下に出ないように
	if (loc.y - viewlocation.y < -SCREEN_HEIGHT / 2.f)
	{
		viewlocation.y = loc.y - -SCREEN_HEIGHT / 2.f;
	}

	if (cnt < 7)
	{
		addy += -3;
	}
	else if(cnt < 7 * 2)
	{
		addy += 3;
	}

	if (cnt > 30)
	{
		flg = false;
	}
	cnt++;
	
}

void AddScore::Draw(Vector2D loc) const
{

	int bufscore = score;
	for (int i = 0; i < digit; i++) {
		//DrawRotaGraphF((SCREEN_WIDTH / 2) + 16 - (i * 32) + location.x, (SCREEN_HEIGHT / 2) + 96 + location.y, .5, 0.0, numimg[bufcombo % 10], true);
		DrawRotaGraphF(viewlocation.x + (-loc.x + (SCREEN_WIDTH / 2)) + (20 * (digit - 2)) - (i * 20), viewlocation.y + (-loc.y + (SCREEN_HEIGHT / 2)) + addy, .5, 0.0, numimg[bufscore % 10], true);
		bufscore /= 10;
	}

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
