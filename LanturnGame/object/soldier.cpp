#include "soldier.h"

#include "DxLib.h"

soldier::soldier()
{
	Initialize();
}

soldier::~soldier()
{

}

void soldier::Initialize()
{
	speed = 0;	//速度の初期化
	location = player->GetLocation() + Vector2D(50.0f, 50.0f);	//座標の初期化

	//画像の読み込みと画像があるかの確認
	/*image = LoadGraph();

	if (image == -1)
	{
		throw("兵隊がありません。\n");
	}*/
}

void soldier::Upadate()
{
	Move();	//座標を比べて兵隊の移動の向きを変える	
}

void soldier::Draw()
{
	DrawCircle(location.x, location.y, radius, 0x123456, true, true);
	/*DrawGraph(location.x, location.y, image, TRUE);*/
}

void soldier::Move()
{
	PL = player->GetLocation();

	//プレイヤーが右にいるなら
	if (location.x <= PL.x)
	{
		location.x += speed;
	}
	//プレイヤーが左にいるなら
	if (location.x >= PL.x)
	{
		location.x -= speed;
	}
	//プレイヤーが上にいるなら
	if (location.y <= PL.y)
	{
		location.y += speed;
	}
	//プレイヤーが下にいるなら
	if (location.y >= PL.y)
	{
		location.y -= speed;
	}
}

void soldier::finalize()
{
	//画像の削除

}