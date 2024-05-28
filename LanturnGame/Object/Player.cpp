#include "Player.h"
#include "DxLib.h"
#include <math.h>
#include "../Utility/InputControl.h"
#include "../Utility/common.h"
#include "../Utility/UserData.h"
Player::Player()
{
	speed = 5;
	deadzone = UserData::LoadData(0);
}

Player::~Player()
{
	DeleteGraph(*playerimg);
	DeleteGraph(d_playerimg);
}

void Player::Init()
{
	LoadDivGraph("Resources/images/player.png", 12, 3, 4, 64, 64, playerimg);
	d_playerimg = LoadGraph("Resources/images/player_death.png");
	angryimg = LoadGraph("Resources/images/angry.png");
}

void Player::Update()
{
	lastinput = 0;

	if (overice == false)
	{
		speed = 5;
	}else{
		speed = 10;
	}

	if (onconveyor == false)
	{
		speed = 5;
	}
	else {

	}

	//if (!InputControl::GetButton(XINPUT_BUTTON_A)) {
	if (pflg == true && hit_soldier == false)
	{
		Movement();
		location += velocity;
		location += exvelocity;

	}
	else if (hit_soldier == true)
	{

		if (stan <= 90)
		{
			stan++;
		}
		else
		{
			hit_soldier = false;
			stan = 0;
		}


	}
	//}
	//else {
	//	LineTrace();
	//}

	// 爆発に当たったら無敵時間
	if (hitflg == true) {
		Invincible();
		Blinking();
	}

	if (hit_soldier == false)
	{
		// プレイヤーアニメーション
		if (direction == 0) {	// 下移動
			MoveDown();
		}
		else if (direction == 2) {	// 右移動
			MoveRight();
		}
		else if (direction == 1) {	// 左移動
			MoveLeft();
		}
		else if (direction == 3) {	// 上移動
			MoveUp();
		}
		else if (direction == 4) {	// 下停止
			imgnum = 1;
		}
		else if (direction == 6) {	// 右停止
			imgnum = 7;
		}
		else if (direction == 5) {	// 左停止
			imgnum = 4;
		}
		else if (direction == 7) {	// 上停止
			imgnum = 10;
		}
	}

	

}

void Player::Draw(int camerashake) const
{
	if (pflg == true && hit_soldier == false) {
		if (blinkingflg == false)
		{
			DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[imgnum], true);
		}
		else {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
			DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[imgnum], true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
		}
	}
	else if(pflg == false) {
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, d_playerimg, true);
	}
	else if (pflg == true && hit_soldier == true)
	{
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, angryimg, true);
	}
	
	// 元の描画を取得
	int OldBlendMode;
	int OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)max(((180. / cun) * 6) - 48, 0));
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff0000, true);
	SetDrawBlendMode(OldBlendMode, OldBlendParam);

}

void Player::Movement()
{
	if (fabsf(InputControl::GetLeftStick().x) > deadzone || fabsf(InputControl::GetLeftStick().y) > deadzone)
	{
		// スティック入力
		velocity += Vector2D(
			InputControl::GetLeftStick().x * acceleration
		 , -InputControl::GetLeftStick().y * acceleration);
	}
	// 摩擦係数
	if (overice == true)
	{
		velocity *= 0.99f;
	}
	else 
	{
		velocity *= friction;
	}

	// 移動ベクトルの大きさの計算
	movelength = sqrtf(velocity.x * velocity.x + velocity.y * velocity.y);

	// 最大速度を超えないように
	if (movelength > speed)
	{
		float scale = speed / movelength;
		velocity.x *= scale;
		velocity.y *= scale;
	}

	if (fabs(velocity.x) < 0.01)
	{
		velocity.x = 0;
	}
	if (fabs(velocity.y) < 0.01)
	{
		velocity.y = 0;
	}

	// 画面外に出ないように
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


	// 氷の上に乗っていない時
	if (hit_soldier == false) {
		// 左右アニメーション
		if (velocity.x == 0)
		{
			// 右移動
			if (InputControl::GetLeftStick().x > 0.8)
			{
				direction = 2;
				stopdirection = 6;
			}
			// 左移動
			if (InputControl::GetLeftStick().x < -0.8)
			{
				direction = 1;
				stopdirection = 5;
			}
		}
		else {
			// 右移動
			if (InputControl::GetLeftStick().x > 0.2)
			{
				direction = 2;
				stopdirection = 6;
			}
			// 左移動
			if (InputControl::GetLeftStick().x < -0.2)
			{
				direction = 1;
				stopdirection = 5;
			}
		}

		// 前後アニメーション
		if (velocity.y == 0)
		{
			// 上移動
			if (InputControl::GetLeftStick().y > 0.8)
			{
				direction = 3;
				stopdirection = 7;
			}
			// 下移動
			if (InputControl::GetLeftStick().y < -0.8)
			{
				direction = 0;
				stopdirection = 4;
			}
		}
		else {
			// 上移動
			if (InputControl::GetLeftStick().y > 0.2)
			{
				direction = 3;
				stopdirection = 7;
			}
			// 下移動
			if (InputControl::GetLeftStick().y < -0.2)
			{
				direction = 0;
				stopdirection = 4;
			}
		}

	}
	// 氷に乗っているとき
	//else {

	//	// 右移動
	//	if (InputControl::GetLeftStick().x > 0.2)
	//	{
	//		direction = 2;
	//		stopdirection = 6;
	//	}
	//	// 左移動
	//	if (InputControl::GetLeftStick().x < -0.2)
	//	{
	//		direction = 1;
	//		stopdirection = 5;
	//	}
	//	// 上移動
	//	if (InputControl::GetLeftStick().y > 0.2)
	//	{
	//		direction = 3;
	//		stopdirection = 7;
	//	}
	//	// 下移動
	//	if (InputControl::GetLeftStick().y < -0.2)
	//	{
	//		direction = 0;
	//		stopdirection = 4;
	//	}

	//	direction = stopdirection;
	//}

	// 立ち止まっているとき（アニメーション）
	// 左スティックが入力されていなかったら
	if (InputControl::GetLeftStick().x < 0.2 && InputControl::GetLeftStick().x > -0.2 
		&& InputControl::GetLeftStick().y < 0.2 && InputControl::GetLeftStick().y > -0.2) {
		// 十字ボタンが入力されていなかったら
		if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) && !InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT) 
			&& !InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) && !InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN)) 
		{
			direction = stopdirection;
		}
		
	}
}

