#include"Conveyor_y.h"
#include"Dxlib.h"
#include"../Utility/common.h"

Conveyor_y::Conveyor_y():scroll(0) {
	//radius = 100;
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 100.f;
	box.bottom = box.top + 600.f;
	images = LoadGraph("Resources/images/conveyorY.png", 0);
	image_con = LoadGraph("Resources/images/conveyor5.png", 0);
	image_belt = LoadGraph("Resources/images/conveyor7.png", 0);
	image_line = LoadGraph("Resources/images/conveyor6.png", 0);
	image_up = LoadGraph("Resources/images/conveyor6_2.png", 0);
}

Conveyor_y::~Conveyor_y() {

}

void Conveyor_y::Update() {
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 100.f;
	box.bottom = box.top + 600.f;

	if (scroll <= 56)
	{
		scroll = scroll + 2;
	}
	else
	{
		scroll = 0;
	}
}


void Conveyor_y::Draw(Vector2D loc, float _distance) const {

	//DrawFromCameraX(location, _distance, loc)
	//	, DrawFromCameraY(location, _distance, loc)
	//DrawBoxAA(box.left + (-loc.x + SCREEN_WIDTH / 2), box.top + (-loc.y + SCREEN_HEIGHT / 2),(box.right + (-loc.x + SCREEN_WIDTH / 2)),(box.bottom + (-loc.y + SCREEN_HEIGHT / 2)), GetColor(80, 20, 0), 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 50.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 300.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_belt, 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 50.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + (scroll + 300.f)), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_line, 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 50.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 300.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_con, 1);
}

void Conveyor_y::Draw_up(Vector2D loc, float _distance) const {

	//DrawFromCameraX(location, _distance, loc)
	//	, DrawFromCameraY(location, _distance, loc)
	//DrawBoxAA(box.left + (-loc.x + SCREEN_WIDTH / 2), box.top + (-loc.y + SCREEN_HEIGHT / 2),(box.right + (-loc.x + SCREEN_WIDTH / 2)),(box.bottom + (-loc.y + SCREEN_HEIGHT / 2)), GetColor(80, 20, 0), 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 50.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 300.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_belt, 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 50.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + (300.f - scroll)), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_up, 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 50.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 300.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_con, 1);
}

Vector2D Conveyor_y::GetLocation() const
{
	return location;
}

void Conveyor_y::SetLocation(Vector2D loc)
{
	this->location = loc;
}