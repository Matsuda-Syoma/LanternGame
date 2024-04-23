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
}

void Player::Init()
{
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
	DrawCircle(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, (int)radius, 0xffff00, true, true);
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
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity += Vector2D(0.5f, 0.0f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity += Vector2D(0.0f, 0.5f);
	}
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity += Vector2D(0.0f, -0.5f);
	}
	if (fabsf(InputControl::GetLeftStick().x) > deadzone)
	{
		if (InputControl::GetLeftStick().x < 0.f) {
			velocity += Vector2D((InputControl::GetLeftStick().x + deadzone) * speed, 0);
		}
		if (InputControl::GetLeftStick().x > 0.f) {
			velocity += Vector2D((InputControl::GetLeftStick().x - deadzone) * speed, 0);
		}
	}
	if (fabsf(InputControl::GetLeftStick().y) > deadzone)
	{
		if (InputControl::GetLeftStick().y < 0.f) {
			velocity += Vector2D(0, (-InputControl::GetLeftStick().y - deadzone) * speed);
		}
		if (InputControl::GetLeftStick().y > 0.f) {
			velocity += Vector2D(0, (-InputControl::GetLeftStick().y + deadzone) * speed);
		}
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

	if (fabsf(velocity.x) == fabsf(velocity.y))
	{
		velocity *= 0.7071f;
	}
	// 減速

		if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) &&
			!InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT) && 
			fabsf(InputControl::GetLeftStick().x) < deadzone) {
			velocity.x /= 1.2f;
		}
		if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) &&
			!InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) && 
			fabsf(InputControl::GetLeftStick().y) < deadzone) {
			velocity.y /= 1.2f;
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