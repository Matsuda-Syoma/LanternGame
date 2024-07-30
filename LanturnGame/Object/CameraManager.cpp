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
	//float scale = 0.3;		// 相対ベクターを100分の1に縮尺するための変数.
	//float damp = 0.65;		// 減衰ベクター.
	//location = _g->GetPlayer()->GetLocation();
	//ShakeImpulse.x = scale * ShakeImpulse.x;
	//ShakeImpulse.y = scale * ShakeImpulse.y;
	//Speed.x = damp * (Speed.x + ShakeImpulse.x);
	//Speed.y = damp * (Speed.y + ShakeImpulse.y);
	//location += Speed;
	//if (fabsf(Speed.x) < 0.01)
	//{
	//	Speed.x = 0.0f;
	//}
	//if (fabsf(Speed.y) < 0.01)
	//{
	//	Speed.y = 0.0f;
	//}

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
