#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
class GameMain : public AbstractScene
{
public:
	GameMain();
	// コンストラクタ
	~GameMain();								// デストラクタ

	virtual AbstractScene* Update() override;	// 描画以外の更新を実行
	void Draw() const override;					// 描画に関することを実装
	void Game();								// ゲームの処理
};

