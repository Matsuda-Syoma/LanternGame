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
	float direction(Vector2D PL);
	//ノックバック
	void Knockback(Vector2D V, float P);
private:
	int image;	//画像イメージ
	Vector2D length = 0;
	Vector2D move = 0;
	Vector2D knockback = 0;
	int CD;//中心点の距離
};
