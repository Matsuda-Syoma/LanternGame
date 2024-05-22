#include "AddScore.h"
#include "DxLib.h"
#include "../Utility/common.h"

AddScore::AddScore(Vector2D loc, int _score)
{
	score = _score;
}

AddScore::~AddScore()
{
}

void AddScore::Update(Vector2D loc)
{
}

void AddScore::Draw(Vector2D loc) const
{
	DrawCircleAA(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), 16, 16, 0xffffff, true, true);
}

void AddScore::LoadImages()
{
	LoadDivGraph("Resources/images/number.png", 10, 10, 1, 64, 64, numimg);
}

void AddScore::DeleteImages()
{
	DeleteGraph(*numimg);
}
