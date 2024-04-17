#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
#include "../Object/Bomb.h"
#include "../Object/Explosion.h"
#include "../Object/Player.h"
#include "../Object/BackGround.h"
#include "../Object/Soldier.h"
class GameMain : public AbstractScene
{
private:
	Bomb** bomb;
	Explosion** explosion;
	Player* player;
	Soldier* soldier;
	BackGround** background;

	unsigned int game_frametime = 0;
	unsigned int score = 0;
	unsigned int ratio = 0;

	int life = 3;
	int lifeimage;
	int lifematchimage;
	bool hitmoment = false;
	bool ratioflg = false;

	__int8 ui_ratio_framecount = 0;

	int CamerashakeCount = 0;
	int Camerashake = 0;

public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	void Draw() const override;
	void Game();	
	void SpawnExplosion(Vector2D loc);
	void CameraUpdate();
	void SetCameraShake(int _i);
};

