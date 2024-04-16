#include "Player.h"
#include "DxLib.h"
#include "Utility/InputControl.h"
#include <math.h>
#include "common.h"
Player::Player()
{
	speed = 10;
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
}

void Player::Draw(int camerashake) const
{
	DrawCircle(camerashake + SCREEN_WIDTH / 2, camerashake + SCREEN_HEIGHT / 2, radius, 0xffff00, true, true);
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
	if (fabsf(InputControl::GetLeftStick().x) > 0.1)
	{
		velocity += Vector2D(InputControl::GetLeftStick().x, 0.0f);
	}
	if (fabsf(InputControl::GetLeftStick().y) > 0.1)
	{
		velocity += Vector2D(0.0f, -InputControl::GetLeftStick().y);
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

	// 減速(X)
	if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) || 
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT) || 
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) ||
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) ||
		fabsf(InputControl::GetLeftStick().y) < 0.2 ||
		fabsf(InputControl::GetLeftStick().x) < 0.2)
	{
		velocity /= 1.2;
		if (fabs(velocity.x) < 0.1)
		{
			velocity.x = 0;
		}
		if (fabs(velocity.y) < 0.1)
		{
			velocity.y = 0;
		}
	}

	// 画面外に出ないように
	/*
	if (location.x < 0)
	{
		location.x = 0;
	}
	if (location.x >= 1280.0f - radius)
	{
		location.x = 1280.0f - radius;
	}
	if (location.y < 0)
	{
		location.y = 0;
	}
	if (location.y >= 720.0f - radius)
	{
		location.y = 720.0f - radius;
	}*/
}
