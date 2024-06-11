#include"stage.h"
#include"Dxlib.h"
#include"math.h"
#include"../Utility/common.h"

Stage::Stage() {
	radius = 150;
	radias = 100;
	images = LoadGraph("Resources/images/ice.png", 0);
}

Stage::~Stage() {

}

void Stage::Update() {

}

void Stage::Draw(Vector2D loc, float _distance) const {
	//DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(0, 20, 100), 1);
	DrawRotaGraphF(DrawFromCameraX(location, _distance, loc)
				 , DrawFromCameraY(location, _distance, loc)
				 , 1.0 * ScaleFromCamera(_distance), 0.0, images, true);
}
