#include "BackGround.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include "CameraManager.h"

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

void BackGround::Draw(CameraManager* camera) const
{
	// •`‰æ
	DrawRotaGraphF((location.x * (64.0f - (camera->GetDistance() * 32.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
				 , (location.y * (64.0f - (camera->GetDistance() * 32.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2)), 2.032 - camera->GetDistance(), 0.0, images[9], true);
}

void BackGround::LoadImages() {
	int result = LoadDivGraph("Resources/images/background.png", 64, 8, 8, 32, 32, images);
	if (result == -1) {
		printfDx("‰æ‘œƒGƒ‰[");
	}
}

void BackGround::DeleteImages()
{
	DeleteGraph(*images);
}
