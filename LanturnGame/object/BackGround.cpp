#include "BackGround.h"
#include "DxLib.h"
#include "../Utility/common.h"

int BackGround::images[64];

BackGround::BackGround(Vector2D loc)
{
	location = loc;
}

BackGround::~BackGround()
{
}

void BackGround::Init(int i)
{
}

void BackGround::Draw(Vector2D loc, float _distance) const
{
	DrawRotaGraphF((location.x * (64. - (_distance * 32.))) + (-loc.x + (SCREEN_WIDTH / 2)), (location.y * (64. - (_distance * 32.))) + (-loc.y + (SCREEN_HEIGHT / 2)), 2.032 - _distance, 0.0, images[9], true);
}

void BackGround::LoadImages() {
	int result = LoadDivGraph("Resources/images/background.png", 64, 8, 8, 32, 32, images);
	//int result = 0;
	if (result == -1) {
		printfDx("âÊëúÉGÉâÅ[");
	}
}

void BackGround::DeleteImages()
{
	DeleteGraph(*images);
}
