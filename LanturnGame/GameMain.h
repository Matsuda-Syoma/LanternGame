#pragma once
#include"DxLib.h"
#include"AbstractScene.h"
#include "Bomb.h"
#include "Explosion.h"
#include "Player.h"
class GameMain : public AbstractScene
{
private:
	Bomb** bomb;
	Explosion** explosion;
	Player* player;
	int score = 0;
	int ratio = 0;
	bool ratioflg = false;
public:
	GameMain();
	~GameMain();

	virtual AbstractScene* Update() override;
	void Draw() const override;
	void Game();	
	void SpawnExplosion(Vector2D loc);
};

