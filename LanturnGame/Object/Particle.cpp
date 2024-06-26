#include "Particle.h"
#include "DxLib.h"
#include "../Utility/common.h"
#define _USE_MATH_DEFINES
#include <math.h>


int Particle::images[6][30];
Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Update()
{
	velocity.x = (speed * cosf(angle));
	velocity.y = (speed * sinf(angle));
	location += velocity;

	if (root != nullptr) {
		SetLocation(root->GetLocation() + addloc);
	}
	if (flg) {
		if (lifetime >= 29) {
			if (!loopflg) {
				flg = false;
			}
			else {
				lifetime = 0;
			}
		}
		lifetime++;
	}

}

void Particle::Draw(Vector2D loc, float _distance) const
{
	if (flg) {
		int OldDrawMode;
		int OldDrawParam;
		GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
		if (type == 3)
		{

			SetDrawBright(color[0], color[1], color[2]);
			//SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);

		}
		if (visible)
		{
			DrawRotaGraphF(DrawFromCameraX(location, _distance, loc)
				, DrawFromCameraY(location, _distance, loc)
				, scale * ScaleFromCamera(_distance), imageangle, images[type][lifetime], true);
		}
		if (type == 3)
		{
			SetDrawBright(255, 255, 255);
		}
		SetDrawBlendMode(OldDrawMode, OldDrawParam);
	}

}

void Particle::Draw() const
{
	if (flg) {
		int OldDrawMode;
		int OldDrawParam;
		GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
		if (type == 3)
		{

			SetDrawBright(color[0], color[1], color[2]);
			//SetDrawBlendMode(DX_BLENDMODE_INVSRC, 255);

		}
		if (visible)
		{
			DrawRotaGraphF(location.x,location.y, scale, imageangle, images[type][lifetime], true);
		}
		if (type == 3)
		{
			SetDrawBright(255, 255, 255);
		}
		SetDrawBlendMode(OldDrawMode, OldDrawParam);
	}

}

bool Particle::Getflg() const
{
	return this->flg;
}

int Particle::LoadImages()
{
	int ret = LoadDivGraph("Resources/images/impact.pnacg", 30, 6, 5, 128, 128, images[0]);
	ret = LoadDivGraph("Resources/images/fire.png", 30, 6, 5, 64, 64, images[1]);
	ret = LoadDivGraph("Resources/images/explosion_2.png", 30, 6, 5, 128, 128, images[2]);
	ret = LoadDivGraph("Resources/images/exp.png", 30, 6, 5, 256, 256, images[3]);
	ret = LoadDivGraph("Resources/images/smoke.png", 30, 6, 5, 32, 32, images[4]);
	for (int i = 0; i < 30; i++)
	{
		images[5][i] = LoadGraph("Resources/images/ci-export.png");
	}
	return ret;
}

void Particle::DeleteImages()
{
	DeleteGraph(**images);
}

void Particle::SetAngle(Vector2D loc, Vector2D loc2)
{
	Vector2D temp = loc - loc2;
	angle = atan2f(temp.y, temp.x);
	imageangle = atan2f(temp.y, temp.x);
}

void Particle::SetAngle(float _angle)
{
	angle = ((-90 - _angle) * (float)M_PI) / 180;
	imageangle = -(_angle * (float)M_PI) / 180;
}

void Particle::Init(int _type, SphereCollider * _root, bool _loop, float _scale)
{
	type = _type;
	root = _root;
	loopflg = _loop;
	scale = _scale;
	if (type == 3)
	{
		int rgb = GetRand(2);
		for (int i = 0; i < 3; i++)
		{
			color[i] = 255;
			if (i == rgb)
			{
				color[i] = GetRand(64) * 4;
			}
		}

		//for (int i = 0; i < 3; i++)
		//{
		// 
		//	color[i] = GetRand(20) + 235;
		//}
	}
}

void Particle::SetRootLocation(Vector2D loc)
{
	addloc = loc;
}

void Particle::SetSpeed(float _speed)
{
	speed = _speed;
}

void Particle::SetVisible(bool b)
{
	visible = b;
}