#include "Explosion.h"
#include "DxLib.h"
#include "../Utility/common.h"

int Explosion::images[30];

Explosion::Explosion()
{
	radius = 15.0f;
}

Explosion::~Explosion()
{
}

void Explosion::Init(int _size)
{
	size = _size - 2;
}

void Explosion::Update()
{
	// �t���O�������Ă���Ȃ�
	if (flg) {

		// count��15����Ȃ�
		if (count > 15) {

			// �t���O��؂�
			flg = false;
		}

		// count�𑝂₷
		count++;

		// �����蔻��̑傫����count * size�ɂ���
		radius = (float)count * size;
	}
}

void Explosion::Draw(Vector2D loc, float _distance) const
{
	DrawCircleAA(DrawFromCameraX(location, _distance, loc)
				,DrawFromCameraY(location, _distance, loc)
				,radius * ScaleFromCamera(_distance), 16, 0xffffff, true, true);
}

bool Explosion::Getflg() const
{
	return flg;
}

int Explosion::LoadImages() {
	int ret = LoadDivGraph("Resources/images/explosion.png", 30, 6, 5, 128, 128, images);
	return ret;
}

void Explosion::DeleteImages()
{
	DeleteGraph(*images);
}
