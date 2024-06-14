#include "Bomb.h"
#include "DxLib.h"
#include "../Utility/common.h"
#include <math.h>
int Bomb::images[3];
Bomb::Bomb()
{
	speed = 1;
	HitCheck = true;
}
Bomb::~Bomb()
{
}
void Bomb::Init(int _expsize)
{
	expsize = _expsize;
}
void Bomb::Update()
{
	// 点火しているなら
	if (expflg)
	{
		// 速度を変更
		speed = 1.5;
		// 生存時間を下げる
		expcnt--;
		// 0以下になればフラグを切る
		if (expcnt < 0)
		{
			flg = false;
		}
	}

	// ノックバックの速度を徐々に遅くする
	if (knockback != 0.0f)
	{
		knockback /= 1.1f;
	}

	// locationに座標を足す
	location += velocity * speed;
	location += knockback;
	location += exvelocity;

	// マップ外に出ないようにします
	if (location.x < -MapSize + radius)
	{
		location.x = -MapSize + radius;
	}
	if (location.x >= MapSize - radius)
	{
		location.x = MapSize - radius;
	}
	if (location.y < -MapSize + radius)
	{
		location.y = -MapSize + radius;
	}
	if (location.y >= MapSize - radius)
	{
		location.y = MapSize - radius;
	}
}

void Bomb::Draw(Vector2D loc, float _distance) const
{

	// 生存時間が14のあまり7以下なら
	if (expcnt % 14 > 7 && expflg)
	{
		SetDrawBright(255, 0, 0);// 赤以外を暗くする
	}


	int imgnum = 0;

	// 点火しているなら
	if (expflg)
	{
		int OldDrawMode;
		int OldDrawParam;
		GetDrawBlendMode(&OldDrawMode, &OldDrawParam);
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 63);
		// Alpha値63の爆発範囲の円を描画
		DrawCircleAA(DrawFromCameraX(location, _distance, loc)
					,DrawFromCameraY(location, _distance, loc)
					,(15 * (expsize - 2)) * ScaleFromCamera(_distance), 16, 0xffffff, false, 10 * ScaleFromCamera(_distance));
		SetDrawBlendMode(OldDrawMode, OldDrawParam);
		imgnum = 2;
	}

	// 敵画像を描画
	DrawRotaGraphF(DrawFromCameraX(location, _distance, loc)
		, DrawFromCameraY(location, _distance, loc)
		, (1.0 + (double)(max(45 - expcnt, 0) / 45.0)) * ScaleFromCamera(_distance), 0.0, images[imgnum], true);
	
	SetDrawBright(255, 255, 255);// 全色暗くしない（デフォルト）
}

bool Bomb::GetFlg() const
{
	return flg;
}

void Bomb::SetFlg(bool b)
{
	this->flg = b;
}

bool Bomb::GetExpFlg() const
{
	return this->expflg;
}

void Bomb::SetExpFlg(bool b)
{
	this->expflg = b;
}

float Bomb::GetLength(Vector2D loc) 
{
	return sqrtf(powf((loc.x - location.x), 2) + powf((loc.y - location.y), 2));
}

void Bomb::SetVelocity(Vector2D loc)
{
	this->velocity = loc;
}

void Bomb::SetEXVelocity(Vector2D loc)
{
	this->exvelocity = loc;
}

void Bomb::SetMode(int i)
{
	this->mode = i;
}

int Bomb::GetMode()
{
	return this->mode;
}

void Bomb::SetKnockBack(Vector2D vec, int i)
{
	this->knockback = vec * (float)i;
}

void Bomb::LoadImages()
{
	//images = LoadGraph("Resources/images/bomb.png", 0);
	int result = LoadDivGraph("Resources/images/bomb.png", 3, 3, 1, 64, 64, images);
	if (result == -1) {
		printfDx("画像エラー");
	}
}

void Bomb::DeleteImages()
{
	DeleteGraph(*images);
}

void Bomb::hitset()
{
	HitCheck++;
}
int Bomb::hitcheck()
{
	return HitCheck;
}