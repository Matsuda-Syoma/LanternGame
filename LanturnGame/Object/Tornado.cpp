#include "Tornado.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include "CameraManager.h"
int Tornado::images;

Tornado::Tornado()
{
	radius = 200;
	map_radius = radius;
}

Tornado::~Tornado()
{
}

void Tornado::Update(GameMain* _g)
{
	if (cnt >= 360) {
		cnt = 0;
	}
	cnt++;
}

void Tornado::Draw(CameraManager* camera) const
{
	//DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(80, 0, 0), 0);
	DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
				 , location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
				 , 1.5f * (1 - ((camera->GetDistance() / DISTANCE_NUM))), -(((DX_PI) / 180) * (cnt * 3)), images, true);
}

void Tornado::Hit(SphereCollider* _sphere)
{
}

int Tornado::LoadImages() {
	images = LoadGraph("Resources/images/tornado_2.png");
	if (images == -1) {
		printfDx("‰æ‘œƒGƒ‰[");
	}
	return images;
}

void Tornado::DeleteImages()
{
	DeleteGraph(images);
}

void Tornado::Initialize(GameMain* _g, int _obj_pos)
{
	gamemain = _g;
	obj_pos = _obj_pos;
	type = (int)TYPE::_TORNADO;
}
