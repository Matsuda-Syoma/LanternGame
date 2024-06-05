#include"Conveyor.h"
#include"Dxlib.h"
#include"../Utility/common.h"

Conveyor::Conveyor() {
	//radius = 100;
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 600.f;
	box.bottom = box.top + 100.f;
}

Conveyor::~Conveyor() {

}

void Conveyor::Update() {
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 600.f;
	box.bottom = box.top + 100.f;
}

void Conveyor::Draw(Vector2D loc, float _distance) const {

	//DrawFromCameraX(location, _distance, loc)
	//	, DrawFromCameraY(location, _distance, loc)
	//DrawBoxAA(box.left + (-loc.x + SCREEN_WIDTH / 2), box.top + (-loc.y + SCREEN_HEIGHT / 2),(box.right + (-loc.x + SCREEN_WIDTH / 2)),(box.bottom + (-loc.y + SCREEN_HEIGHT / 2)), GetColor(80, 20, 0), 1);
	DrawBoxAA(DrawFromCameraX(location, _distance, loc), DrawFromCameraY(location, _distance, loc)
			, DrawFromCameraX(Vector2D(location.x + 600.f,0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 100.f), _distance, loc), GetColor(80, 20, 0), 1);
}

Vector2D Conveyor::GetLocation() const
{
	return location;
}

void Conveyor::SetLocation(Vector2D loc)
{
	this->location = loc;
}