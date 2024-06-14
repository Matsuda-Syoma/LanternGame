#include"Conveyor.h"
#include"Dxlib.h"
#include"../Utility/common.h"

Conveyor::Conveyor() {
	//radius = 100;
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + 600.f;
	box.bottom = box.top + 100.f;
	outimage = LoadGraph("Resources/images/conv_out.png", 0);
	out2image = LoadGraph("Resources/images/conv_out2.png", 0);
	inimage = LoadGraph("Resources/images/conv_in.png", 0);
}

Conveyor::~Conveyor() {

}

void Conveyor::Update() {
	box.left = location.x;
	box.top = location.y;

	if (cnt >= 58)
	{
		cnt = 0;
	}
	cnt++;
	box.right = box.left + width;
	box.bottom = box.top + height;
}


void Conveyor::Draw(Vector2D loc, float _distance) const {

	//DrawFromCameraX(location, _distance, loc)
	//	, DrawFromCameraY(location, _distance, loc)
	//DrawBoxAA(box.left + (-loc.x + SCREEN_WIDTH / 2), box.top + (-loc.y + SCREEN_HEIGHT / 2),(box.right + (-loc.x + SCREEN_WIDTH / 2)),(box.bottom + (-loc.y + SCREEN_HEIGHT / 2)), GetColor(80, 20, 0), 1);
	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 300.f,0.0f), _distance, loc)
				 , DrawFromCameraY(Vector2D(location.y + 50.f), _distance, loc), 1.0 * ScaleFromCamera(_distance),0.0,outimage, 1);

	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 300.f + (float)cnt, 0.0f), _distance, loc)
		, DrawFromCameraY(Vector2D(location.y + 50.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, inimage, 1);

	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 300.f, 0.0f), _distance, loc)
		, DrawFromCameraY(Vector2D(location.y + 50.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, out2image, 1);
}

Vector2D Conveyor::GetLocation() const
{
	return location;
}

void Conveyor::SetLocation(Vector2D loc)
{
	this->location = loc;
}

float Conveyor::GetScale(int i)
{
	float ret = 0.0f;
	switch (i)
	{
	case 0:
		ret = width;
		break;
		ret = height;
	case 1:
		break;
	}
	return ret;
}