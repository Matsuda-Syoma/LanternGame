#include "Player.h"
#include "DxLib.h"
#include "../Utility/InputControl.h"
#include <math.h>
#include "../Utility/common.h"
Player::Player()
{
	speed = 5;
}

Player::~Player()
{
}

void Player::Init()
{
	LoadDivGraph("Resources/images/player.png", 12, 3, 4, 64, 64, playerimg);
}

void Player::Update()
{
	Movement();
	location += velocity;

	// 爆発に当たったら無敵時間
	if (hitflg == true) {
		Invincible();
	}

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

void Player::Draw(int camerashake) const
{

	DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[imgnum], true);

	if (hitflg == true) {
		DrawString(10, 30, "Invincible", 0xffffff);
	}
}

void Player::Movement()
{
	// pad入力
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity += Vector2D(-0.5f, 0.0f);
		direction = 1;
	}
	
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity += Vector2D(0.5f, 0.0f);
		direction = 2;
	}
	
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity += Vector2D(0.0f, 0.5f);
		direction = 0;
	}
	
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity += Vector2D(0.0f, -0.5f);
		direction = 3;
	}
	
	if (fabsf(InputControl::GetLeftStick().x) > 0.1)
	{
		velocity = Vector2D(InputControl::GetLeftStick().x * speed, GetVelocity().y);
	}
	if (fabsf(InputControl::GetLeftStick().y) > 0.1)
	{
		velocity = Vector2D(GetVelocity().x, -InputControl::GetLeftStick().y * speed);
	}
	// 速度の制限(Y)
	if (velocity.y > speed)
	{
		velocity.y = speed;
	}
	else if (velocity.y < -speed)
	{
		velocity.y = -speed;
	}

	// 速度の制限(X)
	if (velocity.x > speed)
	{
		velocity.x = speed;
	}
	else if (velocity.x < -speed)
	{
		velocity.x = -speed;
	}
	// 減速
	if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) && 
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT) && 
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) &&
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) &&
		fabsf(InputControl::GetLeftStick().y) < 0.2 &&
		fabsf(InputControl::GetLeftStick().x) < 0.2)
	{
		velocity /= 1.2f;
		if (fabs(velocity.x) < 0.01)
		{
			velocity.x = 0;
		}
		if (fabs(velocity.y) < 0.01)
		{
			velocity.y = 0;
		}
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

	// 十字キーが離されたとき
	if (InputControl::GetButtonUp(XINPUT_BUTTON_DPAD_LEFT))
	{
		direction = 5;
	}
	if (InputControl::GetButtonUp(XINPUT_BUTTON_DPAD_RIGHT))
	{
		direction = 6;
	}
	if (InputControl::GetButtonUp(XINPUT_BUTTON_DPAD_DOWN))
	{
		direction = 4;
	}
	if (InputControl::GetButtonUp(XINPUT_BUTTON_DPAD_UP))
	{
		direction = 7;
	}

	/*if (InputControl::GetLeftStick().x > 1) {
		direction = 1;
	}*/

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

Vector2D Player::GetVelocity()
{
	return this->velocity;
}