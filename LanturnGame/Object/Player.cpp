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
}

void Player::Draw(int camerashake) const
{
	/*DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, (int)radius, 0xffff00, true, true);*/

	if (direction == 0) {
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[1], true);
	}
	else if (direction == 1){
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[4], true);
	}
	else if (direction == 2){
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[7], true);
	}
	else if (direction == 3) {
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[10], true);
	}
	

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