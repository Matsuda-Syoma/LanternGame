#include"Conveyor.h"
#include"Dxlib.h"
#include"../Utility/common.h"

Conveyor::Conveyor() {
	//radius = 100;
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 600.f;
	box.bottom = box.top + 100.f;
	images = LoadGraph("Resources/images/conveyor.png", 0);
}

Conveyor::~Conveyor() {

}

void Conveyor::Update() {
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 600.f;
	box.bottom = box.top + 100.f;
}

void Conveyor::Draw(Vector2D loc) const {
	DrawRotaGraphF(box.left + (-loc.x + SCREEN_WIDTH / 2) + 300 , box.top + (-loc.y + SCREEN_HEIGHT / 2) + 50, 1.0 + (double)(max(45 - expcnt, 0) / 45.0), 0.0, images, true);
	//DrawBoxAA(box.left + (-loc.x + SCREEN_WIDTH / 2), box.top + (-loc.y + SCREEN_HEIGHT / 2),(box.right + (-loc.x + SCREEN_WIDTH / 2)),(box.bottom + (-loc.y + SCREEN_HEIGHT / 2)), GetColor(80, 20, 0), 1);
}

Vector2D Conveyor::GetLocation() const
{
	return location;
}

void Conveyor::SetLocation(Vector2D loc)
{
	this->location = loc;
}