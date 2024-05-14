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
}

void Player::Init()
{
	LoadDivGraph("Resources/images/player.png", 12, 3, 4, 64, 64, playerimg);
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

	//if (!InputControl::GetButton(XINPUT_BUTTON_A)) {
		Movement();
		location += velocity;
		location += exvelocity;
	//}
	//else {
	//	LineTrace();
	//}

	// 爆発に当たったら無敵時間
	if (hitflg == true) {
		Invincible();
		Blinking();
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

	if (overice == true) {
		++pointflg;
		countflg = pointflg % 4;
		if (countflg == 0) {
			imgnum = 1;
			}
		if (countflg == 1) {
			imgnum == 7;
		}
		if (countflg == 2) {
			imgnum == 4;
		}
		if (countflg == 3) {
			imgnum == 10;
		}
		
	}
}

void Player::Draw(int camerashake) const
{
	if (blinkingflg == false)
	{
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[imgnum], true);
	}
	else {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
		DrawRotaGraph(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 1.0, 0.0, playerimg[imgnum], true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	// 元の描画を取得
	int OldBlendMode;
	int OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, max(((180. / cun) * 6) - 48, 0));
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff0000, true);
	SetDrawBlendMode(OldBlendMode, OldBlendParam);

}

void Player::Movement()
{
	// pad入力
	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
	{
		velocity += Vector2D(-0.5f, 0.0f);
		direction = 1;
		stopdirection = 5;
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
	{
		velocity += Vector2D(0.5f, 0.0f);
		direction = 2;
		stopdirection = 6;
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
	{
		velocity += Vector2D(0.0f, 0.5f);
		direction = 0;
		stopdirection = 4;
	}

	if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
	{
		velocity += Vector2D(0.0f, -0.5f);
		direction = 3;
		stopdirection = 7;
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
		if(overice == true){
			velocity.x /= 0.6f;
		}
		else {
			velocity.x /= 1.2f;
		}
	}
	if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) &&
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) &&
		fabsf(InputControl::GetLeftStick().y) < deadzone) {
		if (overice == true) {
			velocity.y /= 0.6f;
		}
		else {
			velocity.y /= 1.2f;
		}
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


	// 左右アニメーション
	if (velocity.x == 0)
	{
		if (InputControl::GetLeftStick().x > 0.8)
		{
			direction = 2;
			stopdirection = 6;
		}
		if (InputControl::GetLeftStick().x < -0.8)
		{
			direction = 1;
			stopdirection = 5;
		}
	}
	else {
		if (InputControl::GetLeftStick().x > 0.2)
		{
			direction = 2;
			stopdirection = 6;
		}
		if (InputControl::GetLeftStick().x < -0.2)
		{
			direction = 1;
			stopdirection = 5;
		}
	}
	

	// 前後アニメーション
	if (velocity.y == 0)
	{
		if (InputControl::GetLeftStick().y > 0.8)
		{
			direction = 3;
			stopdirection = 7;
		}

		if (InputControl::GetLeftStick().y < -0.8)
		{
			direction = 0;
			stopdirection = 4;
		}
	}
	else {
		if (InputControl::GetLeftStick().y > 0.2)
		{
			direction = 3;
			stopdirection = 7;
		}

		if (InputControl::GetLeftStick().y < -0.2)
		{
			direction = 0;
			stopdirection = 4;
		}
	}

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

bool Player::GetIceFlg() const
{
	return overice;
}

void Player::SetIceFlg(bool b)
{
	this->overice = b;
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
