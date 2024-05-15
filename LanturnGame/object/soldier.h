#pragma once

#include "CharaBase.h"

class Soldier : public CharaBase
{
public:
	Soldier();
	~Soldier();

	//初期化
	void Initialize();
	//終了時
	void finalize();
	//更新
	void Upadate(Vector2D PL);
	//描画
	void Draw(Vector2D PL);
	//移動
	void Move(Vector2D PL);
	//向き
	float direction(Vector2D L);
	//ノックバック
	void Knockback(Vector2D V, float P);
	void SetVelocity(Vector2D loc);

	//壁より外側にいるなら内側に入れる
	void PositionCheck();

	//爆発に巻き込まれた動きが止まる
	void SetDMGflg(bool i);
	//
	bool ChekDMGflg();
	//消すフラグをセットする

	//
	bool ChekDLflg();

private:
	Vector2D length = 0;
	Vector2D move = 0;
	Vector2D knockback = 0;
	Vector2D velocity = 0;
	int CD;//中心点の距離
	int soldierimg[12];//画像イメージ
	int soldierDetimg[12];//画像イメージ
	int Velimg;//画像の向き
	bool dmgflg = false;
	int countNum;//再生成までの時間を測る
	bool deleteFlg = false;
};
