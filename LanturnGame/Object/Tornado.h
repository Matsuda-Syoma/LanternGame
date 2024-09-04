#pragma once
#include "Object.h"
class GameMain;
class CameraManager;
class Tornado : public Object
{
private:
	static int images;
	int cnt = 0;
	float power = 15.0f;
public:
	Tornado();
	~Tornado();
	static int LoadImages();
	static void DeleteImages();

	void Initialize(GameMain* _g, int _obj_pos) override;
	void Finalize() override {};
	void Update(GameMain* _g) override;
	void Draw(CameraManager* camera)const override;
	void Hit(Object* _obj) override {};                         // “–‚½‚Á‚½‚Ìˆ—
};

