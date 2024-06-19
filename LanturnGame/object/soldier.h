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

	
	void SetMode(int i);//他の兵隊が爆発に巻き込まれた動きが止まる
	int CheckMode();//他の兵隊が爆発に巻き込まれた動きが止まる
	bool CheckDLflg();//消すフラグをセットする

private:
	Vector2D length = 0;
	Vector2D move = 0;
	Vector2D velocity = 0;
	int soldierimg[12];//画像イメージ
	int soldierDetimg;//画像イメージ
	int Velimg = 0;//画像の向き
	int countNum = 0;//時間を測る

	int mode = 1; //0,動けない 1,通常 2,プレイヤーを捕まえた時 3,爆発に巻き込まれたとき
	bool deleteFlg = false;//画面からの削除
	bool SEflg = false;//音が一度だけなる

	int cnt=0;//時間を測る関数
	int animcnt=0;//アニメーション切り替え用関数

};
