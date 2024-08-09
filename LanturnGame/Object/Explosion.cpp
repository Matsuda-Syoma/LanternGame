#include "Explosion.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include "../Scene/GameMain.h"
#include "CameraManager.h"

int Explosion::images[30];

Explosion::Explosion()
{
	type = (int)TYPE::_EXPLOSION;
	radius = 15.0f;
}

Explosion::~Explosion()
{
}

void Explosion::Initialize(GameMain* _g, int _obj_pos)
{
	CharaBase::Initialize(_g, _obj_pos);
}

void Explosion::Finalize()
{
}

void Explosion::Hit(SphereCollider* _sphere)
{
}

void Explosion::Init(int _size)
{
	size = _size - 2;
}

void Explosion::Update(GameMain* _g)
{
	// フラグがたっているなら
	if (flg) {

		// countが15より上なら
		if (count > 15) {

			// フラグを切る
			flg = false;
			_g->DeleteObject(this, obj_pos);
		}

		// countを増やす
		count++;

		// 当たり判定の大きさをcount * sizeにする
		radius = (float)count * size;
	}
}

void Explosion::Draw(CameraManager* camera) const
{
	DrawCircleAA(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
				,location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
				,radius * (1 - (camera->GetDistance())), 16, 0xffffff, false);
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
