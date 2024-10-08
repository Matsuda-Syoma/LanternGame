#include"Conveyor.h"
#include"Dxlib.h"
#include"../Utility/common.h"
#include"CameraManager.h"

Conveyor::Conveyor() 
{
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + width;
	box.bottom = box.top + height;
	images = LoadGraph("Resources/images/n_conv.png", 0);
}


Conveyor::~Conveyor() {

}

void Conveyor::Initialize(GameMain* _g, int _obj_pos)
{
	gamemain = _g;
	obj_pos = _obj_pos;
	type = (int)TYPE::_CONVEYER;

	boxcol = true;
	SetAngle(GetRand(3));
}

//void Conveyor::Update() {
//	box.left = location.x;
//	box.top = location.y;
//	box.right = box.left + width;
//	box.bottom = box.top + height;
//
//	if(scroll <= 55)
//	{
//		scroll = scroll + 2 ;
//	}
//	else {
//		scroll = 0;
//	}
//
//}


//void Conveyor::Draw(Vector2D loc, float _distance) const {
//
//	//DrawFromCameraX(location, _distance, loc)
//	//	, DrawFromCameraY(location, _distance, loc)
//	//DrawBoxAA(box.left + (-loc.x + SCREEN_WIDTH / 2), box.top + (-loc.y + SCREEN_HEIGHT / 2),(box.right + (-loc.x + SCREEN_WIDTH / 2)),(box.bottom + (-loc.y + SCREEN_HEIGHT / 2)), GetColor(80, 20, 0), 1);
//	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 300.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 50.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_belt, 1);
//	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + (scroll + 300.f) , 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 50.f), _distance, loc), 1.0 * ScaleFromCamera(_distance), 0.0, image_line, 1);
//	DrawRotaGraphF(DrawFromCameraX(Vector2D(location.x + 300.f, 0.0f), _distance, loc), DrawFromCameraY(Vector2D(location.y + 50.f), _distance, loc), 1.0 * ScaleFromCamera(_distance),0.0,image_con, 1);
//}

void Conveyor::Update(GameMain* _g)
{
	box.left = location.x;
	box.top = location.y;
	box.right = box.left + width;
	box.bottom = box.top + height;

	if (scroll <= 254)
	{
		scroll = scroll + 1;
	}
	else {
		scroll = 0;
	}
	finalimage[0] = DerivationGraph(0, 0, 512 - (scroll * 2), 128, images);
	finalimage[2] = DerivationGraph(512 - (scroll * 2), 0, 512, 128, images);

}

void Conveyor::Draw(CameraManager* camera) const
{

	switch (angle)
	{
	case 0:
		// �E
		DrawRotaGraphF((box.left + (width / 2) + scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.top + (height / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), 0.0, finalimage[0], true);
		DrawRotaGraphF((box.left + (scroll)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.top + (height / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), 0.0, finalimage[2], true);
		break;

	case 1:
		// ��
		DrawRotaGraphF((box.left + (width / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.top + (height / 2) + scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), DX_PI / 2, finalimage[0], true);
		DrawRotaGraphF((box.left + (width / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.top + scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), DX_PI / 2, finalimage[2], true);
		break;

	case 2:
		// ��
		DrawRotaGraphF((box.right - (width / 2) + (-scroll)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.top + (height / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), DX_PI, finalimage[0], true);
		DrawRotaGraphF((box.right + -scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.top + (height / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), DX_PI, finalimage[2], true);
		break;

	case 3:
		// ��
		DrawRotaGraphF((box.left + (width / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.bottom - (height / 2) + -scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), -DX_PI / 2, finalimage[0], true);
		DrawRotaGraphF((box.left + (width / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
			, (box.bottom + -scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
			, 1.0f * (1.0f - ((camera->GetDistance()))), -DX_PI / 2, finalimage[2], true);
		break;

	default:
		break;
	}

	//DrawBoxAA(box.left * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
	//	, box.top * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
	//	, box.right * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
	//	, box.bottom * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
	//	, 0x00ffff, false, 3.0f);
}

void Conveyor::SetAngle(int i)
{
	angle = i % 4;
	if (angle % 2 == 1)
	{
		int tempwidth = width;
		int tempheight = height;
		width = tempheight;
		height = tempwidth;
	}
}

void Conveyor::Hit(Object* _obj)
{

	Vector2D addloc;
	float power = 2.0f;
	if (angle == 0)
	{
		addloc = Vector2D(power, 0);
	}
	if (angle == 1)
	{
		addloc = Vector2D(0, power);
	}
	if (angle == 2)
	{
		addloc = Vector2D(-power, 0);
	}
	if (angle == 3)
	{
		addloc = Vector2D(0, -power);
	}

	switch (_obj->GetType())
	{
	case TYPE::_PLAYER:
	case TYPE::_BOMB:
	case TYPE::_SOLDIER:
		_obj->SetLocation(_obj->GetLocation() + addloc);
		break;

	default:
		break;
	}
}

Vector2D Conveyor::GetScale() const
{
	return Vector2D(width, height);
}
