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
	Vector2D knockback = 0;		// ノックバックVelocity
	Vector2D movetoloc = 0;		// 指定座標

	//パーティクルを一度だけ表示
	int HitCheck;

public:
	Bomb();
	~Bomb();
	void Initialize(GameMain* _g, int _obj_pos)override;
	void Finalize()override;
	void Hit(SphereCollider* _sphere)override;

	void Init(int _expsize);
	void Update(GameMain* _g)override;
	void Draw(CameraManager* camera)const override;
	bool GetFlg() const;
	void SetFlg(bool b);
	bool GetExpFlg() const;
	void SetExpFlg(bool b);

	void SetVelocity(Vector2D loc);
	void SetEXVelocity(Vector2D loc);

	void SetMode(int i);

	int GetMode();
	void SetKnockBack(Vector2D vec, int i);
	static void LoadImages();
	static void DeleteImages();
	Object* GetInsideBomb();

	//パーティクルを一度だけ表示
	int hitcheck();
	void hitset();
};

