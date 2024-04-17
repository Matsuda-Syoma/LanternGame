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
	speed = 0;	//���x�̏�����
	location = (0.0f,0.0f);	//���W�̏�����

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
	//Move(PL);	//���W���ׂĕ����̈ړ��̌�����ς���	
}

void Soldier::Draw(Vector2D PL)
{
	DrawCircle(location.x + (-PL.x + (SCREEN_WIDTH / 2)), location.y + (-PL.y + (SCREEN_HEIGHT / 2)), radius, 0xffffff, true, true);
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