#pragma once
class Description
{
public:
	Description();
	~Description();
	void Update();
	void Draw();

	int cheakTextNumber();
	//

private:
	//画像読み込み用変数
	//爆弾
	int ignited;
	int touchbomb;
	int bakuhatu;
	int chain;
	//兵隊
	int touchsoldier;
	int be_pursued;

	int sankaku;

	//画像移動用変数
	int Movepng;
	int MovepngMax;
	bool page;

	//表示するtext確認
	int textNumber;
};

