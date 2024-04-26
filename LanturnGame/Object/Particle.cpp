#include "Particle.h"
#include "DxLib.h"
#include "../Utility/common.h"
#define _USE_MATH_DEFINES
#include <math.h>


int Particle::images[2][30];
Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Update()
{
	if (root != nullptr) {
		SetLocation(root->GetLocation());
	}
	if (flg) {
		if (count >= 29) {
			if (!loopflg) {
				flg = false;
			}
			else {
				count = 0;
			}
		}
		count++;
	}
}

void Particle::Draw(Vector2D loc) const
{
	if (flg) {
		DrawRotaGraphF(location.x + (-loc.x + (SCREEN_WIDTH / 2))
					,  location.y + (-loc.y + (SCREEN_HEIGHT / 2)), scale, angle, images[type][count], true);
	}

}

bool Particle::Getflg() const
{
	return this->flg;
}

int Particle::LoadImages()
{
	int ret = LoadDivGraph("Resources/images/impact.png", 30, 6, 5, 128, 128, images[0]);
	ret = LoadDivGraph("Resources/images/fire.png", 30, 6, 5, 64, 64, images[1]);
	return ret;
}

void Particle::SetAngle(Vector2D loc, Vector2D loc2)
{
	Vector2D temp = loc - loc2;
	angle = atan2(temp.y, temp.x);
}

void Particle::Init(int _type, SphereCollider * _root, bool _loop, float _scale)
{
	type = _type;
	root = _root;
	loopflg = _loop;
	scale = _scale;
}

bool Particle::GetRootFlg()
{
	return this->rootflg;
}
