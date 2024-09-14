#include "Player.h"
#include "DxLib.h"
#include <math.h>
#include "../Utility/InputControl.h"
#include "../Utility/common.h"
#include "../Utility/UserData.h"
#include "../Scene/GameMain.h"
#include "CameraManager.h"
Player::Player()
{
	radius = 8;
	speed = 5;
	deadzone = UserData::LoadData(UserData::Type::SETTING);
	map_radius = 32;
}

Player::~Player()
{

}

void Player::Initialize(GameMain* _g, int _obj_pos)
{
	CharaBase::Initialize(_g, _obj_pos);
	type = (int)TYPE::_PLAYER;
	//LoadDivGraph("Resources/images/player.png", 12, 3, 4, 64, 64, playerimg);
	LoadDivGraph("Resources/images/newplayer.png", 24, 6, 4, 64, 64, playerimg);
	deadplayer_img = LoadGraph("Resources/images/player_death.png");
	angry_img = LoadGraph("Resources/images/angry.png");
	map_color = 0x4444ff;
}

void Player::Finalize()
{
	DeleteGraph(*playerimg);
	DeleteGraph(deadplayer_img);
	DeleteGraph(angry_img);
}

void Player::Update(GameMain* _g)
{

	GetMapSize(gamemain->GetMapSize());
	lastinput = 0;

	Movement();

	// ノックバックの速度を徐々に遅くする
	if (knockback != 0.0f)
	{
		knockback /= 1.1f;
	}

	// プレイヤーが生きている かつ 兵隊に捕まっていなかったら
	if (pflg == true && hitsoldier == false)
	{
		location += velocity;
		location += exvelocity;
		location -= knockback;

		exvelocity = 0;
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

		switch (direction)
		{
		case(0):	// 下移動
			imgdirection = 1;
			break;
		case(1):	// 左移動
			imgdirection = 13;
			break;
		case(2):	// 右移動
			imgdirection = 7;
			break;
		case(3):	// 上移動
			imgdirection = 19;
			break;
		case(4):	// 左斜め下移動
			imgdirection = 4;
			break;
		case(5):	// 左斜め上移動
			imgdirection = 10;
			break;
		case(6):	// 右斜め下移動
			imgdirection = 16;
			break;
		case(7):	// 右斜め上移動
			imgdirection = 22;
			break;
		case(8):	// 下停止
			imgnum = 1;
			break;
		case(9):	// 左停止
			imgnum = 13;
			break;
		case(10):	// 右停止
			imgnum = 7;
			break;
		case(11):	// 上停止
			imgnum = 19;
			break;
		case(12):	// 左斜め下停止
			imgnum = 4;
			break;
		case(13):	// 左斜め上停止
			imgnum = 10;
			break;
		case(14):	// 右斜め下停止
			imgnum = 16;
			break;
		case(15):	// 右斜め上停止
			imgnum = 22;
			break;
		default:
			break;
		}

		//// プレイヤーアニメーション
		//if (direction == 0) {	// 下移動
		//	imgdirection = 1;
		//}
		//else if (direction == 1) {	// 左移動
		//	imgdirection = 13;
		//}
		//else if (direction == 2) {	// 右移動
		//	imgdirection = 7;
		//}
		//else if (direction == 3) {	// 上移動
		//	imgdirection = 19;
		//}
		//else if (direction == 4) {	// 左斜め下移動
		//	imgdirection = 4;
		//}
		//else if (direction == 5) {	// 左斜め上移動
		//	imgdirection = 10;
		//}
		//else if (direction == 6) {	// 右斜め下移動
		//	imgdirection = 16;
		//}
		//else if (direction == 7) {	// 右斜め上移動
		//	imgdirection = 22;
		//}
		//else if (direction == 8) {	// 下停止
		//	imgnum = 1;
		//}
		//else if (direction == 9) {	// 左停止
		//	imgnum = 13;
		//}
		//else if (direction == 10) {	// 右停止
		//	imgnum = 7;
		//}
		//else if (direction == 11) {	// 上停止
		//	imgnum = 19;
		//}
		//else if (direction == 12) {	// 左斜め下停止
		//	imgnum = 4;
		//}
		//else if (direction == 13) {	// 左斜め上停止
		//	imgnum = 10;
		//}
		//else if (direction == 14) {	// 右斜め下停止
		//	imgnum = 16;
		//}
		//else if (direction == 15) {	// 右斜め上停止
		//	imgnum = 22;
		//}
	}

	//////////// プレイヤーの残機処理 ////////////

	if (gamemain->GetLife() <= 0)
	{
		SetPlayerFlg(false);
	}

}

