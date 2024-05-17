#include"stage.h"
#include"Dxlib.h"
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

void Stage::Draw(Vector2D loc) const {
	//DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(0, 20, 100), 1);
	DrawRotaGraphF(location.x + (-loc.x + (SCREEN_WIDTH / 2)), location.y + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0 + (double)(max(45 - expcnt, 0) / 45.0), 0.0, images, true);
}

void Stage::LoadImages()
{
	//images[0] = LoadGraph("Resources/images/ice.png", 0);
}
