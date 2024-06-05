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
	if (cnt >= 60) {
		cnt = 0;
	}
	cnt++;
}

void Tornado::Draw(Vector2D loc, float _distance) const
{
	//DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(80, 0, 0), 0);
	DrawRotaGraphF(DrawFromCameraX(location, _distance, loc)
				 , DrawFromCameraY(location, _distance, loc)
				 , 1.5 * ScaleFromCamera(_distance), (((DX_PI) / 180) * (cnt * 3)), images, true);
}

int Tornado::LoadImages() {
	images = LoadGraph("Resources/images/tornado_2.png");
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
