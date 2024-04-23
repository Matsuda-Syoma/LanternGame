#include "Particle.h"
#include "DxLib.h"
#include "../Utility/common.h"
#define _USE_MATH_DEFINES
#include <math.h>


int Particle::images[1][30];
Particle::Particle()
{
}

Particle::~Particle()
{
}

void Particle::Update()
{
	if (flg) {
		if (count > 30) {
			count = 0;
			//flg = false;
		}
		count++;
	}
}

void Particle::Draw(Vector2D loc) const
{
	DrawRotaGraphF(location.x + (-loc.x + (SCREEN_WIDTH / 2))
				,  location.y + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0, angle * 180 / M_PI, images[0][count], true);
}

bool Particle::Getflg() const
{
	return this->flg;
}

int Particle::LoadImages()
{
	int ret = LoadDivGraph("Resources/images/impact.png", 30, 6, 5, 128, 128, images[0]);
	return ret;
}

void Particle::SetAngle(Vector2D loc, Vector2D loc2)
{
	Vector2D temp = loc2 - loc;
	angle = atan2(temp.y, temp.x);
	printfDx("%f\n", angle * (180 / M_PI));
}