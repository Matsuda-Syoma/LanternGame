#include "soldier.h"
#include "../common.h"
#include "DxLib.h"

Soldier::Soldier()
{
	Initialize();
}

Soldier::~Soldier()
{

}

void Soldier::Initialize()
{
	speed = 2;	//���x�̏�����
	location = (100.0f,100.0f);	//���W�̏�����

	//�摜�̓ǂݍ��݂Ɖ摜�����邩�̊m�F
	/*image = LoadGraph();

	if (image == -1)
	{
		throw("����������܂���B\n");
	}*/
}

void Soldier::Upadate(Vector2D PL)
{
	length = location - PL;

	if (length.x <= 0)
	{
		location.x += speed;
	}
	if (length.x >= 0)
	{
		location.x -= speed;
	}
	if (length.y <= 0)
	{
		location.y += speed;
	}
	if (length.y >= 0)
	{
		location.y -= speed;
	}	
}

void Soldier::Draw(Vector2D PL)
{
	DrawCircle(location.x + (-PL.x + (SCREEN_WIDTH / 2)), location.y + (-PL.y + (SCREEN_HEIGHT / 2)), radius, 0xf14f5f, true, true);
	/*DrawGraph(location.x, location.y, image, TRUE);*/
}

//void Soldier::Move(Vector2D PL)
//{
//	length = location - PL;
//
//	if (length.x <= 0)
//	{
//		location.x += speed;
//	}
//	if (length.x >= 0)
//	{
//		location.x -= speed;
//	}
//	if (length.y <= 0)
//	{
//		location.y += speed;
//	}
//	if (length.y >= 0)
//	{
//		location.y -= speed;
//	}
//
//}

void Soldier::finalize()
{
	//�摜�̍폜

}