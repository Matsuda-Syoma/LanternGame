#include "CameraManager.h"
#include "CharaBase.h"
#include <math.h>
#include "../Scene/GameMain.h"

CameraManager::CameraManager()
{
}

CameraManager::~CameraManager()
{
}

void CameraManager::Update(GameMain* _g)
{
	location = _g->GetPlayer()->GetLocation();

	if (InOutCount > 0)
	{
		Distance = 0.0f;
		if (oMin.x != 0.0 || oMin.y != 0.0)
		{
			float CameraDistanceTemp = (GetLength(location, location - oMin) / 2400.0f) * min((InOutCount / 90.0f), 1.0f);
			Distance = CameraDistanceTemp;
		}
		if (oMax.x != 0.0 || oMax.y != 0.0)
		{
			float CameraDistanceTemp = (GetLength(location, location - oMax) / 2400.0f) * min((InOutCount / 90.0f), 1.0f);
			if (Distance < CameraDistanceTemp)
			{
				Distance = CameraDistanceTemp;
			}
		}
		if (Distance > DISTANCE_MAX)
		{
			Distance = DISTANCE_MAX;
		}
		if (oMin.x != 0.0)
		{
			location.x += (oMin.x / 2.0f) * min((InOutCount / 90.0f), 1.0f);
		}
		if (oMin.y != 0.0)
		{
			location.y += (oMin.y / 2.0f) * min((InOutCount / 90.0f), 1.0f);
		}
		if (oMax.x != 0.0)
		{
			location.x += (oMax.x / 2.0f) * min((InOutCount / 90.0f), 1.0f);
		}
		if (oMax.y != 0.0)
		{
			location.y += (oMax.y / 2.0f) * min((InOutCount / 90.0f), 1.0f);
		}
		Vector2D qw = (location * (float)(1.0f - (Distance / DISTANCE_MAX)));
		Vector2D qw2 = (0 * (float)(Distance / DISTANCE_MAX));
		location = qw + qw2;
		
	}
	else
	{
		oMin = 0;
		oMax = 0;
		Distance = 0.0f;
	}

	if (InOutFlg)
	{
		if (InOutCount < 120)
		{
			InOutCount += 5;
		}

	}
	else
	{
		if (InOutCount > 0)
		{
			InOutCount--;
		}
	}

	location.x -= sinf(Index) * (ShakeImpulse.x * Length);
	location.y += sinf(Index) * (ShakeImpulse.y * Length);

	Index /= 1.2;
	if (Index < 0.01)
	{
		Index = 0.0f;
	}
}

// カメラ座標の取得
Vector2D CameraManager::GetLocation() const
{
	return location;
}

float CameraManager::GetDistance() const
{
	return Distance;
}

void CameraManager::SetCameraShake(Vector2D loc, int _index, float _length)
{
	ShakeImpulse = loc;
	Index = DX_PI * _index;
	Length = _length;
}

void CameraManager::SetCameraShake(float _angle, int _index, float _length)
{
	ShakeImpulse.x = cosf(_angle);
	ShakeImpulse.y = sinf(_angle);
	Index = DX_PI * _index;
	Length = _length;
}

void CameraManager::SetObjectDistance(Vector2D loc, bool b)
{
	if (!b)
	{
		oLength = Vector2D(loc.x - location.x, loc.y - location.y);

		// 爆発-カメラのX座標の長さが元の数値より小さいなら保存
		if (oLength.x < oMin.x)
		{
			oMin.x = oLength.x;
		}

		// 爆発-カメラのX座標の長さが元の数値より大きいなら保存
		if (oLength.x >= oMax.x)
		{
			oMax.x = oLength.x;
		}

		// 爆発-カメラのY座標の長さが元の数値より小さいなら保存
		if (oLength.y < oMin.y)
		{
			oMin.y = oLength.y;
		}

		// 爆発-カメラのY座標の長さが元の数値より大きいなら保存
		if (oLength.y >= oMax.y)
		{
			oMax.y = oLength.y;
		}
	}
	else
	{
		oMin = loc;
		oMax = loc;
	}
}

void CameraManager::SetInOutFlg(bool b)
{
	InOutFlg = b;
}