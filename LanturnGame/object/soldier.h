#pragma once

#include "CharaBase.h"

class Soldier : public CharaBase
{
public:
	Soldier();
	~Soldier();

	
	void Initialize();//初期化
	//終了時
	void finalize();
	//更新
	void Upadate(Vector2D PL);
	//描画
	void Draw(Vector2D PL, float _distance);
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
	void SetDMGflg(int i);
	//
	bool ChekDMGflg();
	//消すフラグをセットする
	void SetDLflg(bool i);
	
	bool ChekDLflg();
	bool ChekhitFlg();

	//動きが止まる
	void SetmoveFlg();
	bool ChekmoveFlg();

	//プレイヤーに振られたときにフラグを立てる
	void SetcatchFlg();

private:
	Vector2D length = 0;
	Vector2D move = 0;
	Vector2D knockback = 0;
	Vector2D velocity = 0;
	int CD;//中心点の距離
	int soldierimg[12];//画像イメージ
	int soldierDetimg;//画像イメージ
	int Velimg = 0;//画像の向き
	int countNum = 0;//再生成までの時間を測る
	int a = 0;

	int dmgflg = 1; //1/通常 2/プレイヤーを捕まえた時 3/爆発に巻き込まれたとき
	bool hitFlg = true;

	bool deleteFlg = false;
	bool Musicflg = false;

	bool moveFlg = true;
	bool catchFlg = true;

	int cnt=0;
	int animcnt=0;

};
