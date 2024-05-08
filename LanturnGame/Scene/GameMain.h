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
	Stage** stage;

	unsigned int game_frametime = 0;
	unsigned int score = 0;
	unsigned int hiscore = 0;
	unsigned int combo = 0;
	float MapSize = GM_MAX_MAPSIZE;
	float MapCloseSpeed = 1;
	int MaxEnemyBomb = GM_MAX_ENEMY_BOMB;

	int life = GM_MAX_LIFE;

	int lifeimage;
	int lifematchimage;
	int closemapimage;
	bool hitmoment = false;
	bool comboflg = false;
	bool resultflg = false;
	bool resultnewflg = false;
	bool SE_HitFlg = false;
	bool SE_NewHitFlg = false;
	bool Soldier_Hit_EX = false;

	__int8 ui_combo_framecount = 0;

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
	void SpawnParticle(int type, SphereCollider * root, bool loop, Vector2D loc, Vector2D loc2, float scale);
	void CameraUpdate();
	void SetCameraShake(int _i);
	void SetMapSize(int i);
	void ChangeMapSize();
	void DrawCombo()const;
	void DrawCloseMap()const;
};

