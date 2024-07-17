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
}

// �J�������W�̎擾
Vector2D CameraManager::GetLocation() const
{
	return location;
}

float CameraManager::GetDistance() const
{
	return Distance;
}