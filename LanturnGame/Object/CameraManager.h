#pragma once
#include "../Utility/Vector2D.h"
#include "../Utility/common.h"
class GameMain;

class CameraManager
{
private:
	Vector2D location;
	float Distance = 0.0f;
	Vector2D ShakeImpulse = 0.0f;
	Vector2D Speed = 0.0f;
	float Index = 0.0f;
	float Length = 0.0f;
	bool InOutFlg = false;
	int InOutCount = 0;
	Vector2D oLength, oMin, oMax;
public:
	CameraManager();
	~CameraManager();
	void Update(GameMain* _g);

	Vector2D GetLocation() const;
	float GetDistance() const;

	void SetCameraShake(Vector2D loc, int _index, float _length);

	void SetCameraShake(float _angle, int _index, float _length);

	// ç¿ïWÅAå≈íËïœçXÇ©
	void SetObjectDistance(Vector2D loc, bool b);

	void SetInOutFlg(bool b);


};