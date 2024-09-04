#include"stage.h"
#include"Dxlib.h"
#include"math.h"
#include"../Utility/common.h"
#include "CameraManager.h"

Stage::Stage() {
	radius = 150;
	map_radius = radius;
	images = LoadGraph("Resources/images/ice.png", 0);
}

Stage::~Stage() {

}


void Stage::Initialize(GameMain* _g, int _obj_pos)
{
	gamemain = _g;
	obj_pos = _obj_pos;
	type = (int)TYPE::_ICEFLOOR;
}

void Stage::Update(GameMain* _g)
{
}

void Stage::Draw(CameraManager* camera) const
{
	DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
				,  location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
				,  1.0f * (1 - ((camera->GetDistance() / DISTANCE_NUM))), 0.0, images, true);
	DrawCircleAA(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
		, location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
		, radius, 16, 0xffffff, false, 3.0f);
}
