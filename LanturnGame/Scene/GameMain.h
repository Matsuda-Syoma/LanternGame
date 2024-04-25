#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
#include "../Object/Bomb.h"
#include "../Object/Explosion.h"
#include "../Object/Player.h"
#include "../Object/BackGround.h"
#include "../Object/Soldier.h"
#include "../Object/Particle.h"
#include "../Utility/common.h"
#include "../Object/stage.h"
class GameMain : public AbstractScene
{
private:
	Bomb** bomb;
	Explosion** explosion;
	Player* player;
	Soldier** soldier;
	BackGround** background;
	Particle** particle;
	Stage* stage;

	unsigned int game_frametime = 0;
	unsigned int score = 0;
	unsigned int ratio = 0;
	float MapSize = GM_MAX_MAPSIZE;
	float MapCloseSpeed = 1;
	int MaxEnemyBomb = GM_MAX_ENEMY_BOMB;

	int life = 3;
	int lifeimage;
	int lifematchimage;
	bool hitmoment = false;
	bool ratioflg = false;
	bool resultflg = false;
	bool SE_HitFlg = false;
	bool SE_NewHitFlg = false;

	__int8 ui_ratio_framecount = 0;

	int CamerashakeCount = 0;
	int Camerashake = 0;

	Vector2D ev;
	float l;

public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	void Draw() const override;
	void Game();	
	void SpawnExplosion(Vector2D loc);
	void SpawnParticle(int i, Vector2D loc, Vector2D loc2);
	void CameraUpdate();
	void SetCameraShake(int _i);
	void SetMapSize(int i);
};