void Player::Draw(CameraManager* camera) const
{

	// プレイヤーが生きている かつ 兵隊に捕まっていなかったら
	if (pflg == true && hitsoldier == false) {
		// 点滅フラグがfalseだったら
		if (blinkingflg == false)
		{
			DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
						 , location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
						 , 1.0f * (1 - (((camera->GetDistance()) / DISTANCE_NUM) / 1.0f)), 0.0, playerimg[imgnum], true);
		}
		else {
			SetIgnoreDrawGraphColor(TRUE);
			DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
						 , location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
						 , 1.0f * (1 - ((camera->GetDistance() / DISTANCE_NUM) / 1.0f)), 0.0, playerimg[imgnum], true);
			SetIgnoreDrawGraphColor(FALSE);
		}
	}
	// プレイヤーが死んでいる かつ 兵隊に捕まっていなかったら
	else if(pflg == false && hitsoldier == false) {
		DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
					 , location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
					 , 1.0f * (1 - ((camera->GetDistance() / DISTANCE_NUM) / 1.0f)), 0.0, deadplayer_img, true);
	}
	// 兵隊に捕まっていたら
	else if (hitsoldier == true)
	{
		DrawRotaGraphF(location.x * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().x + (SCREEN_WIDTH / 2))
					 , location.y * (1 - ((camera->GetDistance() / 1.0f))) + (-camera->GetLocation().y + (SCREEN_HEIGHT / 2))
					 , 1.2f * (1 - ((camera->GetDistance() / DISTANCE_NUM) / 1.0f)), 0.0, angry_img, true);
	}
	
	// 元の描画を取得
	int OldBlendMode;
	int OldBlendParam;
	GetDrawBlendMode(&OldBlendMode,&OldBlendParam);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)max(((180. / Invincible_cnt) * 6) - 48, 0));
	DrawBox(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, 0xff0000, true);
	SetDrawBlendMode(OldBlendMode, OldBlendParam);

}

void Player::Hit(Object* _obj)
{
	if (static_cast<CharaBase*>(_obj)->GetType() == CharaBase::TYPE::_EXPLOSION)
	{
		if (!hitflg)
		{
			gamemain->AddLife(-1);
		}
		SetHitFlg(true);
		KnockBack(static_cast<Object*>(_obj)->GetLocation());
		SetDamageDirectionFlg(true);
	}

	if (static_cast<Tornado*>(_obj)->GetType() == TYPE::_TORNADO)
	{
		float length = GetLength(static_cast<Object*>(_obj)->GetLocation() - GetLocation());
		Vector2D vvec = (static_cast<Object*>(_obj)->GetLocation() - GetLocation());
		vvec /= length;
		SetEXVelocity(vvec * 7.8f);
	}

	if (static_cast<Tornado*>(_obj)->GetType() == TYPE::_CONVEYER)
	{
		
	}
}

