#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
#include "../Object/Object.h"
#include "../Object/CameraManager.h"
#include "../Object/Bomb.h"
#include "../Object/Explosion.h"
#include "../Object/Player.h"
#include "../Object/BackGround.h"
#include "../Object/Soldier.h"
#include "../Object/Particle.h"
#include "../Utility/common.h"
//#include "../Object/stage.h"
//#include "../Object/Conveyor.h"
#include "../Object/Tornado.h"
//#include "../Object/ComboEnd.h"
#include "../Utility/TextDisp.h"
//#include "../Object/AddScore.h"
#include "../Utility/UserData.h"
#include "../Scene/Setting.h"
//#include "../Object/Conveyor_y.h"

class GameMain : public AbstractScene
{
private:
	Object* object[GM_MAX_OBJECT] = { nullptr };
	CameraManager* camera;
	BackGround** background;
	//Bomb** bomb;
	//Explosion** explosion;
	//Player* player;
	//Soldier** soldier;
	Particle** particle;
	//Stage** stage;
	//Conveyor** conveyor;
	//Tornado** tornado;
	//ComboEnd** comboend;
	//TextDisp* textdisp;
	//AddScore** addscore;
	//Setting* setting;
	//Conveyor_y** conveyor_y;
	unsigned int game_frametime = 0;
	unsigned int score = 0;
	unsigned int hiscore = 0;
	unsigned int combo = 0;
	unsigned int oldcombo = 0;
	unsigned int botime = 0;
	float MapSize = GM_MAX_MAPSIZE;
	float MapCloseSpeed = 1;
	int MaxSpawnEnemyBomb = C_MaxEnemyBomb;
	int C_MaxEnemyBomb = (int)UserData::LoadData(UserData::SETTING, 1);
	int C_ExpSize = (int)UserData::LoadData(UserData::SETTING, 2);
	int C_MaxSoldier = (int)UserData::LoadData(UserData::SETTING, 3);
	Vector2D Camera, cMin, cMax;

	int CameraOutCnt = 0;

	float CameraDistance = 0.0f;

	int life = GM_MAX_LIFE;
	int Displaylife = life;

	int lifeimage;
	int lifematchimage;
	int closemapimage;
	int hukidasiimage;
	int numimage[10];
	int alphabetimage[26];
	int resultimage;
	int highscoreimage;
	int blackimage;
	int crackimage;
	int sootimage;
	bool hitmoment = false;
	bool comboflg = false;
	bool resultflg = false;
	bool resultnewflg = false;
	bool SE_HitFlg = false;
	bool SE_NewHitFlg = false;
	bool Soldier_Hit_EX = false;
	bool countdownflg = true;
	bool highscoreflg = false;
	bool crackflg = false;
	bool PauseFlg = false;

	__int8 ui_combo_framecount = 0;

	int CamerashakeCount = 0;
	int Camerashake = 0;

	int result_cnt = 0;	// リザルト遷移カウント用
	int cnt = 0;		// カウントダウン用
	int countdown = 4;
	double countsize = 3.0;
	// 画像透かし用
	int fadeout_alpha = 0;
	int crack_alpha = 200;
	int soot_alpha = 0;

	Vector2D ev;
	float l;

	int ScoreCenter = 0;

public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	void Draw() const override;
	void Game();
	void SpawnExplosion(Vector2D loc);
	void CameraUpdate();
	void SetCameraShake(int _i);
	void SetMapSize(float f);
	float GetMapSize() const;
	void ChangeMapSize();
	void DrawCloseMap()const;
	void SpawnAddScore(Vector2D loc, int _score);
	void BlackOut(int color, int time);
	void BlackOutDraw()const;
	void DrawPause()const;
	int CreateObject(Object* _object);
	int CreateParticle(int type);
	Particle* GetParticle(int _num);
	void DeleteObject(Object* _object, int _pos);
	void DeleteParticle(Particle* _particle, int _pos);
	Object* GetObject(int _pos);
	Object* GetPlayer();
	CameraManager* GetCamera();
};

