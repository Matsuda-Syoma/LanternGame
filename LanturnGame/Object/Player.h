#pragma once
#include "CharaBase.h"

class Player : public CharaBase
{
private:
	Vector2D velocity;
	Vector2D lastinput = 0;
	Vector2D knockback = 0;
	Vector2D vvec = 0;
	Vector2D length = 0;
	bool pflg = true;			// プレイヤー生存フラグ
	bool hitflg = false;		// ヒットフラグ（爆発or兵隊）
	bool hitsoldier = false;	// ヒットフラグ（兵隊）
	bool ignitionflg = false;	// 点火フラグ
	bool overice = false;		// 氷の床に乗ったとき用のフラグ
	bool onconveyor = false;	// コンベアに乗ったとき用のフラグ
	bool blinkingflg = false;	// 点滅フラグ
	bool damagedirection = false;	// ダメージ演出用のフラグ
	bool stickflg = false;			// スティック入力フラグ
	bool crossbuttonflg = false;	// 十字ボタン入力フラグ

	int Invincible_cnt = 0;		// 無敵時間カウント用
	int blinking_cnt = 0;		// 点滅カウント用
	int anim_cnt = 0;			// アニメーションカウント用
	int stan_cnt = 0;			// スタン時間カウント用
	int imgnum = 1;				// 画像描画用変数
	int imgdirection = 1;

	//int playerimg[12] = {};		// プレイヤー画像
	int playerimg[24] = {};		// プレイヤー画像
	int deadplayer_img = 0;		// プレイヤー画像（死亡時）
	int angry_img = 0;			// 兵隊に捕まった時の画像
	int direction = 1;			// 現在の向き（０：下　１：左　２：右　３：上　４：左斜め下　５：左斜め上　６：右斜め下　７：右斜め上）
	int stop_direction = 8;		// 止まったときの向き（８：下　９：左　１０：右　１１：上　１２：左斜め下　１３：左斜め上　１４：右斜め下　１５：右斜め上）

	float deadzone = 0.1f;
	float acceleration = 4.f;
	float friction = .8f;
	float movelength = 0.0f;
	int areahitradius = 32;
	bool InputB = false;
public:
	Player();
	~Player();
	void Initialize(GameMain* _g, int _obj_pos)override;
	void Finalize()override;
	void Update(GameMain* _g)override;
	void Draw(CameraManager* camera)const override;
	void Hit(Object* _obj)override;
	void Movement();
	void Invincible();	// 無敵時間
	void Blinking();	// 点滅
	void KnockBack(Vector2D EX);	// ノックバック

	// アニメーション
	void MoveAnim();
	//void MoveRight();	// 右移動
	//void MoveLeft();	// 左移動
	//void MoveUp();		// 上移動
	//void MoveDown();	// 下移動

	bool GetHitFlg() const;
	void SetHitFlg(bool b);
	bool GetPlayerFlg() const;
	void SetPlayerFlg(bool b);
	bool GetIgnitionFlg() const;
	void SetIgnitionFlg(bool b);
	bool GetIceFlg() const;
	void SetIceFlg(bool b);
	bool GetConFlg() const;
	void SetConFlg(bool b);
	bool GetHitSoldier() const;
	void SetHitSoldier(bool b);
	bool GetIDamageDirectionFlg() const;
	void SetDamageDirectionFlg(bool b);

	Vector2D GetVelocity();
	void SetVelocity(Vector2D loc);
	void SetLastInput();
	float GetNormalSpeed();
	float GetLength(Vector2D loc);
	int GetDirection();
	void SetKnockBack(Vector2D vec, int i);

};

