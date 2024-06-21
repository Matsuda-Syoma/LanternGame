#pragma once
#include "AbstractScene.h"
#include "../Object/Particle.h"
class Title : public AbstractScene
{
private:
	Particle** particle;
	Vector2D bombloc;
	int cursor_menu = 0;
	int maxcursor_menu = 2 - 1;
	int titleimage;
	int titlebombimage;
	int titlenameimage[2];
	int menuimage[4];
	int cursorimage;
	int alphabetimage[26];
	int fireanim = 0;
	int maxfireanim = 90;
	int cursor_fireanim = 0;
	bool isCheck = false;
	int cursor_last = 0;
	bool stickonce = false;

public:
	Title();
	~Title();
	virtual AbstractScene* Update() override;
	void Draw() const override;
	void SpawnParticle(int type, SphereCollider* root, bool loop, Vector2D loc, float angle, float scale, float speed);
};

