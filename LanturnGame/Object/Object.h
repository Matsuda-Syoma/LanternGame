#pragma once
#include "SphereCollider.h"
#include <math.h>
class GameMain;
class CameraManager;
class Object : public SphereCollider
{
protected:

	int type = -1;
	int obj_pos = -1;
	int map_radius = radius;
	GameMain* gamemain;

public:

	enum class TYPE : int
	{
		_PLAYER = 0,
		_BOMB,
		_EXPLOSION,
		_SOLDIER,
		_GIMMICK,
	};

	virtual void Initialize(GameMain* _g, int _obj_pos) = 0;				// 
	virtual void Finalize() = 0;							// 
	virtual void Update(GameMain* _g) = 0;					// 更新処理
	virtual void Draw(CameraManager* camera) const =	0;	// 描画処理
	virtual void Hit(SphereCollider* _sphere) = 0;			// ヒットしたときに起きる処理

	TYPE GetType()const { return (TYPE)type; }

	int GetMapRadius() const { return map_radius; }

	bool SpawnCheck(Object* _obj)
	{
		if (!HitSphere(_obj))
		{
			return true;
		}
		return false;
	}
	float GetLength(Vector2D loc)
	{
		return sqrtf(powf((loc.x - location.x), 2) + powf((loc.y - location.y), 2));
	}
};