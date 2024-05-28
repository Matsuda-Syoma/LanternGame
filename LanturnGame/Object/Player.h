#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	Vector2D exvelocity;
	Vector2D lastinput = 0;
	bool pflg = true;			// 生存フラグ
	bool hitflg = false;		// ヒットフラグ
	bool hit_soldier = false;
	bool overice = false;
	bool onconveyor = false;
	bool blinkingflg = false;	// 点滅フラグ
	int cun = 0;				// 無敵時間カウント用
	int blinkingcun = 0;		// 点滅カウント用
	int animcun = 0;			// アニメーションカウント用
	int imgnum = 1;				// 画像描画用変数
	int playerimg[12] = {};		// プレイヤー画像
	int d_playerimg = 0;		// プレイヤー画像（死亡時）
	int angryimg = 0;
	int direction = 4;			// 現在の向き（０：下　１：左　２：右　３：上）
	int stopdirection = 4;		// 歩行中の向き（４：下　５：左　６：右　７：上）
	int pointflg = 0;
	int countflg = 0;
	int stan = 0;
	float deadzone = 0.1f;
	float acceleration = 1.f;
	float friction = .8f;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
	void Invincible();	// 無敵時間
	void Blinking();	// 点滅

	// アニメーション
	void MoveRight();	// 右移動
	void MoveLeft();	// 左移動
	void MoveUp();		// 上移動
	void MoveDown();	// 下移動

	bool GetFlg() const;
	void SetFlg(bool b);
	bool GetPFlg() const;
	void SetPFlg(bool b);
	bool GetIceFlg() const;
	void SetIceFlg(bool b);
	bool GetConFlg() const;
	void SetConFlg(bool b);
	void SetHitSoldier(bool b);
	Vector2D GetVelocity();
	void SetVelocity(Vector2D loc);
	void SetLastInput();
};

