#pragma once
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_COLORBIT 32

#define FRAMERATE 60.0
#define UPDATETIME 800

#define GM_MAX_LIFE 5

#define GM_MAX_ENEMY_BOMB 200
#define GM_MAX_EFFECT_EXPLOSION 200
#define GM_MAX_PARTICLE 1000
#define GM_MAX_ICEFLOOR 2
#define GM_MAX_CONVEYOR 3

#define GM_MAX_TORNADO 7
#define GM_MAX_ADDSCORE 100
#define GM_MAX_COMBOEND 3

#define GM_MAX_MAPSIZE 1500
#define GM_MIN_MAPSIZE 320


#define GM_MAX_ENEMY_SOLDIER 3

#include "Vector2D.h"
#include <math.h>
static float GetLength(Vector2D loc, Vector2D loc2)
{
	return sqrtf(powf((loc2.x - loc.x), 2) + powf((loc2.y - loc.y), 2));
}

static float Normalize(Vector2D loc, Vector2D loc2)
{
	float rx = loc2.x - loc.x;
	float ry = loc2.y - loc.y;
	return atan2f(rx, ry) * -180.0f / 3.14159265358979323846f;
}

static int RandType(int rnd)
{
	// 3,1,1,3,2
	int percent = 0;
	int addpercent[5] = { 10,10,10,40,30 };
	for (int i = 0; i < 5; i++)
	{
		percent += addpercent[i];
		if (rnd < percent)
		{
			return i;
		}
	}
	return 0;
}

//Vector2D temp = loc - loc2;
//angle = atan2f(temp.y, temp.x);
//imageangle = atan2f(temp.y, temp.x);