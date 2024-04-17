#include "BackGround.h"
#include "DxLib.h"
#include "../Utility/common.h"
BackGround::BackGround(Vector2D loc)
{
	location = loc;
	int result = LoadDivGraph("Resources/images/background.png", 64, 8, 8, 32, 32, images);
	if (result == -1) {
		printfDx("âÊëúÉGÉâÅ[");
	}
}

BackGround::~BackGround()
{
}

void BackGround::Init(int i)
{
}

void BackGround::Draw(Vector2D loc) const
{
	DrawRotaGraph(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)),2.0,0.0,images[1],true);
}
