#include "soldier.h"

#include "DxLib.h"

soldier::soldier()
{
	Initialize();
}

soldier::~soldier()
{

}

void soldier::Initialize()
{
	speed = 0;	//���x�̏�����
	location = player->GetLocation() + Vector2D(50.0f, 50.0f);	//���W�̏�����

	//�摜�̓ǂݍ��݂Ɖ摜�����邩�̊m�F
	/*image = LoadGraph();

	if (image == -1)
	{
		throw("����������܂���B\n");
	}*/
}

void soldier::Upadate()
{
	Move();	//���W���ׂĕ����̈ړ��̌�����ς���	
}

void soldier::Draw()
{
	DrawCircle(location.x, location.y, radius, 0x123456, true, true);
	/*DrawGraph(location.x, location.y, image, TRUE);*/
}

void soldier::Move()
{
	PL = player->GetLocation();

	//�v���C���[���E�ɂ���Ȃ�
	if (location.x <= PL.x)
	{
		location.x += speed;
	}
	//�v���C���[�����ɂ���Ȃ�
	if (location.x >= PL.x)
	{
		location.x -= speed;
	}
	//�v���C���[����ɂ���Ȃ�
	if (location.y <= PL.y)
	{
		location.y += speed;
	}
	//�v���C���[�����ɂ���Ȃ�
	if (location.y >= PL.y)
	{
		location.y -= speed;
	}
}

void soldier::finalize()
{
	//�摜�̍폜

}