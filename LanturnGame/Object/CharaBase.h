#pragma once
#include "Object.h"
class CharaBase : public Object
{
protected:
	float speed = 0;
	float MapSize = 1000;
	Vector2D movetoloc;
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

	void Initialize(int _obj_pos) override {};
	void Finalize() override {};

	void Update(GameMain* _g) override {};
	void Draw(CameraManager* camera)const override {};

	void Hit(SphereCollider* _sphere) override {};                         // “–‚½‚Á‚½‚Ìˆ—
};