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

void BackGround::Draw(Vector2D loc) const
{
	DrawRotaGraphF(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)),2.0,0.0,images[1],true);
}

void BackGround::LoadImages() {
	int result = LoadDivGraph("Resources/images/background.png", 64, 8, 8, 32, 32, images);
	//int result = 0;
	if (result == -1) {
		printfDx("âÊëúÉGÉâÅ[");
	}
}