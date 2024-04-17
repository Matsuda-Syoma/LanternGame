#pragma once
#include "CharaBase.h"
#include "Player.h"

class soldier : public CharaBase
{
public:
	soldier();
	~soldier();

	//初期化
	void Initialize();
	//終了時
	void finalize();
	//更新
	void Upadate();
	//描画
	void Draw();

	//移動
	void Move();

private:
	Player* player;
	int image;	//画像イメージ
	Vector2D PL;
};