void Player::Movement()
{
	InputB = false;
	// プレイヤーが生きている かつ 兵隊に捕まっていなかったら
	if (pflg == true && hitsoldier == false)
	{
		//// 十字キーで移動
		if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) || InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) ||
			InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) || InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
		{
			crossbuttonflg = true;

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
		else {
			crossbuttonflg = false;
		}

		// Aボタンで火の付ける/消す
		/*if (InputControl::GetButtonDown(XINPUT_BUTTON_A))
		{
			if (!ignitionflg)
			{
				ignitionflg = true;
				acceleration = 0.5f;
			}
			else {
				ignitionflg = false;
				acceleration = 4.f;
			}
		}*/


		if (fabsf(InputControl::GetLeftStick().x) > deadzone || fabsf(InputControl::GetLeftStick().y) > deadzone)
		{
			stickflg = true;
			// スティック入力
			velocity += Vector2D(
				InputControl::GetLeftStick().x * acceleration
				, -InputControl::GetLeftStick().y * acceleration);
		}
		else {
			stickflg = false;
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
	if (location.x < -MapSize + map_radius)
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
		// 歩行向き所得
		if (velocity.x != 0 || velocity.y != 0)
		{
			// 歩行アニメーション
			MoveAnim();

			// スティック移動
			if (crossbuttonflg == false)
			{
				// 右向き
				if (InputControl::GetLeftStick().x >= 0.2)
				{
					// 右斜め上移動
					if (InputControl::GetLeftStick().y >= 0.2)
					{
						if (direction != 7)
						{
							anim_cnt = 0;
						}
						direction = 7;
						stop_direction = 15;
					}
					// 右斜め下移動
					else if (InputControl::GetLeftStick().y <= -0.2)
					{
						if (direction != 6)
						{
							anim_cnt = 0;
						}
						direction = 6;
						stop_direction = 14;
					}
					// 右移動
					else {

						if (direction != 2)
						{
							anim_cnt = 0;
						}
						direction = 2;
						stop_direction = 10;
					}

				}
				// 左向き
				else if (InputControl::GetLeftStick().x <= -0.2)
				{
					// 左斜め下移動
					if (InputControl::GetLeftStick().y <= -0.2)
					{
						if (direction != 4)
						{
							anim_cnt = 0;
						}
						direction = 4;
						stop_direction = 12;
					}
					// 左斜め上移動
					else if (InputControl::GetLeftStick().y >= 0.2)
					{
						if (direction != 5)
						{
							anim_cnt = 0;
						}
						direction = 5;
						stop_direction = 13;

					}
					// 左移動
					else {

						if (direction != 1)
						{
							anim_cnt = 0;
						}
						direction = 1;
						stop_direction = 9;
					}
					
				}
				// 上移動
				else if (InputControl::GetLeftStick().y >= 0.2)
				{
					if (direction != 3)
					{
						anim_cnt = 0;
					}
					direction = 3;
					stop_direction = 11;
				}
				// 下移動
				else if (InputControl::GetLeftStick().y <= -0.2)
				{
					if (direction != 0)
					{
						anim_cnt = 0;
					}
					direction = 0;
					stop_direction = 8;
				}
			}

			// 十字キー移動
			if (stickflg == false)
			{
				// 右向き
				if (InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT))
				{
					// 右斜め上移動
					if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
					{
						if (direction != 7)
						{
							anim_cnt = 0;
						}
						direction = 7;
						stop_direction = 15;
					}
					// 右斜め下移動
					else if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
					{
						if (direction != 6)
						{
							anim_cnt = 0;
						}
						direction = 6;
						stop_direction = 14;
					}
					// 右移動
					else {
						if (direction != 2)
						{
							anim_cnt = 0;
						}
						direction = 2;
						stop_direction = 10;

					}
				}
				// 左向き
				else if (InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT))
				{
					// 左斜め上移動
					if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
					{
						if (direction != 5)
						{
							anim_cnt = 0;
						}
						direction = 5;
						stop_direction = 13;
					}
					// 左斜め下移動
					else if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
					{
						if (direction != 4)
						{
							anim_cnt = 0;
						}
						direction = 4;
						stop_direction = 12;
					}
					// 左移動
					else {
						if (direction != 1)
						{
							anim_cnt = 0;
						}
						direction = 1;
						stop_direction = 9;
					}
					
				}
				// 上移動
				else if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
				{
					if (direction != 3)
					{
						anim_cnt = 0;
					}
					direction = 3;
					stop_direction = 11;
				}
				// 下移動
				else if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
				{
					if (direction != 0)
					{
						anim_cnt = 0;
					}
					direction = 0;
					stop_direction = 8;
				}
			}
			
		}

		// 前後アニメーション
		//if (velocity.y != 0)
		//{
		//	// スティック移動
		//	if (crossbuttonflg == false)
		//	{
		//		
		//		// 上移動
		//	    if (InputControl::GetLeftStick().y >= 0.2)
		//		{
		//			if (direction != 3)
		//			{
		//				anim_cnt = 0;
		//			}
		//			direction = 3;
		//			stop_direction = 11;
		//		}
		//		// 下移動
		//		else if (InputControl::GetLeftStick().y <= -0.2)
		//		{
		//			if (direction != 0)
		//			{
		//				anim_cnt = 0;
		//			}
		//			direction = 0;
		//			stop_direction = 8;
		//		}
		//	}

		//	// 十字キー移動
		//	if (stickflg == false)
		//	{
		//		// 上移動
		//		if (InputControl::GetButton(XINPUT_BUTTON_DPAD_UP))
		//		{
		//			if (direction != 3)
		//			{
		//				anim_cnt = 0;
		//			}
		//			direction = 3;
		//			stop_direction = 11;
		//		}
		//		// 下移動
		//		else if (InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN))
		//		{
		//			if (direction != 0)
		//			{
		//				anim_cnt = 0;
		//			}
		//			direction = 0;
		//			stop_direction = 8;
		//		}
		//	}
		//	
		//}

	}

	// 立ち止まっているとき（アニメーション）
	// 左スティックが入力されていなかったら
	if (!InputControl::GetButton(XINPUT_BUTTON_DPAD_UP) && !InputControl::GetButton(XINPUT_BUTTON_DPAD_DOWN) &&
		!InputControl::GetButton(XINPUT_BUTTON_DPAD_LEFT) && !InputControl::GetButton(XINPUT_BUTTON_DPAD_RIGHT) &&
		InputControl::GetLeftStick().x < 0.2 && InputControl::GetLeftStick().x > -0.2
		&& InputControl::GetLeftStick().y < 0.2 && InputControl::GetLeftStick().y > -0.2)
	{
		direction = stop_direction;
	}

	/*if (stickflg == true && crossbuttonflg == true)
	{
		direction = stop_direction;
	}*/

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

