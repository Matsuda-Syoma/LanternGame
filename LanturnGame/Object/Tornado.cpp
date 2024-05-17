#include "Tornado.h"
#include "DxLib.h"
#include "../Utility/common.h"

int Tornado::images;

Tornado::Tornado()
{
	radius = 200;
}

Tornado::~Tornado()
{
}

void Tornado::Update()
{
	if (cnt > 60) {
		cnt = 0;
	}
	cnt++;
}

void Tornado::Draw(Vector2D loc) const
{
	//DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(80, 0, 0), 1);
	DrawRotaGraphF(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0, (cnt / DX_PI) / 10, images, true);
}

int Tornado::LoadImages() {
	images = LoadGraph("Resources/images/tornado.png");
	//int result = 0;
	if (images == -1) {
		printfDx("âÊëúÉGÉâÅ[");
	}
	return images;
}

void Tornado::DeleteImages()
{
	DeleteGraph(images);
}
