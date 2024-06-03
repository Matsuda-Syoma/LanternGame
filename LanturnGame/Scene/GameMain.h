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
#include "../Object/Conveyor.h"
#include "../Object/Tornado.h"
#include "../Object/ComboEnd.h"
#include "../Utility/TextDisp.h"
#include "../Object/AddScore.h"
#include "../Utility/UserData.h"
#include "../Scene/Setting.h"

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
	Conveyor** conveyor;
	Tornado** tornado;
	ComboEnd** comboend;
	TextDisp* textdisp;
	AddScore** addscore;
	Setting* setting;

	unsigned int game_frametime = 0;
	unsigned int score = 0;
	unsigned int hiscore = 0;
	unsigned int combo = 0;
	unsigned int oldcombo = 0;
	unsigned int botime = 0;
	float MapSize = GM_MAX_MAPSIZE;
	float MapCloseSpeed = 1;
	int MaxEnemyBomb = GM_MAX_ENEMY_BOMB;

	int life = GM_MAX_LIFE;

	int expsize = UserData::LoadData(UserData::SETTING, 3);

	int lifeimage;
	int lifematchimage;
	int closemapimage;
	int hukidasiimage;
	int numimage[10];
	int alphabetimage[26];
	int resultimage;
	int highscoreimage;
	int blackimage;
	bool hitmoment = false;
	bool comboflg = false;
	bool resultflg = false;
	bool resultnewflg = false;
	bool SE_HitFlg = false;
	bool SE_NewHitFlg = false;
	bool Soldier_Hit_EX = false;
	bool countdownflg = true;
	bool highscoreflg = false;

	__int8 ui_combo_framecount = 0;

	int CamerashakeCount = 0;
	int Camerashake = 0;

	int r_cun = 0;	// リザルト遷移カウント用
	int c_cun = 0;
	int f_cun = 0;
	int countdown = 4;
	int alpha = 0;
	double countsize = 3.0;

	Vector2D ev;
	float l;

public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	void Draw() const override;
	void Game();
	void SpawnExplosion(Vector2D loc);
	void SpawnParticle(int type, SphereCollider * root, bool loop, Vector2D loc, float angle, float scale, float speed);
	void CameraUpdate();
	void SetCameraShake(int _i);
	void SetMapSize(float f);
	void ChangeMapSize();
	void DrawCombo()const;
	void DrawCloseMap()const;
	void SpawnAddScore(Vector2D loc, int _score);
	void BlackOut(int color, int time);
	void BlackOutDraw()const;
};

