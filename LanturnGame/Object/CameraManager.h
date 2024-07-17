#pragma once
#include "../Utility/Vector2D.h"
#include "../Utility/common.h"
class GameMain;

class CameraManager
{
private:
	Vector2D location;
	float Distance = 0.0f;
public:
	CameraManager();
	~CameraManager();
	void Update(GameMain* _g);

	Vector2D GetLocation() const;
	float GetDistance() const;

};