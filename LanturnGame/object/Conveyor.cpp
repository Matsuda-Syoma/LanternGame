#include"Conveyor.h"
#include"Dxlib.h"
#include"../Utility/common.h"

Conveyor::Conveyor() {
	//radius = 100;
}

Conveyor::~Conveyor() {

}

void Conveyor::Update() {

}

void Conveyor::Draw(Vector2D loc) const {
	DrawBoxAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2),(location.x + (-loc.x + SCREEN_WIDTH / 2) + 400),(location.y + (-loc.y + SCREEN_HEIGHT / 2) + 100), GetColor(80, 20, 0), 1);
}