#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	bool hitflg = false;
	bool blinkingflg = false;	// 点滅フラグ
	int cun = 0;				// 無敵時間カウント用
	int blinkingcun = 0;		// 点滅カウント用
	int animcun = 0;			// アニメーションカウント用
	int imgnum = 1;				// 画像描画用変数
	int playerimg[12];			// プレイヤー画像
	int direction = 4;			// 歩行中の向き（０：下　１：左　２：右　３：上）
	int stopdirection = 4;		// 立ち止まった時の向き（４：下　５：左　６：右　７：上）
	float deadzone = 0.1;
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
	Vector2D GetVelocity();
};

