#pragma once
#include "Object.h"
class CharaBase : public Object
{
protected:
	unsigned int lifetime = 0;
	float speed = 0;
	float MapSize = 1000;
	bool spawnev = false;
	Vector2D movetoloc;
	Vector2D exvelocity;
public:
	virtual void GetMapSize(float i) {
		MapSize = i;
	}
	virtual Vector2D GetMoveToLocation() {
		return this->movetoloc;
	}
	virtual void SetMoveToLocation(Vector2D loc) {
		movetoloc = loc;
	}

	void Initialize(GameMain* _g, int _obj_pos) override { gamemain = _g; obj_pos = _obj_pos; };
	void Finalize() override {};

	void Update(GameMain* _g) override;
	void Draw(CameraManager* camera)const override;

	void Hit(Object* _obj) override {};                         // “–‚½‚Á‚½‚Ìˆ—

	void SetEXVelocity(Vector2D loc){ exvelocity = loc; }

	void SpawnEvent();
};