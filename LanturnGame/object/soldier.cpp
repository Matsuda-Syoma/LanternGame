#include "soldier.h"
#include "../common.h"
#include "DxLib.h"

Soldier::Soldier()
{
	Initialize();
}

Soldier::~Soldier()
{

}

void Soldier::Initialize()
{
	speed = 0;	//速度の初期化
	location = (0.0f,0.0f);	//座標の初期化

	//画像の読み込みと画像があるかの確認
	/*image = LoadGraph();

	if (image == -1)
	{
		throw("兵隊がありません。\n");
	}*/
}

void Soldier::Upadate(Vector2D PL)
{
	length = location - PL;

	if (length.x <= 0)
	{
		location.x += speed;
	}
	if (length.x >= 0)
	{
		location.x -= speed;
	}
	if (length.y <= 0)
	{
		location.y += speed;
	}
	if (length.y >= 0)
	{
		location.y -= speed;
	}
	//Move(PL);	//座標を比べて兵隊の移動の向きを変える	
}

void Soldier::Draw(Vector2D PL)
{
	DrawCircle(location.x + (-PL.x + (SCREEN_WIDTH / 2)), location.y + (-PL.y + (SCREEN_HEIGHT / 2)), radius, 0xffffff, true, true);
	/*DrawGraph(location.x, location.y, image, TRUE);*/
}

//void Soldier::Move(Vector2D PL)
//{
//	length = location - PL;
//
//	if (length.x <= 0)
//	{
//		location.x += speed;
//	}
//	if (length.x >= 0)
//	{
//		location.x -= speed;
//	}
//	if (length.y <= 0)
//	{
//		location.y += speed;
//	}
//	if (length.y >= 0)
//	{
//		location.y -= speed;
//	}
//
//}

void Soldier::finalize()
{
	//画像の削除

}