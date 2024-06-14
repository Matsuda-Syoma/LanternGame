#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	Vector2D exvelocity;
	Vector2D lastinput = 0;
	bool pflg = true;			// プレイヤー生存フラグ
	bool hitflg = false;		// ヒットフラグ
	bool hitsoldier = false;	// ヒットフラグ（兵隊）
	bool overice = false;		// 氷の床に乗ったとき用のフラグ
	bool onconveyor = false;	// コンベアに乗ったとき用のフラグ
	bool blinkingflg = false;	// 点滅フラグ
	int Invincible_cnt = 0;		// 無敵時間カウント用
	int blinking_cnt = 0;		// 点滅カウント用
	int anim_cnt = 0;			// アニメーションカウント用
	int stan_cnt = 0;			// スタン時間カウント用
	int imgnum = 1;				// 画像描画用変数
	int playerimg[12] = {};		// プレイヤー画像
	int deadplayer_img = 0;		// プレイヤー画像（死亡時）
	int angry_img = 0;			// 兵隊に捕まった時の画像
	int direction = 4;			// 現在の向き（０：下　１：左　２：右　３：上）
	int stopdirection = 4;		// 歩行中の向き（４：下　５：左　６：右　７：上）
	float deadzone = 0.1f;
	float acceleration = 1.f;
	float friction = .8f;
	float movelength = 0.0f;
public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(Vector2D loc, float _distance)const;
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
	bool GetHitSoldier() const;
	void SetHitSoldier(bool b);
	Vector2D GetVelocity();
	void SetVelocity(Vector2D loc);
	void SetLastInput();
	float GetNormalSpeed();
	int GetDirection();
};

