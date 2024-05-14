#include "Tornado.h"
#include "DxLib.h"
#include "../Utility/common.h"
Tornado::Tornado()
{
	radius = 200;
}

Tornado::~Tornado()
{
}

void Tornado::Update()
{
}

void Tornado::Draw(Vector2D loc) const
{
	DrawCircleAA(location.x + (-loc.x + SCREEN_WIDTH / 2), location.y + (-loc.y + SCREEN_HEIGHT / 2), radius, 16, GetColor(80, 0, 0), 1);
}
