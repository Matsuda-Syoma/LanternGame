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
	images = LoadGraph("Resources/images/conveyor1.png", 0);
}


Conveyor::~Conveyor() {

}

void Conveyor::Initialize(GameMain* _g, int _obj_pos)
{
	gamemain = _g;
	obj_pos = _obj_pos;
	type = (int)TYPE::_CONVEYER;

	boxcol = true;
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

	if (scroll <= 55)
	{
		scroll = scroll + 2;
	}
	else {
		scroll = 0;
	}
	finalimage = DerivationGraph(scroll, 0, 600, 100, images);

}

void Conveyor::Draw(CameraManager* camera) const
{
	DrawBoxAA(box.left * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
		, box.top * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
		, box.right * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
		, box.bottom * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
		, 0x00ffff, true);

	DrawRotaGraphF((box.left + (width / 2) + scroll) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
				 , (box.top + (height / 2)) * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
				 , 1.0f * (1.0f - ((camera->GetDistance()))), 0.0, finalimage, true);


}
