#include"stage.h"
#include"Dxlib.h"
#include"../Utility/common.h"

Stage::Stage() {
	radius = 150;
	radias = 100;
}

Stage::~Stage() {

}

void Stage::Update() {

}

void Stage::Draw(Vector2D loc) const {
	DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(0, 20, 100), 1);
}