// 無敵時間
void Player::Invincible()
{
	cun++;
	switch (cun)
	{
	case(0):
		break;
	case(180):
		hitflg = false;
		cun = 0;
		break;
	default:
		break;
	}
}

// 点滅
void Player::Blinking()
{
	if (pflg == true) {
		blinkingcun++;
		switch (blinkingcun)
		{
		case(1):
			blinkingflg = true;
			break;
		case(10):
			blinkingflg = false;
			break;
		case(20):
			blinkingcun = 0;
		default:
			break;
		}
	}
	else {
		blinkingflg = false;
	}
}

// 右移動アニメーション
void Player::MoveRight()
{
	animcun++;
	switch (animcun)
	{
	case(1):
		imgnum = 7;
		break;
	case(15):
		imgnum = 6;
		break;
	case(30):
		imgnum = 7;
		break;
	case(45):
		imgnum = 8;
		break;
	case(60):
		animcun = 0;
		break;
	default:
		break;
	}
}

// 左移動アニメーション
void Player::MoveLeft()
{
	animcun++;
	switch (animcun)
	{
	case(1):
		imgnum = 4;
		break;
	case(15):
		imgnum = 3;
		break;
	case(30):
		imgnum = 4;
		break;
	case(45):
		imgnum = 5;
		break;
	case(60):
		animcun = 0;
		break;
	default:
		break;
	}
}

// 上移動アニメーション
void Player::MoveUp()
{
	animcun++;
	switch (animcun)
	{
	case(1):
		imgnum = 10;
		break;
	case(15):
		imgnum = 9;
		break;
	case(30):
		imgnum = 10;
		break;
	case(45):
		imgnum = 11;
		break;
	case(60):
		animcun = 0;
		break;
	default:
		break;
	}
}

// 下移動アニメーション
void Player::MoveDown()
{
	animcun++;
	switch (animcun)
	{
	case(1):
		imgnum = 0;
		break;
	case(15):
		imgnum = 1;
		break;
	case(30):
		imgnum = 2;
		break;
	case(45):
		imgnum = 1;
		break;
	case(60):
		animcun = 0;
		break;
	default:
		break;
	}
}

bool Player::GetFlg() const
{
	return hitflg;
}

void Player::SetFlg(bool b)
{
	this->hitflg = b;
}

bool Player::GetPFlg() const
{
	return pflg;
}

void Player::SetPFlg(bool b)
{
	this->pflg = b;
}

bool Player::GetIceFlg() const
{
	return overice;
}

void Player::SetIceFlg(bool b)
{
	this->overice = b;
}

bool Player::GetConFlg() const
{
	return onconveyor;
}

void Player::SetConFlg(bool b)
{
	this->onconveyor = b;
}

void Player::SetHitSoldier(bool b)
{
	this->hit_soldier = b;
}

Vector2D Player::GetVelocity()
{
	return this->velocity;
}

void Player::SetVelocity(Vector2D loc)
{
	this->exvelocity = loc;
}

void Player::SetLastInput()
{
	if (fabsf(InputControl::GetLeftStick().x) > deadzone)
	{
		if (InputControl::GetLeftStick().x < 0.f) {
			lastinput.x = (InputControl::GetLeftStick().x + deadzone);
		}
		if (InputControl::GetLeftStick().x > 0.f) {
			lastinput.x = (InputControl::GetLeftStick().x - deadzone);
		}
	}
	if (fabsf(InputControl::GetLeftStick().y) > deadzone)
	{
		if (InputControl::GetLeftStick().y < 0.f) {
			lastinput.y = (-InputControl::GetLeftStick().y - deadzone);
		}
		if (InputControl::GetLeftStick().y > 0.f) {
			lastinput.y = (-InputControl::GetLeftStick().y + deadzone);
		}
	}
}

float Player::GetNormalSpeed()
{
	return this->movelength / speed;
}
