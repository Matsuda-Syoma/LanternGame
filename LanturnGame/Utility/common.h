#pragma once

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define SCREEN_COLORBIT 32

#define FRAMERATE 60.0
#define UPDATETIME 800

#define GM_MAX_LIFE 50

#define GM_MAX_ENEMY_BOMB 100
#define GM_MAX_EFFECT_EXPLOSION 100
#define GM_MAX_PARTICLE 1000
#define GM_MAX_ICEFLOOR 2
#define GM_MAX_CONVEYOR 3

#define GM_MAX_TORNADO 3

#define GM_MAX_MAPSIZE 1500
#define GM_MIN_MAPSIZE 320


#define GM_MAX_ENEMY_SOLDIER 3

#include "Vector2D.h"
#include <math.h>
static float GetLength(Vector2D loc, Vector2D loc2)
{
	return sqrtf(powf((loc2.x - loc.x), 2) + powf((loc2.y - loc.y), 2));
}