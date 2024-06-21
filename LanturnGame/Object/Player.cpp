#include "Player.h"
#include "DxLib.h"
#include <math.h>
#include "../Utility/InputControl.h"
#include "../Utility/common.h"
#include "../Utility/UserData.h"
Player::Player()
{
	radius = 8;
	speed = 5;
	deadzone = UserData::LoadData(UserData::Type::SETTING);
}

Player::~Player()
{
	DeleteGraph(*playerimg);
	DeleteGraph(deadplayer_img);
	DeleteGraph(angry_img);
}

void Player::Init()
{
	LoadDivGraph("Resources/images/player.png", 12, 3, 4, 64, 64, playerimg);
	deadplayer_img = LoadGraph("Resources/images/player_death.png");
	angry_img = LoadGraph("Resources/images/angry.png");
}

void Player::Update()
{
	lastinput = 0;

	Movement();

	// プレイヤーが生きている かつ 兵隊に捕まっていなかったら
	if (pflg == true && hitsoldier == false)
	{
		location += velocity;
		location += exvelocity;

	}
	// 兵隊に捕まっていたら
	else if (hitsoldier == true)
	{
		// 1.5秒スタンする
		if (stan_cnt <= 90)
		{
			stan_cnt++;
		}
		else
		{
			// プレイヤーが生きていたら
			if (pflg == true)
			{
				hitsoldier = false;
				stan_cnt = 0;
			}
		}


	}

	// 爆発か兵隊に当たったら無敵時間
	if (hitflg == true) {
		Invincible();
		Blinking();
	}

	// 兵隊に捕まっていなかったら
	if (hitsoldier == false)
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

void Player::Draw(Vector2D loc, float _distance) const
{
	// プレイヤーが生きている かつ 兵隊に捕まっていなかったら
	if (pflg == true && hitsoldier == false) {
		// 点滅フラグがfalseだったら
		if (blinkingflg == false)
		{
			DrawRotaGraphF((location.x * (1 - (float)((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.x + (SCREEN_WIDTH / 2))
						, (location.y * (1 - (float)((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0f * (1 - ((_distance / DISTANCE_MAX) / 4.0f)), 0.0, playerimg[imgnum], true);
		}
		else {
			SetIgnoreDrawGraphColor(TRUE);
			DrawRotaGraphF((location.x * (1 - (float)((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.x + (SCREEN_WIDTH / 2))
				, (location.y * (1 - (float)((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0f * (1 - ((_distance / DISTANCE_MAX) / 4.0f)), 0.0, playerimg[imgnum], true);
			SetIgnoreDrawGraphColor(FALSE);
		}
	}
	// プレイヤーが死んでいる かつ 兵隊に捕まっていなかったら
	else if(pflg == false && hitsoldier == false) {
		DrawRotaGraphF((location.x * (float)(1 - ((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.x + (SCREEN_WIDTH / 2))
			, (location.y * (float)(1 - ((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.y + (SCREEN_HEIGHT / 2)), 1.0f * (1 - ((_distance / DISTANCE_MAX) / 4.0f)), 0.0, deadplayer_img, true);
	}
	// 兵隊に捕まっていたら
	else if (hitsoldier == true)
	{
		DrawRotaGraphF((location.x * (1 - (float)((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.x + (SCREEN_WIDTH / 2))
			, (location.y * (float)(1 - ((_distance / DISTANCE_MAX) / DISTANCE_NUM))) + (-loc.y + (SCREEN_HEIGHT / 2)), 1.2f * (1 - ((_distance / DISTANCE_MAX) / 4.0f)), 0.0, angry_img, true);
	}
	
	// 元の描画を取得
	int OldBlendMode;
	int OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)max(((180. / Invincible_cnt) * 6) - 48, 0));
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff0000, true);
	SetDrawBlendMode(OldBlendMode, OldBlendParam);

}

void Player::Movement()
{
	// プレイヤーが生きている かつ 兵隊に捕まっていなかったら
	if (pflg == true && hitsoldier == false)
	{
		// 十字キーで移動
		if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) ||
			InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
			{
				velocity.x -= acceleration;
			}

			if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
			{
				velocity.x += acceleration;
			}

			if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
			{
				velocity.y -= acceleration;
			}

			if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
			{
				velocity.y += acceleration;
			}

		}
		else if (fabsf(InputControl::GetLeftStick().x) > deadzone || fabsf(InputControl::GetLeftStick().y) > deadzone)
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
	}

	// 画面外に出ないように
	if (location.x < -MapSize + areahitradius)
	{
		location.x = -MapSize + areahitradius;
	}
	if (location.x >= MapSize - areahitradius)
	{
		location.x = MapSize - areahitradius;
	}
	if (location.y < -MapSize + areahitradius)
	{
		location.y = -MapSize + areahitradius;
	}
	if (location.y >= MapSize - areahitradius)
	{
		location.y = MapSize - areahitradius;
	}

	// 兵隊に捕まっていない かつ プレイヤーが生きていたら
	if (hitsoldier == false && pflg == true) {
		// 左右アニメーション
		if (velocity.x != 0)
		{
			// 右移動
			if (InputControl::GetLeftStick().x > 0.8 || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
			{
				direction = 2;
				stop_direction = 6;
				anim_cnt = 0;
			}
			// 左移動
			else if (InputControl::GetLeftStick().x < -0.8 || InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
			{
				direction = 1;
				stop_direction = 5;
				anim_cnt = 0;
			}
		}

		// 前後アニメーション
		if (velocity.y != 0)
		{
			// 上移動
			if (InputControl::GetLeftStick().y > 0.8)
			{
				direction = 3;
				stop_direction = 7;
				anim_cnt = 0;
			}
			// 下移動
			if (InputControl::GetLeftStick().y < -0.8)
			{
				direction = 0;
				stop_direction = 4;
				anim_cnt = 0;
			}
		}

	}

	// 立ち止まっているとき（アニメーション）
	// 左スティックが入力されていなかったら
	if (InputControl::GetLeftStick().x < 0.2 && InputControl::GetLeftStick().x > -0.2 
		&& InputControl::GetLeftStick().y < 0.2 && InputControl::GetLeftStick().y > -0.2) {
		
		direction = stop_direction;
	}

}

// 無敵時間
void Player::Invincible()
{
	Invincible_cnt++;
	switch (Invincible_cnt)
	{
	case(0):
		break;
	case(180):
		hitflg = false;
		damagedirection = false;
		Invincible_cnt = 0;
		break;
	default:
		break;
	}
}

// プレイヤーの点滅
void Player::Blinking()
{
	// プレイヤーが生きていたら
	if (pflg == true) {
		blinking_cnt++;
		switch (blinking_cnt)
		{
		case(1):
			blinkingflg = true;
			break;
		case(10):
			blinkingflg = false;
			break;
		case(20):
			blinking_cnt = 0;
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
	anim_cnt++;
	switch (anim_cnt)
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
		anim_cnt = 0;
		break;
	default:
		break;
	}
}

// 左移動アニメーション
void Player::MoveLeft()
{
	anim_cnt++;
	switch (anim_cnt)
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
		anim_cnt = 0;
		break;
	default:
		break;
	}
}

// 上移動アニメーション
void Player::MoveUp()
{
	anim_cnt++;
	switch (anim_cnt)
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
		anim_cnt = 0;
		break;
	default:
		break;
	}
}

// 下移動アニメーション
void Player::MoveDown()
{
	anim_cnt++;
	switch (anim_cnt)
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
		anim_cnt = 0;
		break;
	default:
		break;
	}
}

bool Player::GetHitFlg() const
{
	return hitflg;
}

void Player::SetHitFlg(bool b)
{
	this->hitflg = b;
}

bool Player::GetPlayerFlg() const
{
	return pflg;
}

void Player::SetPlayerFlg(bool b)
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

bool Player::GetHitSoldier()const
{
	return this->hitsoldier;
}

void Player::SetHitSoldier(bool b)
{
	this->hitsoldier = b;
}

bool Player::GetIDamageDirectionFlg() const
{
	return this->damagedirection;
}

void Player::SetDamageDirectionFlg(bool b)
{
	this->damagedirection = b;
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

int Player::GetDirection()
{
	return this->direction;
}