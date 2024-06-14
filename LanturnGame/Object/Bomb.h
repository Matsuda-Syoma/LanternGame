#pragma once
#include "CharaBase.h"

class Bomb : public CharaBase
{
private:
	static int images[];
	int mode = 0;				// 動くタイプ
	bool flg = true;			// 生きているか
	bool expflg = false;		// 着火しているか
	int maxexpcnt = 180;		// 着火から爆発するまで
	int expcnt = maxexpcnt;		// 爆発するまでの時間
	int expsize = 10;			// 初期の爆発サイズ
	Vector2D velocity = 0;		// 移動Velocity
	Vector2D exvelocity = 0;	// 外的Velocity
	Vector2D knockback = 0;		// ノックバックVelocity
	Vector2D movetoloc = 0;		// 指定座標

	//パーティクルを一度だけ表示
	int HitCheck;

public:
	Bomb();
	~Bomb();
	void Init(int _expsize);
	void Update();
	void Draw(Vector2D loc, float _distance) const;
	bool GetFlg() const;
	void SetFlg(bool b);
	bool GetExpFlg() const;
	void SetExpFlg(bool b);

	float GetLength(Vector2D loc);

	void SetVelocity(Vector2D loc);
	void SetEXVelocity(Vector2D loc);

	void SetMode(int i);

	int GetMode();
	void SetKnockBack(Vector2D vec, int i);
	static void LoadImages();
	static void DeleteImages();

	//パーティクルを一度だけ表示
	int hitcheck();
	void hitset();
};