// プレイヤーの反発
void Player::KnockBack(Vector2D EX)
{
	if (Invincible_cnt < 1)
	{
		vvec = EX - location;
		length = GetLength(EX);
		vvec /= length;

		SetKnockBack(vvec, (int)max(5, 15.f));

	}
}

// 歩行アニメーション
void Player::MoveAnim()
{
	anim_cnt++;
	switch (anim_cnt)
	{
	case(1):
		imgnum = imgdirection;
		break;
	case(15):
		imgnum--;
		break;
	case(30):
		imgnum++;
		break;
	case(45):
		imgnum++;
		break;
	case(60):
		anim_cnt = 0;
		break;
	default:
		break;
	}
}


// 右移動アニメーション
//void Player::MoveRight()
//{
//	anim_cnt++;
//	switch (anim_cnt)
//	{
//	case(1):
//		imgnum = 7;
//		break;
//	case(15):
//		imgnum = 6;
//		break;
//	case(30):
//		imgnum = 7;
//		break;
//	case(45):
//		imgnum = 8;
//		break;
//	case(60):
//		anim_cnt = 0;
//		break;
//	default:
//		break;
//	}
//}
//
//
//// 左移動アニメーション
//void Player::MoveLeft()
//{
//	anim_cnt++;
//	switch (anim_cnt)
//	{
//	case(1):
//		imgnum = 13;
//		break;
//	case(15):
//		imgnum = 12;
//		break;
//	case(30):
//		imgnum = 13;
//		break;
//	case(45):
//		imgnum = 14;
//		break;
//	case(60):
//		anim_cnt = 0;
//		break;
//	default:
//		break;
//	}
//}
//
//// 上移動アニメーション
//void Player::MoveUp()
//{
//	anim_cnt++;
//	switch (anim_cnt)
//	{
//	case(1):
//		imgnum = 19;
//		break;
//	case(15):
//		imgnum = 18;
//		break;
//	case(30):
//		imgnum = 19;
//		break;
//	case(45):
//		imgnum = 20;
//		break;
//	case(60):
//		anim_cnt = 0;
//		break;
//	default:
//		break;
//	}
//}
//
//// 下移動アニメーション
//void Player::MoveDown()
//{
//	anim_cnt++;
//	switch (anim_cnt)
//	{
//	case(1):
//		imgnum = 0;
//		break;
//	case(15):
//		imgnum = 1;
//		break;
//	case(30):
//		imgnum = 2;
//		break;
//	case(45):
//		imgnum = 1;
//		break;
//	case(60):
//		anim_cnt = 0;
//		break;
//	default:
//		break;
//	}
//}

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

bool Player::GetIgnitionFlg() const
{
	return ignitionflg;
}

void Player::SetIgnitionFlg(bool b)
{
	this->ignitionflg = b;
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

float Player::GetLength(Vector2D loc)
{
	return sqrtf(powf((loc.x - location.x), 2) + powf((loc.y - location.y), 2));
}

int Player::GetDirection()
{
	return this->direction;
}

void Player::SetKnockBack(Vector2D vec, int i)
{
	this->knockback = vec * (float)i;
}
