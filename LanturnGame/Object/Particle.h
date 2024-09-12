#pragma once
#include "SphereCollider.h"
class GameMain;
class CameraManager;
class Particle : public SphereCollider
{
private:
	int obj_pos = -1;
	bool flg = true;
	bool visible = true;
	unsigned int type = 0;
	static int images[][30];
	unsigned int lifetime = 0;
	unsigned int maxlifetime = 30;
	float imageangle = 0.f;
	float angle = 0.f;
	float speed = 0.f;
	int alpha = 255;
	bool changealphaflg = false;
	SphereCollider* root = nullptr;
	bool loopflg = false;
	float scale = 1.f;
	Vector2D addloc = 0;
	Vector2D velocity = 0.f;
	int color[3] = {};
public:
	Particle();
	~Particle();                       // ìñÇΩÇ¡ÇΩéûÇÃèàóù

	static int LoadImages();
	static void DeleteImages();

	void Update(GameMain* _g);
	void Draw(CameraManager* camera)const;
	void Draw() const;
	bool Getflg()const;
	void SetAngle(Vector2D loc, Vector2D loc2);
	void SetAngle(float _angle);
	void Init(int _type, int _obj_pos);
	void SetRoot(SphereCollider * _root);
	void SetLoop(bool b);
	void SetLocation(Vector2D loc);
	void SetScale(float _scale);
	void SetRootLocation(Vector2D loc);

	void SetSpeed(float _speed);

	void SetVisible(bool b);

	void SetAlpha(int i);

	void SetChangeAlphaFlg(bool b);

	void SetLifeTime(int i);

};

