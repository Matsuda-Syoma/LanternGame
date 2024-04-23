#pragma once
#include "CharaBase.h"
class Player : public CharaBase
{
private:
	Vector2D velocity;
	bool hitflg = false;
	int cun = 0;			// 無敵時間カウント用
	int animcun = 0;		// アニメーションカウント用
	int imgnum = 1;			// 画像描画用変数
	int playerimg[12];		// プレイヤー画像
	int direction = 4;		// 向き取得
	int stopdirection = 0;

public:
	Player();
	~Player();
	void Init();
	void Update();
	void Draw(int camerashake)const;
	void Movement();
	void Invincible();

	// アニメーション
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();

	bool GetFlg() const;
	void SetFlg(bool b);
	Vector2D GetVelocity();
};

