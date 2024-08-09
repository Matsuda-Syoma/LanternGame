#pragma once
#include "../Utility/Vector2D.h"
class CameraManager;
class BackGround
{
private:
	static int images[64];
	Vector2D location;
public:
	BackGround(Vector2D loc);
	~BackGround();
	void Init(int i);
	void Draw(CameraManager* camera)const;
	static void LoadImages();
	static void DeleteImages();
};

