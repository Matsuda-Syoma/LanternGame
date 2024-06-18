#pragma once

#include "CharaBase.h"

class Soldier : public CharaBase
{
public:
	Soldier();
	~Soldier();

	
	void Initialize();//初期化
	void finalize();//終了時
	void Upadate(Vector2D PL);//更新
	void Draw(Vector2D PL, float _distance);//描画
	void Move(Vector2D PL);//移動
	float direction(Vector2D L);//向き
	void SetVelocity(Vector2D loc);
	void PositionCheck();//壁より外側にいるなら内側に入れる

	
	void SetDMGflg(int i);//爆発に巻き込まれた動きが止まる
	bool CheckDLflg();//消すフラグをセットする
	bool checkhitFlg();//当たり判定

	
	void SetmoveFlg();//動きが止まる

private:
	Vector2D length = 0;
	Vector2D move = 0;
	Vector2D velocity = 0;
	int soldierimg[12];//画像イメージ
	int soldierDetimg;//画像イメージ
	int Velimg = 0;//画像の向き
	int countNum = 0;//時間を測る

	int dmgflg = 1; //1/通常 2/プレイヤーを捕まえた時 3/爆発に巻き込まれたとき
	bool hitFlg = true;

	bool deleteFlg = false;
	bool Musicflg = false;

	bool moveFlg = true;

	int cnt=0;
	int animcnt=0;

};
